/*!
 * \file FileUtil.cpp
 * \date 10-14-2014 11:09:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileUtil.h"

bool FileUtil::readStringFile(std::string& strOut, const std::string& filePath)
{
	BUFFER_DATA buffer;
	if (!readFile(buffer, filePath)) return false;

	strOut.clear();
	strOut.append(buffer.data(), buffer.size());

	return true;
}
