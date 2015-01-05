/*!
 * \file MandelbrotApp.cpp
 * \date 10-10-2014 14:04:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "MandelbrotApp.h"
#include <utils/LogUtil.h>
#include <utils/FileUtil.h>
#include <utils/StringBuilder.h>
#include <render/VertexAttributes.h>

MandelbrotApp::MandelbrotApp()
{
	// TODO: 
}

MandelbrotApp::~MandelbrotApp()
{

}

bool MandelbrotApp::initialize()
{
	if (!BaseApp::initialize()) return false;

	spank::IRenderer* pRenderer = getRenderer();

	m_pShader = pRenderer->createShader("data/shaders/mandelbrot.shader");
	if (!m_pShader) return false;

	createRenderBuffer(pRenderer);

	return true;
}

void MandelbrotApp::terminate()
{
	SAFE_RELEASE(m_pVMemVertexBuffer);
	SAFE_RELEASE(m_pVMemIndexBuffer);
	SAFE_RELEASE(m_pShader);
	BaseApp::terminate();
}

void MandelbrotApp::update(float dt)
{
	updateFPS(dt);
}

void MandelbrotApp::render()
{
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const glm::mat4& matMVP = getRenderer()->getOrthoMatrix();

	m_pShader->useProgram();
	m_pShader->setUniform("u_matMVP", matMVP);
	m_pShader->setUniform("u_maxIterations", 128.0f);
	m_pShader->setUniform("u_zoom", 0.005f);
	m_pShader->setUniform("u_centerPos", glm::vec2(0.0, 0.0));

	m_pShader->drawBuffer(m_pVMemVertexBuffer, m_pVMemIndexBuffer);

	renderFPS();
}

void MandelbrotApp::createRenderBuffer(spank::IRenderer* pRenderer)
{
	m_pVMemVertexBuffer = pRenderer->createVMemVertexBuffer(m_pShader->getVertexAttributes());
	if (!m_pVMemVertexBuffer) return;

	m_pVMemIndexBuffer = pRenderer->createVMemIndexBuffer();
	if (!m_pVMemIndexBuffer) return;

	const glm::vec2& surfaceSize = pRenderer->getSurfaceSize();
	spank::VERT_ATTR_POS3 verts[] =
	{
		 // front
		-0.5f*surfaceSize.x, -0.5f*surfaceSize.y, 0.0f,
		-0.5f*surfaceSize.x,  0.5f*surfaceSize.y, 0.0f,
		 0.5f*surfaceSize.x,  0.5f*surfaceSize.y, 0.0f,
		 0.5f*surfaceSize.x, -0.5f*surfaceSize.y, 0.0f,
	};

	m_pVMemVertexBuffer->uploadBuffer(verts, sizeof(verts));

	glm::uint16 indis[] = { 0, 1, 3, 1, 2, 3 };
	m_pVMemIndexBuffer->uploadBuffer(indis,  sizeof(indis));
}
