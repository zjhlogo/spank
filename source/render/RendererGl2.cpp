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
	// TODO: 
	return nullptr;
}

void RendererGl2::clearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
