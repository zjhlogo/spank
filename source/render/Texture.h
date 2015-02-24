/*!
 * \file Texture.h
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#pragma once

#include "RenderObject.h"
#include "../utils/ImageUtil.h"

namespace spank
{

class IRenderer;

class Texture : public RenderObject
{
	friend class RendererGl2;

public:
	bool loadFromFile(const tstring& filePath);
	bool reload(bool freeOld);

	inline uint getTextureId() const { return m_textureId; };
	inline int getWidth() const{ return m_width; };
	inline int getHeight() const{ return m_height; };

protected:
	Texture(IRenderer* pRenderer);
	virtual ~Texture();

	virtual void preDelete() override;

private:
	void destroyTexture();

private:
	ImageUtil::IMAGE_FILE_TYPE m_eImageFileType{ ImageUtil::IFT_UNKNOWN };
	GLuint m_textureId{ 0 };
	int m_width{ 0 };
	int m_height{ 0 };
	IRenderer* m_pRenderer{ nullptr };

};

}
