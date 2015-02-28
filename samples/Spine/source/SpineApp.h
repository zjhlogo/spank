/*!
 * \file SpineApp.h
 * \date 10-10-2014 14:03:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <BaseApp.h>
#include "SpineAnimation.h"

class SpineApp : public BaseApp
{
public:
	SpineApp();
	virtual ~SpineApp();

	virtual bool initialize() override;
	virtual void terminate() override;

protected:
	virtual void update(float dt) override;
	virtual void render() override;

private:
	SpineAnimation* m_pSpineAnimation = nullptr;

};
