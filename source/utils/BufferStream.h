/*!
 * \file BufferStream.h
 * \date 10-17-2014 13:41:43
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "../base/PlatformDefine.h"

namespace spank
{

class BufferStream
{
public:
	BufferStream(const BUFFER_DATA& bufferData);
	virtual ~BufferStream();

	bool read(void* pDataOut, std::size_t size);
	bool skip(int size);

	inline void reset() { m_readPos = 0; };
	inline std::size_t getSize() const { return m_bufferSize; };
	inline std::size_t getPosition() const { return m_readPos; };

private:
	const char* m_pBuffer{ nullptr };
	std::size_t m_bufferSize{ 0 };
	std::size_t m_readPos{ 0 };

};

}
