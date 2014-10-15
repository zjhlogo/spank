/*!
 * \file IApp.h
 * \date 10-10-2014 14:00:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "Framework.h"

namespace spank
{

class IApp
{
public:
	virtual bool initialize(Framework* pFramework) = 0;
	virtual void terminate() = 0;

	void step();

	inline void setFramework(Framework* pFramework) { m_pFramework = pFramework; };
	inline Framework* getFramework() const { return m_pFramework; };
	inline IRenderer* getRenderer() const { return m_pFramework->getRenderer(); };

protected:
	IApp();
	virtual ~IApp();

	virtual void update(float dt) = 0;
	virtual void render() = 0;

private:
	int m_lastTime{ 0 };
	int m_currTime{ 0 };
	float m_frameTime{ 0.0f };
	Framework* m_pFramework{ nullptr };

};

}
