/*!
 * \file HelloGLESApp.cpp
 * \date 10-10-2014 14:04:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "HelloGLESApp.h"
#include <utils/LogUtil.h>
#include <utils/FileUtil.h>
#include <utils/StringBuilder.h>
#include <render/VertexAttributes.h>

HelloGLESApp::HelloGLESApp()
{
	// TODO: 
}

HelloGLESApp::~HelloGLESApp()
{

}

bool HelloGLESApp::initialize()
{
	if (!BaseApp::initialize()) return false;

	spank::IRenderer* pRenderer = getRenderer();

	m_pShader = pRenderer->createShader("data/shaders/pos3_uv2.shader");
	if (!m_pShader) return false;

	m_pTexture = pRenderer->createTexture("data/test.png");
	if (!m_pTexture) return false;

	createRenderBuffer(pRenderer);

	return true;
}

void HelloGLESApp::terminate()
{
	SAFE_RELEASE(m_pVMemVertexBuffer);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pShader);
	BaseApp::terminate();
}

void HelloGLESApp::update(float dt)
{
	updateFPS(dt);

	m_rot += dt;
	if (m_rot > glm::pi<float>()*2.0f) m_rot -= glm::pi<float>()*2.0f;
}

void HelloGLESApp::render()
{
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::quat quaRot = glm::angleAxis(m_rot, glm::normalize(glm::vec3(0.3f, 1.0f, 0.7f)));
	glm::mat4 matRot = glm::mat4_cast(quaRot);
	glm::mat4 matView = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 matMVP = getRenderer()->getPerspectiveMatrix() * matView * matRot;

	m_pShader->useProgram();
	m_pShader->setUniform("u_matMVP", matMVP);
	m_pShader->setTexture(m_pTexture, 0);
	m_pShader->drawBuffer(m_pVMemVertexBuffer, 0, 36);

	renderFPS();
}

void HelloGLESApp::createRenderBuffer(spank::IRenderer* pRenderer)
{
	m_pVMemVertexBuffer = pRenderer->createVMemVertexBuffer(m_pShader->getVertexAttributes());
	if (!m_pVMemVertexBuffer) return;

	spank::VERT_ATTR_POS3_UV2 verts[] =
	{
		 // front
		-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

		 // top
		-1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f, 0.0f,

		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f, 0.0f,

		 // back
		-1.0f,  1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f, 0.0f,

		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f, 0.0f,

		 // bottom
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

		-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

		 // left
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

		 // right
		 1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

		 1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
	};

	m_pVMemVertexBuffer->uploadBuffer(verts, sizeof(verts));
}
