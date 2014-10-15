/*!
 * \file Shader.cpp
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#include "Shader.h"
#include "IRenderer.h"
#include "Texture.h"
#include "VertexAttributes.h"
#include "RenderBuffer.h"

#include "../utils/FileUtil.h"
#include "../utils/StringUtil.h"
#include "../utils/LogUtil.h"

#include <libTinyxml2/source/tinyxml2.h>

namespace spank
{

class AutoDeleteShaderObj
{
public:
	AutoDeleteShaderObj(GLuint shaderId) :m_shaderId(shaderId) {};
	~AutoDeleteShaderObj() { if (m_shaderId != 0) glDeleteShader(m_shaderId); };

private:
	GLuint m_shaderId;

};

Shader::Shader(IRenderer* pRenderer)
	:m_pRenderer(pRenderer)
{

}

Shader::~Shader()
{
	destroyProgram();
	SAFE_RELEASE(m_pVertAttributes);
}

bool Shader::loadFromFile(const std::string& filePath)
{
	std::string xmlData;
	if (!FileUtil::readStringFile(xmlData, filePath)) return false;

	tinyxml2::XMLDocument doc;
	if (doc.Parse(xmlData.data()) != tinyxml2::XML_SUCCESS) return false;

	tinyxml2::XMLElement* pXmlRoot = doc.RootElement();
	if (!pXmlRoot) return false;

	const char* pszAttrFile = pXmlRoot->Attribute("attributes");
	const char* pszVertFile = pXmlRoot->Attribute("vertex_shader");
	const char* pszFragFile = pXmlRoot->Attribute("fregment_shader");
	if (!pszAttrFile || !pszVertFile || !pszFragFile) return false;

	// get texture list
	m_textureInfoMap.clear();
	int index = 0;
	for (tinyxml2::XMLElement* pXmlTexture = pXmlRoot->FirstChildElement("texture"); pXmlTexture != nullptr; pXmlTexture = pXmlTexture->NextSiblingElement("texture"))
	{
		const char* pszName = pXmlTexture->Attribute("name");
		if (!pszName) return false;

		TEXTURE_INFO textureInfo;
		textureInfo.slotId = index++;
		textureInfo.name = pszName;

		m_textureInfoMap.insert(std::make_pair(textureInfo.slotId, textureInfo));
	}

	std::string strDir = StringUtil::getFileDir(filePath);

	// create vertex attributes
	m_pVertAttributes = m_pRenderer->createVertexAttributes(strDir + "/" + pszAttrFile);
	if (!m_pVertAttributes) return false;

	// read vertex shader text
	if (!FileUtil::readStringFile(m_vertexShaderData, strDir + "/" + pszVertFile)) return false;

	// read fragment shader text
	if (!FileUtil::readStringFile(m_fragShaderData, strDir + "/" + pszFragFile)) return false;

	if (reload(true))
	{
		setId(filePath);
		return true;
	}

	return false;
}

bool Shader::reload(bool freeOld)
{
	if (freeOld) destroyProgram();

	m_programId = glCreateProgram();
	if (m_programId == 0) return false;

	// create vertex shader
	GLuint vertexId = compileShader(GL_VERTEX_SHADER, m_vertexShaderData);
	AutoDeleteShaderObj vertexShaderObj(vertexId);
	if (vertexId == 0) return false;

	// create fragment shader
	GLuint fragmentId = compileShader(GL_FRAGMENT_SHADER, m_fragShaderData);
	AutoDeleteShaderObj fragmentShaderObj(fragmentId);
	if (fragmentId == 0) return false;

	// attach shaders
	glAttachShader(m_programId, vertexId);
	glAttachShader(m_programId, fragmentId);

	// bind attribute
	int numAttrs = m_pVertAttributes->getNumAttributeItems();
	for (int i = 0; i < numAttrs; ++i)
	{
		const VertexAttributes::ATTRIBUTE_ITEM* pAttrItem = m_pVertAttributes->getAttributeItem(i);
		glBindAttribLocation(m_programId, i, pAttrItem->name.c_str());
	}

	// link program
	glLinkProgram(m_programId);
	if (getProgramErrorLog(m_programId))
	{
		LOGE("Link program failed with error log %s", m_errorLog.c_str());
		return false;
	}

	// bind texture slot
	glUseProgram(m_programId);
	for (auto textureInfo : m_textureInfoMap)
	{
		TEXTURE_INFO& info = textureInfo.second;
		GLint loc = glGetUniformLocation(m_programId, info.name.c_str());
		GL_ERROR_CHECK();

		glUniform1i(loc, info.slotId);
		GL_ERROR_CHECK();
	}
	glUseProgram(0);

	return true;
}

void Shader::useProgram()
{
	glUseProgram(m_programId);
	GL_ERROR_CHECK();
}

bool Shader::setMatrix(const char* pszName, const float* pMatrix)
{
	// First gets the location of that variable in the shader using its name
	int loc = glGetUniformLocation(m_programId, pszName);
	GL_ERROR_CHECK();

	// Then passes the matrix to that variable
	glUniformMatrix4fv(loc, 1, GL_FALSE, pMatrix);
	GL_ERROR_CHECK();

	return true;
}

bool Shader::setTexture(Texture* pTexture, int index)
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, pTexture->getTextureId());
	GL_ERROR_CHECK();

	return true;
}

void Shader::drawArrays(MemRenderBuffer* pRenderBuffer, int start, int numVerts)
{
	if (!pRenderBuffer) return;

	uint bufferSize = pRenderBuffer->getBufferSize();
	if (bufferSize == 0) return;

	if (!m_pVertAttributes->isEqual(pRenderBuffer->getVertexAttributes())) return;

	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	int numAttrs = m_pVertAttributes->getNumAttributeItems();
	int stride = m_pVertAttributes->getStride();

	for (int i = 0; i < numAttrs; ++i)
	{
		const VertexAttributes::ATTRIBUTE_ITEM* pAttrItem = m_pVertAttributes->getAttributeItem(i);

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, pAttrItem->size, pAttrItem->glType, GL_FALSE, stride, (void*)(pRenderBuffer->getBufferMemAddr() + pAttrItem->offset));
	}

	// Draws a non-indexed triangle array
	glDrawArrays(GL_TRIANGLES, start, numVerts);
	GL_ERROR_CHECK();
}

void Shader::drawArrays(VMemRenderBuffer* pRenderBuffer, int start, int numVerts)
{
	if (!pRenderBuffer) return;

	uint bufferSize = pRenderBuffer->getBufferSize();
	if (bufferSize == 0) return;

	if (!m_pVertAttributes->isEqual(pRenderBuffer->getVertexAttributes())) return;

	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, pRenderBuffer->getBufferId());
	GL_ERROR_CHECK();

	int numAttrs = m_pVertAttributes->getNumAttributeItems();
	int stride = m_pVertAttributes->getStride();

	for (int i = 0; i < numAttrs; ++i)
	{
		const VertexAttributes::ATTRIBUTE_ITEM* pAttrItem = m_pVertAttributes->getAttributeItem(i);

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, pAttrItem->size, pAttrItem->glType, GL_FALSE, stride, (void*)pAttrItem->offset);
	}

	// Draws a non-indexed triangle array
	glDrawArrays(GL_TRIANGLES, start, numVerts);
	GL_ERROR_CHECK();

	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Shader::destroyProgram()
{
	if (m_programId != 0)
	{
		glDeleteProgram(m_programId);
		m_programId = 0;
	}
}

GLuint Shader::compileShader(GLuint shaderType, const std::string& shaderData)
{
	if (shaderData.length() <= 0) return 0;

	int shaderId = glCreateShader(shaderType);
	if (shaderId == 0) return 0;

	const char* pszShader = shaderData.c_str();
	glShaderSource(shaderId, 1, &pszShader, NULL);
	glCompileShader(shaderId);

	if (getShaderErrorLog(shaderId))
	{
		LOGE("Compile shader failed with error log %s", m_errorLog.c_str());
		glDeleteShader(shaderId);
		return 0;
	}

	return shaderId;
}

bool Shader::getShaderErrorLog(GLuint shaderId)
{
	GLint compileStatus = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_TRUE) return false;

	GLint infoLength = 0;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLength);
	if (infoLength <= 1) return false;

	BUFFER_DATA buffer;
	buffer.resize(infoLength);

	GLsizei charWritten = 0;
	glGetShaderInfoLog(shaderId, infoLength, &charWritten, buffer.data());

	m_errorLog.clear();
	m_errorLog.append(buffer.data(), infoLength);

	return true;
}

bool Shader::getProgramErrorLog(GLuint programId)
{
	GLint linkStatus = 0;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_TRUE) return false;

	GLint infoLength = 0;
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLength);
	if (infoLength <= 1) return false;

	BUFFER_DATA buffer;
	buffer.resize(infoLength);

	GLsizei charWritten = 0;
	glGetProgramInfoLog(programId, infoLength, &charWritten, buffer.data());

	m_errorLog.clear();
	m_errorLog.append(buffer.data(), infoLength);

	return true;
}

void Shader::preDelete()
{
	m_pRenderer->removeShader(this);
}

}
