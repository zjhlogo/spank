/*!
 * \file HelloGLES3App.h
 * \date 10-10-2014 14:03:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <IApp.h>

class HelloGLES3App : public spank::IApp
{
public:
	HelloGLES3App();
	virtual ~HelloGLES3App();

	virtual bool initialize(spank::Framework* pFramework) override;
	virtual void terminate() override;

protected:
	virtual void update(float dt) override;
	virtual void render() override;

private:
	spank::Texture* m_pTexture{ nullptr };
	spank::Shader* m_pShader{ nullptr };

	spank::MemRenderBuffer* m_pRenderBufferMem{ nullptr };
	spank::VMemRenderBuffer* m_pRenderBufferVMem{ nullptr };
};
