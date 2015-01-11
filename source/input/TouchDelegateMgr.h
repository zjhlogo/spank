/*!
 * \file TouchDelegateMgr.h
 * \date 10-16-2014 9:18:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "../base/IMgr.h"
#include <glm/glm.hpp>

namespace spank
{

class ITouchDelegate
{
public:
	enum ACTION_TYPE_ID
	{
		TOUCH_UNKNOWN = 0,
		TOUCH_BEGIN,
		TOUCH_END,
		TOUCH_MOVE,
		TOUCH_CANCEL,
	};

public:
	ITouchDelegate() {};
	virtual ~ITouchDelegate() {};

	virtual void onTouchEvent(ACTION_TYPE_ID eActionType, const glm::vec2& touchPos) = 0;
	virtual void onZoomEvent(float zoom) = 0;

};

class TouchDelegateMgr : public IMgr
{
public:
	typedef std::vector<ITouchDelegate*> TV_TOUCH_DELEGATE;

public:
	TouchDelegateMgr();
	virtual ~TouchDelegateMgr();

	virtual bool initialize() override;
	virtual void terminate() override;

	bool addDelegate(ITouchDelegate* pDelegate);
	bool removeDelegate(ITouchDelegate* pDelegate);

	void handleTouchEvent(ITouchDelegate::ACTION_TYPE_ID eActionType, const glm::vec2& touchPos);
	void handleZoomEvent(float zoom);

private:
	TV_TOUCH_DELEGATE m_vTouchDelegate;

};

}
