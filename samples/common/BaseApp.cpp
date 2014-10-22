/*!
 * \file BaseApp.cpp
 * \date 10-22-2014 18:58:36
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "BaseApp.h"
#include <utils/StringBuilder.h>

BaseApp::BaseApp()
{
	// TODO: 
}

BaseApp::~BaseApp()
{
	// TODO: 
}

bool BaseApp::initialize()
{
	spank::IRenderer* pRenderer = getRenderer();

	spank::FontMgr* pFontMgr = getFramework()->getFontMgr();
	spank::IFont* pFont = pFontMgr->createFont("data/12px_Tahoma.xml");
	if (!pFont) return false;

	m_pLblFPS = new spank::Label(pRenderer, pFont);
	if (!m_pLblFPS) return false;
	m_pLblFPS->setPos(-pRenderer->getSurfaceSize()*0.5f);

	return true;
}

void BaseApp::terminate()
{
	SAFE_DELETE(m_pLblFPS);
}

void BaseApp::updateFPS(float dt)
{
	m_elapseTime += dt;
	if (m_elapseTime > 1.0f)
	{
		m_elapseTime -= 1.0f;
		m_pLblFPS->setText(spank::StringBuilder::format("FPS: #0").add(m_fps).build());
		m_fps = 0;
	}

	++m_fps;
}

void BaseApp::renderFPS()
{
	m_pLblFPS->render();
}
