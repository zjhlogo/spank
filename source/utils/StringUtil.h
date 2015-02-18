/*!
 * \file StringUtil.h
 * \date 10-14-2014 13:56:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "../base/PlatformDefine.h"

namespace spank
{

class StringUtil
{
public:
	static std::string getFileDir(const std::string& strIn);
	static std::string getFileExt(const std::string& strIn);

};

}
