/*!
 * \file RenderCache.h
 * \date 2-26-2015 19:07:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "Shader.h"
#include "Texture.h"
#include "VertexAttributes.h"
#include "RenderBuffer.h"
#include <functional>

namespace spank
{

template <typename T> class RenderCache
{
public:
	enum CONST_DEFINE
	{
		DEFAULT_MAX_VERTEX = 512,
	};

	typedef std::vector<T> TV_VERTEX_CACHE;
	typedef std::vector<short> TV_SHORT;

	typedef std::function<void(Shader* pShader, Texture* pTexture, VMemVertexBuffer*, VMemIndexBuffer*)> FUNC_RENDER;

public:
	RenderCache(IRenderer* pRenderer, const tstring& strVertAttr, int maxCache = DEFAULT_MAX_VERTEX)
	{
		m_nMaxVertex = maxCache;
		m_pVertexAttributes = pRenderer->createVertexAttributes(strVertAttr);
		m_pVMemVertexBuffer = pRenderer->createVMemVertexBuffer(m_pVertexAttributes);
		m_pVMemIndexBuffer = pRenderer->createVMemIndexBuffer();
	}

	virtual ~RenderCache()
	{
		SAFE_RELEASE(m_pVertexAttributes);
		SAFE_RELEASE(m_pVMemVertexBuffer);
		SAFE_RELEASE(m_pVMemIndexBuffer);
	}

	bool add(Shader* pShader, Texture* pTexture, const T* pVertexData, int numVertexData, const short* pIndex, int numIndex)
	{
		if (!pShader || !pShader->getVertexAttributes()->isEqual(m_pVertexAttributes)) return false;

		if (m_pShader != pShader || m_pTexture != pTexture)
		{
			flush();
		}

		size_t baseIndex = m_vertexCache.size();
		if (baseIndex + numVertexData >= (size_t)m_nMaxVertex)
		{
			flush();
		}

		m_pShader = pShader;
		m_pTexture = pTexture;

		for (int i = 0; i < numVertexData; ++i)
		{
			m_vertexCache.push_back(pVertexData[i]);
		}

		for (int i = 0; i < numIndex; ++i)
		{
			m_indexCache.push_back(baseIndex + pIndex[i]);
		}

		return true;
	}

	void flush()
	{
		if (m_vertexCache.size() > 0 && m_indexCache.size() > 0 && m_pShader)
		{
			m_pVMemVertexBuffer->uploadBuffer(m_vertexCache.data(), sizeof(T)*m_vertexCache.size());
			m_pVMemIndexBuffer->uploadBuffer(m_indexCache.data(), sizeof(short)*m_indexCache.size());

			// render the data
			m_funcRender(m_pShader, m_pTexture, m_pVMemVertexBuffer, m_pVMemIndexBuffer);
		}

		m_pShader = nullptr;
		m_pTexture = nullptr;
		m_vertexCache.clear();
		m_indexCache.clear();
	}

	void setFuncRender(const FUNC_RENDER& funcRender) { m_funcRender = funcRender; };

private:
	Shader* m_pShader = nullptr;
	VertexAttributes* m_pVertexAttributes = nullptr;
	Texture* m_pTexture = nullptr;

	int m_nMaxVertex{ DEFAULT_MAX_VERTEX };
	TV_VERTEX_CACHE m_vertexCache;
	TV_SHORT m_indexCache;

	VMemVertexBuffer* m_pVMemVertexBuffer = nullptr;
	VMemIndexBuffer* m_pVMemIndexBuffer = nullptr;

	FUNC_RENDER m_funcRender;

};

}
