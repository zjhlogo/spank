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

static GLuint decodeImageBySdl(const std::string& filePath)
{
	SDL_Surface* pSdlSurface = IMG_Load(filePath.c_str());
	if (!pSdlSurface)
	{
		LOGE("Decode image using IMG_Load failed %s", filePath.c_str());
		return 0;
	}

	int w = pSdlSurface->w;
	int h = pSdlSurface->h;

	BUFFER_DATA bufferData;
	flipVertical(bufferData, (const char*)pSdlSurface->pixels, w, h, 4);
	SDL_FreeSurface(pSdlSurface);

	GLuint textureId = 0;
	glGenTextures(1, &textureId);
	if (textureId == 0)
	{
		LOGE("Decode image using IMG_Load failed, can not generate texture %s", filePath.c_str());
		SDL_FreeSurface(pSdlSurface);
		return 0;
	}

	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferData.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureId;
}

GLuint ImageUtil::decodeImage(IMAGE_FILE_TYPE eImageFileType, const std::string& filePath)
{
	GLuint textureId = 0;

	switch (eImageFileType)
	{
	case ImageUtil::IFT_PNG:
		textureId = decodeImageBySdl(filePath);
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
