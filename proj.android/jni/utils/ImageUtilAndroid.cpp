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

bool ImageUtil::decodeImage(TEXTURE_INFO& textureInfo, IMAGE_FILE_TYPE eImageFileType, const tstring& filePath)
{
	bool result = false;

	switch (eImageFileType)
	{
	case ImageUtil::IFT_PNG:
		result = decodePngImage(textureInfo, filePath);
		break;
	case ImageUtil::IFT_PVR:
		result = (PVRTTextureLoadFromPVR(filePath.c_str(), &textureInfo.textureId) == PVR_SUCCESS);
		break;
	default:
		break;
	}

	return result;
}

}
