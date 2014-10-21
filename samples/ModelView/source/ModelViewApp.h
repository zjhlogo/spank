/*!
 * \file ModelViewApp.h
 * \date 10-21-2014 10:39:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <IApp.h>
#include <ui/Label.h>

#include <libAssimp/include/assimp/cimport.h>
#include <libAssimp/include/assimp/scene.h>
#include <libAssimp/include/assimp/postprocess.h>

class ModelViewApp : public spank::IApp
{
public:
	ModelViewApp();
	virtual ~ModelViewApp();

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
