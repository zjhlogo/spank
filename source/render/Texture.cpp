/*!
 * \file Texture.cpp
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#include "Texture.h"
#include <libPvr/source/PVRTTextureAPI.h>

Texture::Texture()
{

}

Texture::~Texture()
{
	destroyTexture();
}

bool Texture::loadFromFile(const std::string& filePath)
{
	if (m_textureId != 0) return false;

	if (PVRTTextureLoadFromPVR(filePath.c_str(), &m_textureId) == PVR_SUCCESS)
	{
		setId(filePath);
		return true;
	}

	return false;
}

bool Texture::reload(bool freeOld)
{
	if (freeOld) destroyTexture();

	const std::string& filePath = getId();
	return (PVRTTextureLoadFromPVR(filePath.c_str(), &m_textureId) == PVR_SUCCESS);
}

void Texture::destroyTexture()
{
	if (m_textureId != 0)
	{
		glDeleteTextures(1, &m_textureId);
		m_textureId = 0;
	}
}
