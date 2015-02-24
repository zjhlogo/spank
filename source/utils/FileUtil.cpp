/*!
 * \file FileUtil.cpp
 * \date 10-14-2014 11:09:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileUtil.h"

namespace spank
{

bool FileUtil::readStringFile(tstring& strOut, const tstring& filePath)
{
	BUFFER_DATA buffer;
	if (!readFile(buffer, filePath)) return false;

	strOut.clear();
	strOut.append(buffer.data(), buffer.size());

	return true;
}

}
