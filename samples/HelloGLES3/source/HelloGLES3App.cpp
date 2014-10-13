/*!
 * \file HelloGLES3App.cpp
 * \date 10-10-2014 14:04:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "HelloGLES3App.h"
#include <utils/LogUtil.h>
#include <utils/FileUtil.h>

HelloGLES3App::HelloGLES3App()
{
	// TODO: 
}

HelloGLES3App::~HelloGLES3App()
{
	// TODO: 
}

bool HelloGLES3App::initialize(Framework* pFramework)
{
	BUFFER_DATA buffer;
	if (!FileUtil::readFile(buffer, "data/grid16.png")) return false;

	IRenderer* pRenderer = getRenderer();
	Texture* pTexture = pRenderer->createTexture("data/image.pvr");

	return true;
}

void HelloGLES3App::terminate()
{
	// TODO: throw std::exception("The method or operation is not implemented.");
}

void HelloGLES3App::update(float dt)
{
	// TODO: throw std::exception("The method or operation is not implemented.");
}

void HelloGLES3App::render()
{
	IRenderer* pRenderer = getRenderer();

	pRenderer->clearColor(0.6f, 0.8f, 1.0f, 1.0f);
}
