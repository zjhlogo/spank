/*!
 * \file FileUtil.h
 *
 * \author zjhlogo
 * \date 2014/10/12
 *
 * 
 */
#pragma once

#include "../base/PlatformDefine.h"

namespace spank
{

class FileUtil
{
public:
	static bool readFile(BUFFER_DATA& bufferOut, const tstring& filePath);
	static bool readStringFile(tstring& strOut, const tstring& filePath);
};

}
