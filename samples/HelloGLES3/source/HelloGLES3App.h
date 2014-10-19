/*!
 * \file HelloGLES3App.h
 * \date 10-10-2014 14:03:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <IApp.h>
#include <ui/Label.h>

class HelloGLES3App : public spank::IApp
{
public:
	HelloGLES3App();
	virtual ~HelloGLES3App();

	virtual bool initialize() override;
	virtual void terminate() override;

protected:
	virtual void update(float dt) override;
	virtual void render() override;

	void createRenderBuffer(spank::IRenderer* pRenderer);

private:
	spank::Texture* m_pTexture{ nullptr };
	spank::Shader* m_pShader{ nullptr };
	spank::Label* m_pLblFPS{ nullptr };

	spank::VMemVertexBuffer* m_pVMemVertexBuffer{ nullptr };

	float m_rot{ 0.0f };

	int m_fps{ 0 };
	float m_elapseTime{ 0.0f };

};
