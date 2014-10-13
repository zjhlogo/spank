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
#include "Shader.h"
#include "RenderBuffer.h"

class IRenderer : public IMgr
{
public:
	IRenderer();
	virtual ~IRenderer();

	virtual Texture* createTexture(const std::string& filePath) = 0;
	virtual Shader* createShader(const std::string& vertexShaderFile, const std::string&  fragShaderFile) = 0;
	virtual VMemRenderBuffer* createVMemRenderBuffer() = 0;

};
