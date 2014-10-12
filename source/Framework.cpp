/*!
 * \file Framework.cpp
 * \date 10-10-2014 11:44:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Framework.h"
#include "render/RendererGl3.h"

Framework::Framework()
{

}

Framework::~Framework()
{

}

bool Framework::initialize()
{
	m_pRenderer = new RendererGl3();
	if (!m_pRenderer->initialize()) return false;

	return true;
}

void Framework::terminate()
{
	if (m_pRenderer) m_pRenderer->terminate();
	SAFE_DELETE(m_pRenderer);
}
