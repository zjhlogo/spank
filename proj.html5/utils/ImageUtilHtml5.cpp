/*!
 * \file ImageUtilHtml5.cpp
 * \date 10-17-2014 16:39:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <utils/ImageUtil.h>
#include <utils/LogUtil.h>

#include <libPvr/source/PVRTTextureAPI.h>
#include <SDL/SDL_image.h>

namespace spank
{

// Flip the image data vertically.
static void flipVertical(BUFFER_DATA& bufferData, const char* pixel, int w, int h, int bpp)
{
	bufferData.resize(w*h*bpp);
	for (int y = 0; y < h; ++y)
	{
		memcpy(bufferData.data() + (h - y - 1)*w*bpp, pixel + (y*w*bpp), w*bpp);
	}
}

static bool decodeImageBySdl(ImageUtil::TEXTURE_INFO& textureInfo, const std::string& filePath)
{
	SDL_Surface* pSdlSurface = IMG_Load(filePath.c_str());
	if (!pSdlSurface)
	{
		LOGE("Decode image using IMG_Load failed %s", filePath.c_str());
		return false;
	}

	int w = pSdlSurface->w;
	int h = pSdlSurface->h;
	int bpp = pSdlSurface->format->BytesPerPixel;
	LOGI("Image %s decode info w=%d, h=%d, bpp=%d", filePath.c_str(), w, h, bpp);

	GLint glFormat = GL_ALPHA;
	switch (bpp)
	{
	case 1:
		glFormat = GL_ALPHA;
		break;
	case 3:
		glFormat = GL_RGB;
		break;
	case 4:
		glFormat = GL_RGBA;
		break;
	default:
		SDL_FreeSurface(pSdlSurface);
		return false;
		break;
	}

	BUFFER_DATA bufferData;
	flipVertical(bufferData, (const char*)pSdlSurface->pixels, w, h, bpp);
	SDL_FreeSurface(pSdlSurface);

	GLuint textureId = 0;
	glGenTextures(1, &textureId);
	if (textureId == 0)
	{
		LOGE("Decode image using IMG_Load failed, can not generate texture %s", filePath.c_str());
		SDL_FreeSurface(pSdlSurface);
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, w, h, 0, glFormat, GL_UNSIGNED_BYTE, bufferData.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	textureInfo.textureId = textureId;
	textureInfo.width = w;
	textureInfo.height = h;

	return true;
}

bool ImageUtil::decodeImage(TEXTURE_INFO& textureInfo, IMAGE_FILE_TYPE eImageFileType, const tstring& filePath)
{
	bool result = false;

	switch (eImageFileType)
	{
	case ImageUtil::IFT_PNG:
		result = decodeImageBySdl(textureInfo, filePath);
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
