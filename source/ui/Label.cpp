/*!
 * \file Label.cpp
 * \date 10-18-2014 15:34:07
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Label.h"
#include "../font/IFont.h"
#include "../render/RenderBuffer.h"
#include "../render/IRenderer.h"
#include "../render/Shader.h"
#include "../render/VertexAttributes.h"

namespace spank
{

Label::Label(IRenderer* pRenderer, IFont* pFont)
	:m_pRenderer(pRenderer)
	, m_pFont(pFont)
{
	m_pShader = m_pRenderer->createShader("data/shaders/pos3_uv2.shader");
}

Label::~Label()
{
	SAFE_RELEASE(m_pShader);
	SAFE_RELEASE(m_vertexBuffer);
	clearBuffer();
}

void Label::setText(const tstring& text)
{
	if (m_text == text) return;
	m_text = text;

	// 
	createBuffer(m_text);
}

glm::vec2 Label::calcTextSize(const tstring& text)
{
	// calculate the number of lines
	int numLines = 1;
	for (const auto& charId : text)
	{
		if (charId == '\n') ++numLines;
	}

	int lineHeight = m_pFont->getLineHeight();
	// adjust the start position base on number of lines
	glm::vec2 textSize;
	textSize.y = (float)(numLines * lineHeight);

	glm::vec2 currPos;
	currPos.y += (numLines - 1) * lineHeight;

	for (const auto& charId : text)
	{
		if (charId == '\n')
		{
			currPos.y -= lineHeight;
			currPos.x = 0.0f;
			continue;
		}

		const IFont::CHAR_INFO& charInfo = m_pFont->getCharInfo(charId);
		if (charInfo.charId == 0) continue;

		glm::vec2 charPos = currPos + charInfo.offset;
		currPos.x += charInfo.xadvance;

		if (textSize.x < currPos.x) textSize.x = currPos.x;
	}

	return textSize;
}

void Label::render()
{
	if (m_indexBufferInfoMap.empty()) return;

	m_pShader->useProgram();

	glm::mat4 matTran;
	matTran = glm::translate(matTran, glm::vec3(m_pos, 0.0f));

	glm::mat4 matMVP = m_pRenderer->getOrthoMatrix() * matTran;
	m_pShader->setUniform("u_matMVP", matMVP);

	for (auto it : m_indexBufferInfoMap)
	{
		INDEX_BUFFER_INFO* pBufferInfo = it.second;
		m_pShader->setTexture(pBufferInfo->pTexture, 0);
		m_pShader->drawBuffer(m_vertexBuffer, pBufferInfo->pIndexBuffer);
	}
}

void Label::clearBuffer()
{
	for (auto it : m_indexBufferInfoMap)
	{
		INDEX_BUFFER_INFO* pBufferInfo = it.second;
		SAFE_RELEASE(pBufferInfo->pIndexBuffer);
		SAFE_DELETE(pBufferInfo);
	}
	m_indexBufferInfoMap.clear();
}

bool Label::createBuffer(const tstring& text)
{
	clearBuffer();

	if (!m_vertexBuffer)
	{
		m_vertexBuffer = m_pRenderer->createVMemVertexBuffer(m_pFont->getVertexAttributes());
		if (!m_vertexBuffer) return false;
	}

	// calculate the number of lines
	int numLines = 1;
	for (const auto& charId : text)
	{
		if (charId == '\n') ++numLines;
	}

	// adjust the start position base on number of lines
	glm::vec2 currPos;
	currPos.y += (numLines - 1)*m_pFont->getLineHeight();

	std::vector<VERT_ATTR_POS3_UV2> vVerts;

	for (const auto& charId : text)
	{
		if (charId == '\n')
		{
			currPos.y -= m_pFont->getLineHeight();
			currPos.x = 0.0f;
			continue;
		}

		const IFont::CHAR_INFO& charInfo = m_pFont->getCharInfo(charId);
		if (charInfo.charId == 0) continue;

		INDEX_BUFFER_INFO* pBufferInfo = findIndexBuffer(charInfo.pTexture);
		if (!pBufferInfo) continue;

		glm::vec2 charPos = currPos + charInfo.offset;

		uint16 baseVertIndex = static_cast<uint16>(vVerts.size());

		VERT_ATTR_POS3_UV2 vert;
		vert.x = charPos.x;
		vert.y = charPos.y;
		vert.z = 0.0f;
		vert.u = charInfo.uv.x;
		vert.v = charInfo.uv.y;
		vVerts.push_back(vert);

		vert.x = charPos.x;
		vert.y = charPos.y + charInfo.size.y;
		vert.z = 0.0f;
		vert.u = charInfo.uv.x;
		vert.v = charInfo.uv.y + charInfo.duv.y;
		vVerts.push_back(vert);

		vert.x = charPos.x + charInfo.size.x;
		vert.y = charPos.y + charInfo.size.y;
		vert.z = 0.0f;
		vert.u = charInfo.uv.x + charInfo.duv.x;
		vert.v = charInfo.uv.y + charInfo.duv.y;
		vVerts.push_back(vert);

		vert.x = charPos.x + charInfo.size.x;
		vert.y = charPos.y;
		vert.z = 0.0f;
		vert.u = charInfo.uv.x + charInfo.duv.x;
		vert.v = charInfo.uv.y;
		vVerts.push_back(vert);

		pBufferInfo->vIndis.push_back(baseVertIndex + 0);
		pBufferInfo->vIndis.push_back(baseVertIndex + 1);
		pBufferInfo->vIndis.push_back(baseVertIndex + 3);
		pBufferInfo->vIndis.push_back(baseVertIndex + 1);
		pBufferInfo->vIndis.push_back(baseVertIndex + 2);
		pBufferInfo->vIndis.push_back(baseVertIndex + 3);

		currPos.x += charInfo.xadvance;
	}

	m_vertexBuffer->uploadBuffer(vVerts.data(), vVerts.size()*sizeof(VERT_ATTR_POS3_UV2));

	// upload index buffer
	for (auto it : m_indexBufferInfoMap)
	{
		INDEX_BUFFER_INFO* pBufferInfo = it.second;
		pBufferInfo->pIndexBuffer->uploadBuffer(pBufferInfo->vIndis.data(), pBufferInfo->vIndis.size()*sizeof(uint16));
		pBufferInfo->vIndis.clear();
	}

	return true;
}

Label::INDEX_BUFFER_INFO* Label::findIndexBuffer(Texture* pTexture)
{
	auto it = m_indexBufferInfoMap.find(pTexture);
	if (it != m_indexBufferInfoMap.end()) return it->second;

	VMemIndexBuffer* pVMemIndexBuffer = m_pRenderer->createVMemIndexBuffer();
	if (!pVMemIndexBuffer) return nullptr;

	INDEX_BUFFER_INFO* pBufferInfo = new INDEX_BUFFER_INFO();
	pBufferInfo->pTexture = pTexture;
	pBufferInfo->pIndexBuffer = pVMemIndexBuffer;
	m_indexBufferInfoMap.insert(std::make_pair(pTexture, pBufferInfo));

	return pBufferInfo;
}

}
