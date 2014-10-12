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

class FileUtil
{
public:
	static bool readFile(BUFFER_DATA& bufferOut, const std::string& filePath);

};
