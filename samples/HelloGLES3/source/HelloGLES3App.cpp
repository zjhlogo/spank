/*!
 * \file HelloGLES3App.cpp
 * \date 10-10-2014 14:04:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "HelloGLES3App.h"
#include <utils/LogUtil.h>

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
	LOGD("OpenGLES3TestApp::initialize");

	m_pFramework = pFramework;
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
	IRenderer* pRenderer = m_pFramework->getRenderer();

	pRenderer->clearColor(0.6f, 0.8f, 1.0f, 1.0f);
}
