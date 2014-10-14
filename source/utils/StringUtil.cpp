/*!
 * \file StringUtil.cpp
 * \date 10-14-2014 13:56:16
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "StringUtil.h"

std::string StringUtil::getFileDir(const std::string& strIn)
{
	std::string strDir;
	size_t nPosEnd = strIn.find_last_of("/\\");

	if (nPosEnd == std::string::npos) return strDir;

	return strIn.substr(0, nPosEnd);
}
