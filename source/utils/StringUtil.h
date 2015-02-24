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

	static tstring getFileDir(const tstring& strIn);
	static tstring getFileExt(const tstring& strIn);

	static int splitString(TV_STRING& arrOut, const tstring& strIn, const tstring& strSplit);
	static tstring joinString(const TV_STRING& arrIn, const tstring& strSplit, bool reverse = false);
	static int replaceString(tstring& strInOut, const tstring& strSearch, const tstring& strReplace);

};

}
