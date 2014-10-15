/*!
 * \file RenderBuffer.h
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#pragma once

#include "RenderObject.h"

namespace spank
{

class IRenderer;
class VertexAttributes;

class RenderBuffer : public RenderObject
{
	friend class RendererGl2;

public:
	virtual bool uploadBuffer(const void* bufferData, uint bufferSize) = 0;
	virtual bool reload(bool freeOld);

protected:
	RenderBuffer(IRenderer* pRenderer);
	virtual ~RenderBuffer();

	virtual void preDelete() override;

protected:
	IRenderer* m_pRenderer{ nullptr };

};

class MemRenderBuffer : public RenderBuffer
{
	friend class RendererGl2;

public:
	virtual bool uploadBuffer(const void* bufferData, uint bufferSize) override;

	inline const char* getBufferMemAddr() const { return m_bufferData.data(); };
	inline uint getBufferSize() const { return m_bufferData.size(); };
	inline const VertexAttributes* getVertexAttributes() const { return m_pVertAttrs; };

protected:
	MemRenderBuffer(IRenderer* pRenderer, const VertexAttributes* pVertAttrs);
	virtual ~MemRenderBuffer();

protected:
	const VertexAttributes* m_pVertAttrs{ nullptr };
	BUFFER_DATA m_bufferData;

};

class VMemRenderBuffer : public MemRenderBuffer
{
	friend class RendererGl2;

public:
	virtual bool uploadBuffer(const void* bufferData, uint bufferSize) override;
	virtual bool reload(bool freeOld) override;

	inline GLuint getBufferId() const { return m_bufferId; };

protected:
	VMemRenderBuffer(IRenderer* pRenderer, const VertexAttributes* pVertAttrs);
	virtual ~VMemRenderBuffer();

private:
	void destroyVBuffer();
	bool updateVBufferData();

private:
	GLuint m_bufferId{ 0 };

};

}
