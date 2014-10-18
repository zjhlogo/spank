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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

HelloGLES3App::HelloGLES3App()
{
	// TODO: 
}

HelloGLES3App::~HelloGLES3App()
{

}

bool HelloGLES3App::initialize()
{
	spank::IRenderer* pRenderer = getRenderer();

	m_pShader = pRenderer->createShader("data/shaders/pos3_uv2.shader");
	if (!m_pShader) return false;

	m_pTexture = pRenderer->createTexture("data/test.png");
	if (!m_pTexture) return false;

	m_pMemVertexBuffer = pRenderer->createMemVertexBuffer(m_pShader->getVertexAttributes());
	if (!m_pMemVertexBuffer) return false;

	m_pVMemVertexBuffer = pRenderer->createVMemVertexBuffer(m_pShader->getVertexAttributes());
	if (!m_pVMemVertexBuffer) return false;

	GLfloat vertAttribs[] = { -0.4f, -0.4f, 0.0f, // Pos
		0.0f, 0.0f,	  // UVs
		0.4f, -0.4f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.4f, 0.0f,
		0.5f, 1.0f };

	m_pMemVertexBuffer->uploadBuffer(vertAttribs, sizeof(vertAttribs));
	m_pVMemVertexBuffer->uploadBuffer(vertAttribs, sizeof(vertAttribs));

	return true;
}

void HelloGLES3App::terminate()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pShader);
	SAFE_RELEASE(m_pMemVertexBuffer);
	SAFE_RELEASE(m_pVMemVertexBuffer);
}

void HelloGLES3App::update(float dt)
{
	m_rot += dt;
	if (m_rot > glm::pi<float>()*2.0f) m_rot -= glm::pi<float>()*2.0f;
}

void HelloGLES3App::render()
{
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glm::quat quaRot = glm::angleAxis(m_rot, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 matRot = glm::mat4_cast(quaRot);

	m_pShader->useProgram();
	m_pShader->setMatrix("u_matMVP", matRot);
	m_pShader->setTexture(m_pTexture, 0);
	m_pShader->drawArrays(m_pVMemVertexBuffer, 0, 3);
}
