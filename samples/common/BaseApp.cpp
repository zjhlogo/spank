/*!
 * \file BaseApp.cpp
 * \date 10-22-2014 18:58:36
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "BaseApp.h"
#include <utils/StringBuilder.h>

void BaseAppTouchDelegate::onTouchEvent(spank::ITouchDelegate::ACTION_TYPE_ID eActionType, const glm::vec2& touchPos)
{
	m_pBaseApp->onTouchEvent(eActionType, touchPos);
}

void BaseAppTouchDelegate::onZoomEvent(float zoom)
{
	m_pBaseApp->onZoomEvent(zoom);
}

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
	m_pLblFPS->setPos(-pRenderer->getSurfaceSize()*0.5f + glm::vec2(10.0f, 0.0f));

	m_pBaseAppTouchDelegate = new BaseAppTouchDelegate(this);
	if (!getFramework()->getTouchDelegateMgr()->addDelegate(m_pBaseAppTouchDelegate)) return false;

	return true;
}

void BaseApp::terminate()
{
	getFramework()->getTouchDelegateMgr()->removeDelegate(m_pBaseAppTouchDelegate);
	SAFE_DELETE(m_pBaseAppTouchDelegate);
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
