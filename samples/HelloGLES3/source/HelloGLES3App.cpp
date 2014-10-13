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
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pRenderBuffer);
}

bool HelloGLES3App::initialize(Framework* pFramework)
{
	BUFFER_DATA buffer;
	if (!FileUtil::readFile(buffer, "data/grid16.png")) return false;

	IRenderer* pRenderer = getRenderer();

	m_pShader = pRenderer->createShader("data/image.vsh", "data/image.fsh");
	if (!m_pShader) return false;

	m_pTexture = pRenderer->createTexture("data/image.pvr");
	if (!m_pTexture) return false;

	m_pRenderBuffer = pRenderer->createVMemRenderBuffer();
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
	// TODO: throw std::exception("The method or operation is not implemented.");
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

	m_pShader->useShader();
	m_pShader->setMatrix("myPMVMatrix", afIdentity);
	m_pShader->setTexture("sampler2d", m_pTexture);

	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_pRenderBuffer->getBufferId());

	// Pass the vertex data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, 0);

	// Pass the texture coordinates data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)(3 * sizeof(GLfloat)));

	// Draws a non-indexed triangle array
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
