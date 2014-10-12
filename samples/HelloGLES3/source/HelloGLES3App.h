/*!
 * \file HelloGLES3App.h
 * \date 10-10-2014 14:03:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <IApp.h>

class HelloGLES3App : public IApp
{
public:
	HelloGLES3App();
	virtual ~HelloGLES3App();

	virtual bool initialize(Framework* pFramework) override;
	virtual void terminate() override;

protected:
	virtual void update(float dt) override;
	virtual void render() override;

private:
	Framework* m_pFramework{ nullptr };

};