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

class Texture : public RenderObject
{
public:
	Texture();
	virtual ~Texture();

	bool loadFromFile(const std::string& filePath);
	inline uint getTextureId() const { return m_textureId; };

private:
	GLuint m_textureId{ 0 };

};
