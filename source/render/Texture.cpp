/*!
 * \file Texture.cpp
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#include "Texture.h"
#include <GLES3/gl3.h>
#include <libPvr/source/PVRTTextureAPI.h>

Texture::Texture()
{

}

Texture::~Texture()
{

}

bool Texture::loadFromFile(const std::string& filePath)
{
	uint uiTexture = 0;
	PVRTTextureLoadFromPVR(filePath.c_str(), &uiTexture);

	return true;
}
