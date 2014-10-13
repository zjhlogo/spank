/*!
 * \file RendererGl3.h
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#pragma once

#include "IRenderer.h"

class RendererGl3 : public IRenderer
{
public:
	RendererGl3();
	virtual ~RendererGl3();

	bool initialize() override;
	void terminate() override;

	virtual Texture* createTexture(const std::string& filePath) override;

	virtual void clearColor(float r, float g, float b, float a) override;

};