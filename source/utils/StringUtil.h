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
	static int str2int(const char* pstrIn);
	static std::string int2str(int value);

	static int64 str2int64(const char* pstrIn);
	static std::string int642str(int64 value);

	static float str2float(const char* pstrIn);
	static std::string float2str(float value);

	static double str2double(const char* pstrIn);
	static std::string double2str(double value);

	static std::string getFileDir(const std::string& strIn);
	static std::string getFileExt(const std::string& strIn);

};

}
