/*!
 * \file RendererGl2.h
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#pragma once

#include "IRenderer.h"

class RendererGl2 : public IRenderer
{
public:
	RendererGl2();
	virtual ~RendererGl2();

	bool initialize() override;
	void terminate() override;

	virtual Texture* createTexture(const std::string& filePath) override;

	virtual void clearColor(float r, float g, float b, float a) override;

};