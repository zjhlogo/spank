/*!
 * \file MandelbrotApp.h
 * \date 10-10-2014 14:03:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <BaseApp.h>

class MandelbrotApp : public BaseApp
{
public:
	MandelbrotApp();
	virtual ~MandelbrotApp();

	virtual bool initialize() override;
	virtual void terminate() override;

protected:
	virtual void update(float dt) override;
	virtual void render() override;

	virtual void onTouchEvent(spank::ITouchDelegate::ACTION_TYPE_ID eActionType, const glm::vec2& touchPos) override;
	virtual void onZoomEvent(float zoom) override;

private:
	void createRenderBuffer(spank::IRenderer* pRenderer);

private:
	spank::Shader* m_pShader{ nullptr };

	spank::VMemVertexBuffer* m_pVMemVertexBuffer{ nullptr };
	spank::VMemIndexBuffer* m_pVMemIndexBuffer{ nullptr };

	float m_fZoom{ 0.005f };
	glm::vec2 m_centerPos;
	glm::vec2 m_lastTouchPos;

};
