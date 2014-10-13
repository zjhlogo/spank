/*!
 * \file RendererGl2.cpp
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#include "RendererGl2.h"
#include <GLES2/gl2.h>
#include "../utils/LogUtil.h"

RendererGl2::RendererGl2()
{

}

RendererGl2::~RendererGl2()
{

}

bool RendererGl2::initialize()
{
	LOGI("Version: %s", glGetString(GL_VERSION));
	LOGI("Vendor: %s", glGetString(GL_VENDOR));
	LOGI("Renderer: %s", glGetString(GL_RENDERER));
	LOGI("Extensions: %s", glGetString(GL_EXTENSIONS));

	return true;
}

void RendererGl2::terminate()
{
	// TODO: 
}
Texture* RendererGl2::createTexture(const std::string& filePath)
{
	Texture* pTexture = new Texture();
	if (!pTexture->loadFromFile(filePath))
	{
		SAFE_DELETE(pTexture);
		return nullptr;
	}

	return pTexture;
}

Shader* RendererGl2::createShader(const std::string& vertexShaderFile, const std::string& fragShaderFile)
{
	Shader* pShader = new Shader();
	if (!pShader->loadFromFile(vertexShaderFile, fragShaderFile))
	{
		SAFE_DELETE(pShader);
		return nullptr;
	}

	return pShader;
}

VMemRenderBuffer* RendererGl2::createVMemRenderBuffer()
{
	VMemRenderBuffer* pRenderBuffer = new VMemRenderBuffer();
	if (!pRenderBuffer->createBufferObject())
	{
		SAFE_DELETE(pRenderBuffer);
		return nullptr;
	}

	return pRenderBuffer;
}
