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

	virtual bool initialize() override;
	virtual void terminate() override;

protected:
	virtual void update(float dt) override;
	virtual void render() override;

private:
	spank::Texture* m_pTexture{ nullptr };
	spank::Shader* m_pShader{ nullptr };

	spank::MemVertexBuffer* m_pMemVertexBuffer{ nullptr };
	spank::VMemVertexBuffer* m_pVMemVertexBuffer{ nullptr };

	float m_rot{ 0.0f };

};
