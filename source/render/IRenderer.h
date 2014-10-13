/*!
 * \file IRenderer.h
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#pragma once

#include "../base/IMgr.h"
#include "Texture.h"

class IRenderer : public IMgr
{
public:
	IRenderer();
	virtual ~IRenderer();

	virtual Texture* createTexture(const std::string& filePath) = 0;

	virtual void clearColor(float r, float g, float b, float a) = 0;
};
