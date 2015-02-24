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
	m_eImageFileType = ImageUtil::getImageFileType(filePath);
	if (m_eImageFileType == ImageUtil::IFT_UNKNOWN)
	{
		LOGE("Unknown image type %s", filePath.c_str());
		return false;
	}

	setId(filePath);

	return reload(false);
}

bool Texture::reload(bool freeOld)
{
	if (freeOld) destroyTexture();

	const tstring& filePath = getId();

	ImageUtil::TEXTURE_INFO textureInfo;
	if (!ImageUtil::decodeImage(textureInfo, m_eImageFileType, filePath))
	{
		LOGE("Load texture failed %s", filePath.c_str());
		return false;
	}

	m_textureId = textureInfo.textureId;
	m_width = textureInfo.width;
	m_height = textureInfo.height;

	return true;
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
