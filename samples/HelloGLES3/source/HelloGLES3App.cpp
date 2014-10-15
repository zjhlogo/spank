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

bool HelloGLES3App::initialize(spank::Framework* pFramework)
{
	spank::IRenderer* pRenderer = getRenderer();

	m_pShader = pRenderer->createShader("data/shaders/pos3_uv2.shader");
	if (!m_pShader) return false;

	m_pTexture = pRenderer->createTexture("data/image.pvr");
	if (!m_pTexture) return false;

	m_pRenderBufferMem = pRenderer->createMemRenderBuffer(m_pShader->getVertexAttributes());
	if (!m_pRenderBufferMem) return false;

	m_pRenderBufferVMem = pRenderer->createVMemRenderBuffer(m_pShader->getVertexAttributes());
	if (!m_pRenderBufferVMem) return false;

	GLfloat vertAttribs[] = { -0.4f, -0.4f, 0.0f, // Pos
		0.0f, 0.0f,	  // UVs
		0.4f, -0.4f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.4f, 0.0f,
		0.5f, 1.0f };

	m_pRenderBufferMem->uploadBuffer(vertAttribs, sizeof(vertAttribs));
	m_pRenderBufferVMem->uploadBuffer(vertAttribs, sizeof(vertAttribs));

	return true;
}

void HelloGLES3App::terminate()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pShader);
	SAFE_RELEASE(m_pRenderBufferMem);
	SAFE_RELEASE(m_pRenderBufferVMem);
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
	m_pShader->setTexture(m_pTexture, 0);
	m_pShader->drawArrays(m_pRenderBufferVMem, 0, 3);
}
