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

ModelViewApp::ModelViewApp()
{
	// TODO: 
}

ModelViewApp::~ModelViewApp()
{

}

bool ModelViewApp::initialize()
{
	spank::BUFFER_DATA bufferData;
	if (!spank::FileUtil::readFile(bufferData, "data/md5/BoarMan.md5mesh")) return false;
	const aiScene* pScene = aiImportFileFromMemory(bufferData.data(), bufferData.size(), aiProcessPreset_TargetRealtime_MaxQuality, "md5mesh");

	spank::IRenderer* pRenderer = getRenderer();

	m_pShader = pRenderer->createShader("data/shaders/pos3_uv2.shader");
	if (!m_pShader) return false;

	m_pTexture = pRenderer->createTexture("data/test.png");
	if (!m_pTexture) return false;

	spank::FontMgr* pFontMgr = getFramework()->getFontMgr();
	spank::IFont* pFont = pFontMgr->createFont("data/12px_Tahoma.xml");
	if (!pFont) return false;

	m_pLblFPS = new spank::Label(pRenderer, pFont);
	if (!m_pLblFPS) return false;
	m_pLblFPS->setPos(-pRenderer->getSurfaceSize()*0.5f);

	createRenderBuffer(pRenderer);

	return true;
}

void ModelViewApp::terminate()
{
	SAFE_RELEASE(m_pVMemVertexBuffer);
	SAFE_DELETE(m_pLblFPS);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pShader);
}

void ModelViewApp::update(float dt)
{
	m_elapseTime += dt;
	if (m_elapseTime > 1.0f)
	{
		m_elapseTime -= 1.0f;
		m_pLblFPS->setText(spank::StringBuilder::format("FPS: #0").add(m_fps).build());
		m_fps = 0;
	}

	++m_fps;
	m_rot += dt;
	if (m_rot > glm::pi<float>()*2.0f) m_rot -= glm::pi<float>()*2.0f;
}

void ModelViewApp::render()
{
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::quat quaRot = glm::angleAxis(m_rot, glm::normalize(glm::vec3(0.3f, 1.0f, 0.7f)));
	glm::mat4 matRot = glm::mat4_cast(quaRot);
	glm::mat4 matView = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 matMVP = getRenderer()->getPerspectiveMatrix() * matView * matRot;

	m_pShader->useProgram();
	m_pShader->setMatrix("u_matMVP", matMVP);
	m_pShader->setTexture(m_pTexture, 0);
	m_pShader->drawBuffer(m_pVMemVertexBuffer, 0, 36);

	m_pLblFPS->render();
}

void ModelViewApp::createRenderBuffer(spank::IRenderer* pRenderer)
{
	m_pVMemVertexBuffer = pRenderer->createVMemVertexBuffer(m_pShader->getVertexAttributes());
	if (!m_pVMemVertexBuffer) return;

	spank::VERT_ATTR_POS3_UV2 verts[] =
	{
		 // front
		-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

		 // top
		-1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f, 0.0f,

		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f, 0.0f,

		 // back
		-1.0f,  1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f, 0.0f,

		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f, 0.0f,

		 // bottom
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

		-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

		 // left
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

		 // right
		 1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

		 1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
	};

	m_pVMemVertexBuffer->uploadBuffer(verts, sizeof(verts));
}
