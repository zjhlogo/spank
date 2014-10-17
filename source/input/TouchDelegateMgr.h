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

class TouchDelegateMgr : public IMgr
{
public:
	TouchDelegateMgr();
	virtual ~TouchDelegateMgr();

	virtual bool initialize() override;
	virtual void terminate() override;

	void handleTouchBegin(const glm::vec2& touchPos);
	void handleTouchMove(const glm::vec2& touchPos);
	void handleTouchEnd(const glm::vec2& touchPos);

};

}
