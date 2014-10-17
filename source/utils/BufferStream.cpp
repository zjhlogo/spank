/*!
 * \file BufferStream.cpp
 * \date 10-17-2014 13:41:52
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "BufferStream.h"
#include <memory>

namespace spank
{

BufferStream::BufferStream(const BUFFER_DATA& bufferData)
{
	m_pBuffer = bufferData.data();
	m_bufferSize = bufferData.size();
}

BufferStream::~BufferStream()
{
	// TODO: 
}

bool BufferStream::read(void* pDataOut, std::size_t size)
{
	if (!pDataOut || size + m_readPos > m_bufferSize) return false;
	if (size <= 0) return true;

	memcpy(pDataOut, m_pBuffer+m_readPos, size);
	m_readPos += size;

	return true;
}

bool BufferStream::skip(int size)
{
	if (size + m_readPos > m_bufferSize) return false;
	m_readPos += size;
	return true;
}

}
