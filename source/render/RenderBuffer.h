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

class RenderBuffer : public RenderObject
{
public:
	RenderBuffer();
	virtual ~RenderBuffer();

	virtual bool uploadBuffer(const void* bufferData, uint bufferSize) = 0;

};

class MemRenderBuffer : public RenderBuffer
{
public:
	MemRenderBuffer();
	virtual ~MemRenderBuffer();

	virtual bool uploadBuffer(const void* bufferData, uint bufferSize) override;

};

class VMemRenderBuffer : public RenderBuffer
{
public:
	VMemRenderBuffer();
	virtual ~VMemRenderBuffer();

	bool createBufferObject();
	inline GLuint getBufferId() const { return m_bufferId; };

	virtual bool uploadBuffer(const void* bufferData, uint bufferSize) override;

private:
	GLuint m_bufferId{ 0 };

};