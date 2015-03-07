/*!
 * \file SpineApp.cpp
 * \date 10-10-2014 14:04:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SpineApp.h"
#include <utils/LogUtil.h>
#include <utils/FileUtil.h>
#include <utils/StringBuilder.h>

SpineApp::SpineApp()
{
	// TODO: 
}

SpineApp::~SpineApp()
{

}

bool SpineApp::initialize()
{
	if (!BaseApp::initialize()) return false;

	SpineAnimation::setRenderer(getRenderer());

	m_pSpineAnimation = new SpineAnimation();
	if (!m_pSpineAnimation->loadFromFile("data/spineboy.json", "data/spineboy.atlas")) return false;

	m_pSpineAnimation->setMix("walk", "jump", 0.2f);
	m_pSpineAnimation->setMix("jump", "run", 0.2f);
	m_pSpineAnimation->setAnimation("walk", 0, true);
	m_pSpineAnimation->addAnimation("jump", 0, false, 3.0f);
	m_pSpineAnimation->addAnimation("run", 0, true, 0.0f);

	return true;
}

void SpineApp::terminate()
{
	SAFE_DELETE(m_pSpineAnimation);

	BaseApp::terminate();
}

void SpineApp::update(float dt)
{
	m_pSpineAnimation->update(dt);

	updateFPS(dt);
}

void SpineApp::render()
{
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// 	glm::mat4 matTrans = glm::mat4(1.0f);
// 	matTrans = glm::translate(matTrans, glm::vec3(0.0f, -300.0f, 0.0f));
// 	glm::mat4 matMVP = getRenderer()->getOrthoMatrix() * matTrans;
// 
// 	m_pShader->useProgram();
// 	m_pShader->setUniform("u_matMVP", matMVP);
// 	m_pShader->setTexture(m_pCurrTexture, 0);
// 	m_pShader->drawBuffer(m_pMemVertexBuffer, m_pMemIndexBuffer);

	m_pSpineAnimation->render();

	renderFPS();
}
