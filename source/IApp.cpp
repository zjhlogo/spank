/*!
 * \file IApp.cpp
 * \date 10-10-2014 14:00:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "IApp.h"
#include "utils/TimeUtil.h"
#include <algorithm>

namespace spank
{

IApp::IApp()
{
	// TODO: 
}

IApp::~IApp()
{
	// TODO: 
}

void IApp::step()
{
	m_lastTime = m_currTime;
	m_currTime = TimeUtil::getNowTime();
	m_frameTime = std::max(m_currTime - m_lastTime, 0) / 1000.0f;

	update(m_frameTime);
	render();
}

}
