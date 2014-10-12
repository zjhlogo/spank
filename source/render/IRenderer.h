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
#include "RenderTarget.h"

class IRenderer : public IMgr
{
public:
	IRenderer();
	virtual ~IRenderer();

	virtual RenderTarget* getRenderTarget() = 0;
	virtual bool setRenderTarget(RenderTarget* pRenderTarget) = 0;

	virtual void clearColor(float r, float g, float b, float a) = 0;
};
