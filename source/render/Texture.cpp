/*!
 * \file Texture.cpp
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#include "Texture.h"
#include "IRenderer.h"
#include "../utils/StringUtil.h"
#include "../utils/LogUtil.h"

namespace spank
{

Texture::Texture(IRenderer* pRenderer)
	: m_pRenderer(pRenderer)
{

}

Texture::~Texture()
{
	destroyTexture();
}

bool Texture::loadFromFile(const tstring& filePath)
{
	if (m_textureId != 0) return false;

	m_eImageFileType = ImageUtil::getImageFileType(filePath);
	if (m_eImageFileType == ImageUtil::IFT_UNKNOWN)
	{
		LOGE("Unknown image type %s", filePath.c_str());
		return false;
	}

	m_textureId = ImageUtil::decodeImage(m_eImageFileType, filePath);
	if (m_textureId != 0)
	{
		setId(filePath);
		return true;
	}

	LOGE("Load texture failed %s", filePath.c_str());
	return false;
}

bool Texture::reload(bool freeOld)
{
	if (freeOld) destroyTexture();

	const tstring& filePath = getId();
	m_textureId = ImageUtil::decodeImage(m_eImageFileType, filePath);
	if (m_textureId != 0) return true;

	return false;
}

void Texture::destroyTexture()
{
	if (m_textureId != 0)
	{
		glDeleteTextures(1, &m_textureId);
		m_textureId = 0;
	}
}

void Texture::preDelete()
{
	m_pRenderer->removeTexture(this);
}

}
