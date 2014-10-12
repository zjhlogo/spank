/*!
 * \file IApp.h
 * \date 10-10-2014 14:00:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "Framework.h"

class IApp
{
public:
	virtual bool initialize(Framework* pFramework) = 0;
	virtual void terminate() = 0;

	void step();

protected:
	IApp();
	virtual ~IApp();

	virtual void update(float dt) = 0;
	virtual void render() = 0;

private:
	int m_lastTime{ 0 };
	int m_currTime{ 0 };
	float m_frameTime{ 0.0f };

};
