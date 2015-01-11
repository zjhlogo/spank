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

	spank::FontMgr* pFontMgr = getFramework()->getFontMgr();
	spank::IFont* pFont = pFontMgr->createFont("data/12px_Tahoma.xml");
	if (!pFont) return false;

	m_pLblInfo = new spank::Label(pRenderer, pFont);
	if (!m_pLblInfo) return false;
	updateInfo();

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
	m_pShader->setUniform("u_maxIterations", m_fMaxIteration);
	m_pShader->setUniform("u_zoom", m_fZoom);
	m_pShader->setUniform("u_centerPos", m_centerPos);

	m_pShader->drawBuffer(m_pVMemVertexBuffer, m_pVMemIndexBuffer);

	renderInfo();
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

void MandelbrotApp::onTouchEvent(spank::ITouchDelegate::ACTION_TYPE_ID eActionType, const glm::vec2& touchPos)
{
	switch (eActionType)
	{
	case spank::ITouchDelegate::TOUCH_BEGIN:
	{
		m_lastTouchPos = touchPos;
	}
		break;
	case spank::ITouchDelegate::TOUCH_END:
	{
		// TODO: 
	}
		break;
	case spank::ITouchDelegate::TOUCH_MOVE:
	{
		glm::vec2 offset = touchPos - m_lastTouchPos;
		m_lastTouchPos = touchPos;
		const glm::vec2& surfaceSize = getRenderer()->getSurfaceSize();

		m_centerPos.x -= (offset.x * m_fZoom);
		m_centerPos.y += (offset.y * m_fZoom);
	}
		break;
	}

	updateInfo();
}

void MandelbrotApp::onZoomEvent(float zoom)
{
	m_fZoom *= zoom;
	updateInfo();
}

void MandelbrotApp::updateInfo()
{
	std::string text = spank::StringBuilder::format("Touch to move, Pinch to zoom\nMAX ITERATIONS: #0\nZOOM: #1\nCENTER POS: #2, #3").add((int)m_fMaxIteration).add(m_fZoom).add(m_centerPos.x).add(m_centerPos.y).build();
	m_pLblInfo->setText(text);

	glm::vec2 textSize = m_pLblInfo->calcTextSize();
	const glm::vec2& surfaceSize = getRenderer()->getSurfaceSize();

	m_pLblInfo->setPos(glm::vec2(-surfaceSize.x*0.5f, surfaceSize.y*0.5f - textSize.y));
}

void MandelbrotApp::renderInfo()
{
	m_pLblInfo->render();
}
