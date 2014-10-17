/*!
 * \file ImageUtil.h
 * \date 10-17-2014 13:13:10
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "../base/PlatformDefine.h"
#include <GLES2/gl2.h>

namespace spank
{

class ImageUtil
{
public:
	enum IMAGE_FILE_TYPE
	{
		IFT_UNKNOWN = 0,
		IFT_PNG,
		IFT_PVR,
	};

public:
	static IMAGE_FILE_TYPE getImageFileType(const std::string& filePath);
	static GLuint decodeImage(IMAGE_FILE_TYPE eImageFileType, const std::string& filePath);
	static GLuint createTextureFromRawData(int width, int height, const BUFFER_DATA& bufferData);

private:
	static GLuint decodePngImage(const std::string& filePath);

};

}
