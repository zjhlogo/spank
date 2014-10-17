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

namespace spank
{

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
		LOGE("Un-released texture %s", pTexture->getId().c_str());
		SAFE_DELETE(pTexture);
	}
	m_textureMap.clear();

	for (auto shader : m_shaderMap)
	{
		Shader* pShader = shader.second;
		LOGE("Un-released shader %s", pShader->getId().c_str());
		SAFE_DELETE(pShader);
	}
	m_shaderMap.clear();

	for (auto renderBuffer : m_renderBufferSet)
	{
		RenderBuffer* pRenderBuffer = renderBuffer;
		LOGE("Un-released render buffer 0x%08x", pRenderBuffer);
		SAFE_DELETE(pRenderBuffer);
	}
	m_renderBufferSet.clear();

	for (auto vertAttr : m_vertexAttributeMap)
	{
		VertexAttributes* pVertAttr = vertAttr.second;
		LOGE("Un-released vertex attribute 0x%08x", pVertAttr->getId().c_str());
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

	for (auto renderBuffer : m_renderBufferSet)
	{
		renderBuffer->reload(freeOld);
	}
}

void RendererGl2::resize(int width, int height)
{
	LOGD("Renderer resized %dx%d", width, height);

	glViewport(0, 0, width, height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Texture* RendererGl2::createTexture(const std::string& filePath)
{
	// first, find from map
	TM_TEXTURE::iterator it = m_textureMap.find(filePath);
	if (it != m_textureMap.end())
	{
		it->second->incRef();
		return it->second;
	}

	// second, create new one
	Texture* pTexture = new Texture(this);
	if (!pTexture->loadFromFile(filePath))
	{
		SAFE_DELETE(pTexture);
		return nullptr;
	}

	// cache it
	m_textureMap.insert(std::make_pair(pTexture->getId(), pTexture));

	return pTexture;
}

Shader* RendererGl2::createShader(const std::string& filePath)
{
	// first, find shader from map
	TM_SHADER::iterator it = m_shaderMap.find(filePath);
	if (it != m_shaderMap.end())
	{
		it->second->incRef();
		return it->second;
	}

	// second, create new one
	Shader* pShader = new Shader(this);
	if (!pShader->loadFromFile(filePath))
	{
		SAFE_DELETE(pShader);
		return nullptr;
	}

	// cache it
	m_shaderMap.insert(std::make_pair(pShader->getId(), pShader));

	return pShader;
}

MemRenderBuffer* RendererGl2::createMemRenderBuffer(const VertexAttributes* pVertAttrs)
{
	if (!pVertAttrs) return nullptr;

	// new one
	MemRenderBuffer* pRenderBuffer = new MemRenderBuffer(this, pVertAttrs);

	// cache it
	m_renderBufferSet.insert(pRenderBuffer);

	return pRenderBuffer;
}

VMemRenderBuffer* RendererGl2::createVMemRenderBuffer(const VertexAttributes* pVertAttrs)
{
	if (!pVertAttrs) return nullptr;

	// new one
	VMemRenderBuffer* pRenderBuffer = new VMemRenderBuffer(this, pVertAttrs);

	// cache it
	m_renderBufferSet.insert(pRenderBuffer);

	return pRenderBuffer;
}

VertexAttributes* RendererGl2::createVertexAttributes(const std::string& filePath)
{
	// first, find shader from map
	TM_VERTEX_ATTRIBUTE::iterator it = m_vertexAttributeMap.find(filePath);
	if (it != m_vertexAttributeMap.end())
	{
		it->second->incRef();
		return it->second;
	}

	// second, create new one
	VertexAttributes* pVertAttrs = new VertexAttributes(this);
	if (!pVertAttrs->loadFromFile(filePath))
	{
		SAFE_DELETE(pVertAttrs);
		return nullptr;
	}

	// cache it
	m_vertexAttributeMap.insert(std::make_pair(pVertAttrs->getId(), pVertAttrs));

	return pVertAttrs;
}

bool RendererGl2::removeTexture(Texture* pTexture)
{
	if (!pTexture) return false;

	TM_TEXTURE::iterator it = m_textureMap.find(pTexture->getId());
	if (it == m_textureMap.end())
	{
		LOGE("can not find texture %s from map", pTexture->getId().c_str());
		return true;
	}

	m_textureMap.erase(it);
	return true;
}

bool RendererGl2::removeShader(Shader* pShader)
{
	if (!pShader) return false;

	TM_SHADER::iterator it = m_shaderMap.find(pShader->getId());
	if (it == m_shaderMap.end())
	{
		LOGE("can not find shader %s from map", pShader->getId().c_str());
		return true;
	}

	m_shaderMap.erase(it);
	return true;
}

bool RendererGl2::removeRenderBuffer(RenderBuffer* pBuffer)
{
	if (!pBuffer) return false;

	TS_RENDER_BUFFER::iterator it = m_renderBufferSet.find(pBuffer);
	if (it == m_renderBufferSet.end())
	{
		LOGE("can not find VMem Render Buffer 0x%08x from map", pBuffer);
		return true;
	}

	m_renderBufferSet.erase(it);
	return true;
}

bool RendererGl2::removeVertexAttributes(VertexAttributes* pVertAttrs)
{
	if (!pVertAttrs) return false;

	TM_VERTEX_ATTRIBUTE::iterator it = m_vertexAttributeMap.find(pVertAttrs->getId());
	if (it == m_vertexAttributeMap.end())
	{
		LOGE("can not find Vertex Attributes %s from map", pVertAttrs->getId().c_str());
		return true;
	}

	m_vertexAttributeMap.erase(it);

	return true;
}

}
