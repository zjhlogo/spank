/*!
 * \file RenderBuffer.cpp
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#include "RenderBuffer.h"

RenderBuffer::RenderBuffer()
{

}

RenderBuffer::~RenderBuffer()
{

}

MemRenderBuffer::MemRenderBuffer()
{

}

MemRenderBuffer::~MemRenderBuffer()
{

}

bool MemRenderBuffer::uploadBuffer(const void* bufferData, uint bufferSize)
{
	// TODO: 
	return false;
}

VMemRenderBuffer::VMemRenderBuffer()
{

}

VMemRenderBuffer::~VMemRenderBuffer()
{
	glDeleteBuffers(1, &m_bufferId);
	m_bufferId = 0;
}

bool VMemRenderBuffer::createBufferObject()
{
	glGenBuffers(1, &m_bufferId);
	if (m_bufferId == 0) return false;

	return true;
}

bool VMemRenderBuffer::uploadBuffer(const void* bufferData, uint bufferSize)
{
	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);

	// Set the buffer's data
	glBufferData(GL_ARRAY_BUFFER, bufferSize, bufferData, GL_STATIC_DRAW);

	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}
