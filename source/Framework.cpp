/*!
 * \file Framework.cpp
 * \date 10-10-2014 11:44:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Framework.h"
#include "render/RendererGl2.h"

namespace spank
{

Framework::Framework()
{

}

Framework::~Framework()
{

}

bool Framework::initialize()
{
	m_pRenderer = new RendererGl2();
	if (!m_pRenderer->initialize()) return false;

	m_pTouchDelegateMgr = new TouchDelegateMgr();
	if (!m_pTouchDelegateMgr->initialize()) return false;

	m_pFontMgr = new FontMgr();
	if (!m_pFontMgr->initialize()) return false;
	m_pFontMgr->setRenderer(m_pRenderer);

	return true;
}

void Framework::terminate()
{
	if (m_pFontMgr) m_pFontMgr->terminate();
	SAFE_DELETE(m_pFontMgr);

	if (m_pTouchDelegateMgr) m_pTouchDelegateMgr->terminate();
	SAFE_DELETE(m_pTouchDelegateMgr);

	if (m_pRenderer) m_pRenderer->terminate();
	SAFE_DELETE(m_pRenderer);
}

}
