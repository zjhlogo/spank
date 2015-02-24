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

	typedef struct TEXTURE_INFO_tag
	{
		GLuint textureId{ 0 };
		int width{ 0 };
		int height{ 0 };
	} TEXTURE_INFO;

public:
	static IMAGE_FILE_TYPE getImageFileType(const tstring& filePath);
	static bool decodeImage(TEXTURE_INFO& textureInfo, IMAGE_FILE_TYPE eImageFileType, const tstring& filePath);
	static bool createTextureFromRawData(TEXTURE_INFO& textureInfo, int width, int height, int channels, const BUFFER_DATA& bufferData);

private:
	static bool decodePngImage(TEXTURE_INFO& textureInfo, const tstring& filePath);

};

}
