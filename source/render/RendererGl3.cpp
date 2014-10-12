/*!
 * \file RendererGl3.cpp
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#include "RendererGl3.h"
#include <GLES3/gl3.h>
#include "../utils/LogUtil.h"

RendererGl3::RendererGl3()
{

}

RendererGl3::~RendererGl3()
{

}

RenderTarget* RendererGl3::getRenderTarget()
{
	// TODO: 
	return nullptr;
}

bool RendererGl3::setRenderTarget(RenderTarget* pRenderTarget)
{
	// TODO: 
	return false;
}

bool RendererGl3::initialize()
{
	LOGI("Version: %s", glGetString(GL_VERSION));
	LOGI("Vendor: %s", glGetString(GL_VENDOR));
	LOGI("Renderer: %s", glGetString(GL_RENDERER));
	LOGI("Extensions: %s", glGetString(GL_EXTENSIONS));

	return true;
}

void RendererGl3::terminate()
{
	// TODO: 
}

void RendererGl3::clearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
