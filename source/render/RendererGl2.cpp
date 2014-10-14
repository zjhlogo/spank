/*!
 * \file RendererGl2.cpp
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#include "RendererGl2.h"
#include "Texture.h"
#include "Shader.h"
#include "RenderBuffer.h"
#include "VertexAttributes.h"
#include "../utils/LogUtil.h"

#include <GLES2/gl2.h>

RendererGl2::RendererGl2()
{

}

RendererGl2::~RendererGl2()
{

}

bool RendererGl2::initialize()
{
	LOGI("Version: %s", glGetString(GL_VERSION));
	LOGI("Vendor: %s", glGetString(GL_VENDOR));
	LOGI("Renderer: %s", glGetString(GL_RENDERER));
	LOGI("Extensions: %s", glGetString(GL_EXTENSIONS));

	return true;
}

void RendererGl2::terminate()
{
	// release all objects
	for (auto texture : m_textureMap)
	{
		Texture* pTexture = texture.second;
		SAFE_DELETE(pTexture);
	}
	m_textureMap.clear();

	for (auto shader : m_shaderMap)
	{
		Shader* pShader = shader.second;
		SAFE_DELETE(pShader);
	}
	m_shaderMap.clear();

	for (auto renderBuffer : m_vmemRenderBufferSet)
	{
		VMemRenderBuffer* pRenderBuffer = renderBuffer;
		SAFE_DELETE(pRenderBuffer);
	}
	m_vmemRenderBufferSet.clear();

	for (auto vertAttr : m_vertexAttributeMap)
	{
		VertexAttributes* pVertAttr = vertAttr.second;
		SAFE_DELETE(pVertAttr);
	}
	m_vertexAttributeMap.clear();
}

void RendererGl2::reload(bool freeOld)
{
	// reload all objects
	for (auto texture : m_textureMap)
	{
		texture.second->reload(freeOld);
	}

	for (auto shader : m_shaderMap)
	{
		shader.second->reload(freeOld);
	}

	for (auto renderBuffer : m_vmemRenderBufferSet)
	{
		renderBuffer->reload(freeOld);
	}
}

Texture* RendererGl2::createTexture(const std::string& filePath)
{
	// first, find from map
	TM_TEXTURE::iterator it = m_textureMap.find(filePath);
	if (it != m_textureMap.end()) return it->second;

	// second, create new one
	Texture* pTexture = new Texture();
	if (!pTexture->loadFromFile(filePath))
	{
		SAFE_DELETE(pTexture);
		return nullptr;
	}

	// cache it
	m_textureMap.insert(std::make_pair(pTexture->getId(), pTexture));

	return pTexture;
}

bool RendererGl2::releaseTexture(Texture* pTexture)
{
	if (!pTexture) return false;

	TM_TEXTURE::iterator it = m_textureMap.find(pTexture->getId());
	if (it == m_textureMap.end())
	{
		LOGE("can not find texture from map");
		SAFE_DELETE(pTexture);
		return true;
	}

	m_textureMap.erase(it);
	SAFE_DELETE(pTexture);
	return true;
}

Shader* RendererGl2::createShader(const std::string& filePath)
{
	// first, find shader from map
	TM_SHADER::iterator it = m_shaderMap.find(filePath);
	if (it != m_shaderMap.end()) return it->second;

	// second, create new one
	Shader* pShader = new Shader();
	if (!pShader->loadFromFile(filePath, this))
	{
		SAFE_DELETE(pShader);
		return nullptr;
	}

	// cache it
	m_shaderMap.insert(std::make_pair(pShader->getId(), pShader));

	return pShader;
}

bool RendererGl2::releaseShader(Shader* pShader)
{
	if (!pShader) return false;

	TM_SHADER::iterator it = m_shaderMap.find(pShader->getId());
	if (it == m_shaderMap.end())
	{
		LOGE("can not find shader from map");
		SAFE_DELETE(pShader);
		return true;
	}

	m_shaderMap.erase(it);
	SAFE_DELETE(pShader);
	return true;
}

VMemRenderBuffer* RendererGl2::createVMemRenderBuffer(const VertexAttributes* pVertAttrs)
{
	if (!pVertAttrs) return nullptr;

	VMemRenderBuffer* pRenderBuffer = new VMemRenderBuffer(pVertAttrs);
	if (!pRenderBuffer->createBufferObject())
	{
		SAFE_DELETE(pRenderBuffer);
		return nullptr;
	}

	// cache it
	m_vmemRenderBufferSet.insert(pRenderBuffer);

	return pRenderBuffer;
}

bool RendererGl2::releaseVMemRenderBuffer(VMemRenderBuffer* pBuffer)
{
	if (!pBuffer) return false;

	TS_VMEM_RENDER_BUFFER::iterator it = m_vmemRenderBufferSet.find(pBuffer);
	if (it == m_vmemRenderBufferSet.end())
	{
		LOGE("can not find VMem Render Buffer from map");
		SAFE_DELETE(pBuffer);
		return true;
	}

	m_vmemRenderBufferSet.erase(it);
	SAFE_DELETE(pBuffer);
	return true;
}

VertexAttributes* RendererGl2::createVertexAttributes(const std::string& filePath)
{
	// first, find shader from map
	TM_VERTEX_ATTRIBUTE::iterator it = m_vertexAttributeMap.find(filePath);
	if (it != m_vertexAttributeMap.end()) return it->second;

	// second, create new one
	VertexAttributes* pVertAttrs = new VertexAttributes();
	if (!pVertAttrs->loadFromFile(filePath))
	{
		SAFE_DELETE(pVertAttrs);
		return nullptr;
	}

	// cache it
	m_vertexAttributeMap.insert(std::make_pair(pVertAttrs->getId(), pVertAttrs));

	return pVertAttrs;
}

bool RendererGl2::releaseVertexAttributes(VertexAttributes* pVertAttrs)
{
	if (!pVertAttrs) return false;

	TM_VERTEX_ATTRIBUTE::iterator it = m_vertexAttributeMap.find(pVertAttrs->getId());
	if (it == m_vertexAttributeMap.end())
	{
		LOGE("can not find Vertex Attributes from map");
		SAFE_DELETE(pVertAttrs);
		return true;
	}

	// don't delete it untill terminate

	return true;
}
