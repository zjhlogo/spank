/*!
 * \file ModelViewApp.cpp
 * \date 10-21-2014 10:39:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ModelViewApp.h"
#include <utils/LogUtil.h>
#include <utils/FileUtil.h>
#include <utils/StringBuilder.h>
#include <render/VertexAttributes.h>
#include <model/MeshData.h>

ModelViewApp::ModelViewApp()
{
	// TODO: 
}

ModelViewApp::~ModelViewApp()
{

}

bool ModelViewApp::initialize()
{
	if (!BaseApp::initialize()) return false;

	spank::IRenderer* pRenderer = getRenderer();
	m_pShader = pRenderer->createShader("data/shaders/pos3_uv2_normal.shader");
	if (!m_pShader) return false;

	m_pTexture = pRenderer->createTexture("data/md5/guard1_body.png");
	if (!m_pTexture) return false;

	m_pMeshData = getFramework()->getModelMgr()->createMeshData("data/md5/Bob.mesh");
	if (!m_pMeshData) return false;

	return true;
}

void ModelViewApp::terminate()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pShader);
	BaseApp::terminate();
}

void ModelViewApp::update(float dt)
{
	updateFPS(dt);

	m_rot += dt;
	if (m_rot > glm::pi<float>()*2.0f) m_rot -= glm::pi<float>()*2.0f;
}

void ModelViewApp::render()
{
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::quat quaRot = glm::angleAxis(m_rot, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
	glm::mat4 matRot = glm::mat4_cast(quaRot);
	glm::mat4 matView = glm::lookAt(glm::vec3(0.0f, 0.0f, 200.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 matMVP = getRenderer()->getPerspectiveMatrix() * matView * matRot;

	m_pShader->useProgram();
	m_pShader->setMatrix("u_matMVP", matMVP);
	m_pShader->setTexture(m_pTexture, 0);

	for (const auto& renderPieceInfo : m_pMeshData->renderPieceInfoList)
	{
		m_pShader->drawBuffer(renderPieceInfo->pVertexBuffer, renderPieceInfo->pIndexBuffer);
	}

	renderFPS();
}
