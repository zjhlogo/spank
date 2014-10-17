/*!
 * \file ImageUtilAndroid.cpp
 * \date 10-17-2014 16:21:29
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <utils/ImageUtil.h>
#include <libPvr/source/PVRTTextureAPI.h>

namespace spank
{

GLuint ImageUtil::decodeImage(IMAGE_FILE_TYPE eImageFileType, const std::string& filePath)
{
	GLuint textureId = 0;

	switch (eImageFileType)
	{
	case ImageUtil::IFT_PNG:
		textureId = decodePngImage(filePath);
		break;
	case ImageUtil::IFT_PVR:
		PVRTTextureLoadFromPVR(filePath.c_str(), &textureId);
		break;
	default:
		break;
	}

	return textureId;
}

}
