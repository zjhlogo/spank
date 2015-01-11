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
#include <input/TouchDelegateMgr.h>

class BaseApp;

class BaseAppTouchDelegate : public spank::ITouchDelegate
{
public:
	BaseAppTouchDelegate(BaseApp* pBaseApp):m_pBaseApp(pBaseApp) {};
	virtual ~BaseAppTouchDelegate() {};

	virtual void onTouchEvent(ITouchDelegate::ACTION_TYPE_ID eActionType, const glm::vec2& touchPos) override;
	virtual void onZoomEvent(float zoom) override;

private:
	BaseApp* m_pBaseApp{ nullptr };

};

class BaseApp : public spank::IApp
{
	friend class BaseAppTouchDelegate;

public:
	BaseApp();
	virtual ~BaseApp();

	virtual bool initialize() override;
	virtual void terminate() override;

protected:
	void updateFPS(float dt);
	void renderFPS();

	virtual void onTouchEvent(spank::ITouchDelegate::ACTION_TYPE_ID eActionType, const glm::vec2& touchPos) {};
	virtual void onZoomEvent(float zoom) {};

private:
	spank::Texture* m_pTexture{ nullptr };
	spank::Shader* m_pShader{ nullptr };
	spank::Label* m_pLblFPS{ nullptr };
	BaseAppTouchDelegate* m_pBaseAppTouchDelegate{ nullptr };

	int m_fps{ 0 };
	float m_elapseTime{ 0.0f };

};
