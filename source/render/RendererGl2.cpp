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
		if (texture.second->reload(freeOld))
		{
			LOGI("Reload texture success %s", texture.second->getId().c_str());
		}
		else
		{
			LOGE("Reload texture failed %s", texture.second->getId().c_str());
		}
	}

	for (auto shader : m_shaderMap)
	{
		if (shader.second->reload(freeOld))
		{
			LOGI("Reload shader success %s", shader.second->getId().c_str());
		}
		else
		{
			LOGE("Reload shader failed %s", shader.second->getId().c_str());
		}
	}

	for (auto renderBuffer : m_renderBufferSet)
	{
		if (renderBuffer->reload(freeOld))
		{
			LOGI("Reload render buffer success %x", renderBuffer);
		}
		else
		{
			LOGI("Reload render buffer success %x", renderBuffer);
		}
	}
}

void RendererGl2::resize(int width, int height)
{
	LOGD("Renderer resized %dx%d", width, height);

	m_surfaceSize.x = static_cast<float>(width);
	m_surfaceSize.y = static_cast<float>(height);

	m_matOrtho = glm::ortho(-width*0.5f, width*0.5f, -height*0.5f, height*0.5f);

	glViewport(0, 0, width, height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

const glm::vec2& RendererGl2::getSurfaceSize() const
{
	return m_surfaceSize;
}

const glm::mat4& RendererGl2::getOrthoMatrix() const
{
	return m_matOrtho;
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

MemVertexBuffer* RendererGl2::createMemVertexBuffer(const VertexAttributes* pVertAttrs)
{
	if (!pVertAttrs) return nullptr;

	// new one
	MemVertexBuffer* pRenderBuffer = new MemVertexBuffer(this, pVertAttrs);

	// cache it
	m_renderBufferSet.insert(pRenderBuffer);

	return pRenderBuffer;
}

VMemVertexBuffer* RendererGl2::createVMemVertexBuffer(const VertexAttributes* pVertAttrs)
{
	if (!pVertAttrs) return nullptr;

	// new one
	VMemVertexBuffer* pRenderBuffer = new VMemVertexBuffer(this, pVertAttrs);

	// cache it
	m_renderBufferSet.insert(pRenderBuffer);

	return pRenderBuffer;
}

MemIndexBuffer* RendererGl2::createMemIndexBuffer()
{
	// new one
	MemIndexBuffer* pRenderBuffer = new MemIndexBuffer(this);

	// cache it
	m_renderBufferSet.insert(pRenderBuffer);

	return pRenderBuffer;
}

VMemIndexBuffer* RendererGl2::createVMemIndexBuffer()
{
	// new one
	VMemIndexBuffer* pRenderBuffer = new VMemIndexBuffer(this);

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
