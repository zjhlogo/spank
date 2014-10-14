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

}

bool HelloGLES3App::initialize(Framework* pFramework)
{
	IRenderer* pRenderer = getRenderer();

	m_pShader = pRenderer->createShader("data/shaders/pos3_uv2.shader");
	if (!m_pShader) return false;

	m_pTexture = pRenderer->createTexture("data/image.pvr");
	if (!m_pTexture) return false;

	m_pRenderBuffer = pRenderer->createVMemRenderBuffer(m_pShader->getVertexAttributes());
	if (!m_pRenderBuffer) return false;

	GLfloat vertAttribs[] = { -0.4f, -0.4f, 0.0f, // Pos
		0.0f, 0.0f,	  // UVs
		0.4f, -0.4f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.4f, 0.0f,
		0.5f, 1.0f };
	m_pRenderBuffer->uploadBuffer(vertAttribs, sizeof(vertAttribs));

	return true;
}

void HelloGLES3App::terminate()
{
	IRenderer* pRenderer = getRenderer();

	pRenderer->releaseTexture(m_pTexture);
	m_pTexture = nullptr;

	pRenderer->releaseShader(m_pShader);
	m_pShader = nullptr;

	pRenderer->releaseVMemRenderBuffer(m_pRenderBuffer);
	m_pRenderBuffer = nullptr;
}

void HelloGLES3App::update(float dt)
{
	// TODO: throw std::exception("The method or operation is not implemented.");
}

void HelloGLES3App::render()
{
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Matrix used for projection model view
	float afIdentity[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	m_pShader->useProgram();
	m_pShader->setMatrix("u_matMVP", afIdentity);
	m_pShader->setTexture("u_texture", m_pTexture);
	m_pShader->drawArrays(m_pRenderBuffer, 0, 3);
}
