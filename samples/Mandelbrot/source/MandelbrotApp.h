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

	void updateInfo();
	void renderInfo();

private:
	spank::Shader* m_pShader{ nullptr };

	spank::VMemVertexBuffer* m_pVMemVertexBuffer{ nullptr };
	spank::VMemIndexBuffer* m_pVMemIndexBuffer{ nullptr };

	spank::Label* m_pLblInfo{ nullptr };

	float m_fZoom{ 0.0025f };
	float m_fMaxIteration{ 18.0f };
	float m_fEscapeRadius{ 4.0f };
	glm::vec2 m_centerPos{ -0.64f, 0.0f };
	glm::vec3 m_colorScale{ 0.025f, 0.08f, 0.12f };

	glm::vec2 m_lastTouchPos;

};
