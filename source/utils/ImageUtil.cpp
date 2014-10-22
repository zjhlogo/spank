/*!
 * \file ImageUtil.cpp
 * \date 10-17-2014 13:16:09
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ImageUtil.h"
#include "StringUtil.h"
#include "FileUtil.h"
#include "LogUtil.h"
#include "BufferStream.h"
#include <libPng/source/png.h>

namespace spank
{

ImageUtil::IMAGE_FILE_TYPE spank::ImageUtil::getImageFileType(const std::string& filePath)
{
	std::string strExt = StringUtil::getFileExt(filePath);
	if (strExt == "png") return IFT_PNG;
	if (strExt == "pvr") return IFT_PVR;
	return IFT_UNKNOWN;
}

static void FuncReaderCallback(png_structp pPngStruct, png_bytep pData, png_size_t nSize)
{
	BufferStream* pBufferStream = (BufferStream*)png_get_io_ptr(pPngStruct);

	if (!pBufferStream->read(pData, nSize))
	{
		png_error(pPngStruct, "FuncReaderCallback failed");
	}
}

GLuint ImageUtil::decodePngImage(const std::string& filePath)
{
	BUFFER_DATA fileBuffer;
	if (!FileUtil::readFile(fileBuffer, filePath))
	{
		LOGE("Decode png file failed, can not read file %s", filePath.c_str());
		return 0;
	}

	png_sig_cmp((png_const_bytep)fileBuffer.data(), 0, 8);

	png_structp pPngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop pPngInfo = png_create_info_struct(pPngStruct);
	if (setjmp(png_jmpbuf(pPngStruct)))
	{
		LOGE("Decode png file failed, error on setjmp");
		return 0;
	}

	BufferStream bufferStream(fileBuffer);

	// define our own callback function for I/O instead of reading from a file
	png_set_read_fn(pPngStruct, &bufferStream, FuncReaderCallback);

	png_read_info(pPngStruct, pPngInfo);
	int width = png_get_image_width(pPngStruct, pPngInfo);
	int height = png_get_image_height(pPngStruct, pPngInfo);
	// can be PNG_COLOR_TYPE_RGB, PNG_COLOR_TYPE_PALETTE, ...
	png_byte nColorType = png_get_color_type(pPngStruct, pPngInfo);
	int bpp = png_get_bit_depth(pPngStruct, pPngInfo);
	int channels = png_get_channels(pPngStruct, pPngInfo);

	// convert stuff to appropriate formats!
	if (nColorType == PNG_COLOR_TYPE_PALETTE)
	{
		png_set_packing(pPngStruct);
		// expand data to 24-bit RGB or 32-bit RGBA if alpha available
		png_set_palette_to_rgb(pPngStruct);
	}

	// expand data to 24-bit RGB or 32-bit RGBA if alpha available
	if (nColorType == PNG_COLOR_TYPE_GRAY && bpp < 8) png_set_expand_gray_1_2_4_to_8(pPngStruct);
	if (nColorType == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(pPngStruct);
	if (bpp == 16) png_set_strip_16(pPngStruct);

	// expand paletted or RGB images with transparency to full alpha channels so the data will be available as RGBA quartets.
	if (png_get_valid(pPngStruct, pPngInfo, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(pPngStruct);

	BUFFER_DATA imagePixel;
	imagePixel.resize(width * height * channels);

	// read image data into pRowPointers
	std::vector<char*> rowPointer;
	rowPointer.resize(height);
	for (int y = 0; y < height; y++)
	{
		rowPointer[y] = imagePixel.data() + (height - y - 1) * width * channels;		//each pixel(RGBA) has 4 bytes
	}
	png_read_image(pPngStruct, (png_bytepp)rowPointer.data());

	// free the stream object and png structure
	png_destroy_read_struct(&pPngStruct, &pPngInfo, NULL);

	return createTextureFromRawData(width, height, channels, imagePixel);
}

GLuint ImageUtil::createTextureFromRawData(int width, int height, int channels, const BUFFER_DATA& bufferData)
{
	GLint glFormat = GL_ALPHA;
	switch (channels)
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
		return 0;
		break;
	}

	GLuint textureId = 0;
	glGenTextures(1, &textureId);
	if (textureId == 0) return 0;

	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, bufferData.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	return textureId;
}

}
