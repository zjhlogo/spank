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

namespace spank
{

class IRenderer;

class Texture : public RenderObject
{
	friend class RendererGl2;

public:
	bool loadFromFile(const std::string& filePath);
	bool reload(bool freeOld);

	inline uint getTextureId() const { return m_textureId; };

protected:
	Texture(IRenderer* pRenderer);
	virtual ~Texture();

	virtual void preDelete() override;

private:
	void destroyTexture();

private:
	GLuint m_textureId{ 0 };
	IRenderer* m_pRenderer{ nullptr };

};

}
