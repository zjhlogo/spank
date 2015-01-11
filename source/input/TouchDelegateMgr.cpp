/*!
 * \file TouchDelegateMgr.cpp
 * \date 10-16-2014 9:31:29
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "TouchDelegateMgr.h"
#include <algorithm>
#include "../utils/LogUtil.h"

namespace spank
{

TouchDelegateMgr::TouchDelegateMgr()
{
	// TODO: 
}

TouchDelegateMgr::~TouchDelegateMgr()
{
	// TODO: 
}

bool TouchDelegateMgr::initialize()
{
	return true;
}

void TouchDelegateMgr::terminate()
{

}

bool TouchDelegateMgr::addDelegate(ITouchDelegate* pDelegate)
{
	auto it = std::find(m_vTouchDelegate.begin(), m_vTouchDelegate.end(), pDelegate);
	if (it != m_vTouchDelegate.end()) return false;

	m_vTouchDelegate.push_back(pDelegate);
	return true;
}

bool TouchDelegateMgr::removeDelegate(ITouchDelegate* pDelegate)
{
	auto it = std::find(m_vTouchDelegate.begin(), m_vTouchDelegate.end(), pDelegate);
	if (it != m_vTouchDelegate.end())
	{
		m_vTouchDelegate.erase(it);
		return true;
	}

	return false;
}

void TouchDelegateMgr::handleTouchEvent(ITouchDelegate::ACTION_TYPE_ID eActionType, const glm::vec2& touchPos)
{
	LOGI("touch, type=%d, (%f,%f)", eActionType, touchPos.x, touchPos.y);

	for (auto delegate : m_vTouchDelegate)
	{
		delegate->onTouchEvent(eActionType, touchPos);
	}
}

void TouchDelegateMgr::handleZoomEvent(float zoom)
{
	LOGI("zoom, %f", zoom);

	for (auto delegate : m_vTouchDelegate)
	{
		delegate->onZoomEvent(zoom);
	}
}

}
