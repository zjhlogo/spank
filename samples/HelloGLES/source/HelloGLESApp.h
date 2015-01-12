/*!
 * \file HelloGLESApp.h
 * \date 10-10-2014 14:03:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <BaseApp.h>

class HelloGLESApp : public BaseApp
{
public:
	HelloGLESApp();
	virtual ~HelloGLESApp();

	virtual bool initialize() override;
	virtual void terminate() override;

protected:
	virtual void update(float dt) override;
	virtual void render() override;

	void createRenderBuffer(spank::IRenderer* pRenderer);

private:
	spank::Texture* m_pTexture{ nullptr };
	spank::Shader* m_pShader{ nullptr };

	spank::VMemVertexBuffer* m_pVMemVertexBuffer{ nullptr };

	float m_rot{ 0.0f };

};
