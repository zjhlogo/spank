/*!
 * \file BaseApp.h
 * \date 10-22-2014 18:58:30
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <IApp.h>
#include <ui/Label.h>

class BaseApp : public spank::IApp
{
public:
	BaseApp();
	virtual ~BaseApp();

	virtual bool initialize() override;
	virtual void terminate() override;

protected:
	void updateFPS(float dt);
	void renderFPS();

private:
	spank::Texture* m_pTexture{ nullptr };
	spank::Shader* m_pShader{ nullptr };
	spank::Label* m_pLblFPS{ nullptr };

	int m_fps{ 0 };
	float m_elapseTime{ 0.0f };

};
