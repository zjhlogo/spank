/*!
 * \file RenderBuffer.cpp
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#include "RenderBuffer.h"
#include "VertexAttributes.h"
#include "../utils/LogUtil.h"

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

bool MemRenderBuffer::reload(bool freeOld)
{
	// TODO: 
	return true;
}

VMemRenderBuffer::VMemRenderBuffer(const VertexAttributes* pVertAttrs)
	:m_pVertAttrs(pVertAttrs)
{

}

VMemRenderBuffer::~VMemRenderBuffer()
{
	destroyBuffer();
}

bool VMemRenderBuffer::createBufferObject()
{
	glGenBuffers(1, &m_bufferId);
	GL_ERROR_CHECK();
	if (m_bufferId == 0) return false;

	return true;
}

bool VMemRenderBuffer::uploadBuffer(const void* bufferData, uint bufferSize)
{
	if (!bufferData || bufferSize == 0) return false;

	m_bufferData.resize(bufferSize);
	memcpy(m_bufferData.data(), bufferData, bufferSize);

	updateData();

	return true;
}

bool VMemRenderBuffer::reload(bool freeOld)
{
	if (freeOld) destroyBuffer();

	glGenBuffers(1, &m_bufferId);
	if (m_bufferId == 0) return false;

	updateData();

	return true;
}

void VMemRenderBuffer::destroyBuffer()
{
	if (m_bufferId != 0)
	{
		glDeleteBuffers(1, &m_bufferId);
		m_bufferId = 0;
	}
}

bool VMemRenderBuffer::updateData()
{
	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
	GL_ERROR_CHECK();

	// Set the buffer's data
	glBufferData(GL_ARRAY_BUFFER, m_bufferData.size(), m_bufferData.data(), GL_STATIC_DRAW);
	GL_ERROR_CHECK();

	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}
