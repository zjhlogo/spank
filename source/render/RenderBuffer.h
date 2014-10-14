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

class VertexAttributes;

class RenderBuffer : public RenderObject
{
public:
	RenderBuffer();
	virtual ~RenderBuffer();

	virtual bool uploadBuffer(const void* bufferData, uint bufferSize) = 0;
	virtual bool reload(bool freeOld) = 0;

};

class MemRenderBuffer : public RenderBuffer
{
public:
	MemRenderBuffer();
	virtual ~MemRenderBuffer();

	virtual bool uploadBuffer(const void* bufferData, uint bufferSize) override;
	virtual bool reload(bool freeOld) override;

};

class VMemRenderBuffer : public RenderBuffer
{
public:
	VMemRenderBuffer(const VertexAttributes* pVertAttrs);
	virtual ~VMemRenderBuffer();

	bool createBufferObject();
	inline GLuint getBufferId() const { return m_bufferId; };

	virtual bool uploadBuffer(const void* bufferData, uint bufferSize) override;
	virtual bool reload(bool freeOld) override;

	inline const VertexAttributes* getVertexAttributes() const { return m_pVertAttrs; };
	inline uint getBufferSize() const { return m_bufferData.size(); };

private:
	void destroyBuffer();
	bool updateData();

private:
	GLuint m_bufferId{ 0 };
	const VertexAttributes* m_pVertAttrs{ nullptr };
	BUFFER_DATA m_bufferData;

};