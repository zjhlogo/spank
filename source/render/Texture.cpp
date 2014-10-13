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
	glDeleteTextures(1, &m_textureId);
	m_textureId = 0;
}

bool Texture::loadFromFile(const std::string& filePath)
{
	if (m_textureId != 0) return false;

	return (PVRTTextureLoadFromPVR(filePath.c_str(), &m_textureId) == PVR_SUCCESS);
}
