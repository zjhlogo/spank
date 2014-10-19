/*!
 * \file HelloGLES3App.cpp
 * \date 10-10-2014 14:04:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "HelloGLES3App.h"
#include <utils/LogUtil.h>
#include <utils/FileUtil.h>
#include <utils/StringBuilder.h>

HelloGLES3App::HelloGLES3App()
{
	// TODO: 
}

HelloGLES3App::~HelloGLES3App()
{

}

bool HelloGLES3App::initialize()
{
	spank::IRenderer* pRenderer = getRenderer();

	m_pShader = pRenderer->createShader("data/shaders/pos3_uv2.shader");
	if (!m_pShader) return false;

	m_pTexture = pRenderer->createTexture("data/test.png");
	if (!m_pTexture) return false;

	spank::FontMgr* pFontMgr = getFramework()->getFontMgr();
	spank::IFont* pFont = pFontMgr->createFont("data/12px_Tahoma.xml");
	if (!pFont) return false;

	m_pLabel = new spank::Label(pRenderer, pFont);
	if (!m_pLabel) return false;
	m_pLabel->setPos(-pRenderer->getSurfaceSize()*0.5f);

	m_pMemVertexBuffer = pRenderer->createMemVertexBuffer(m_pShader->getVertexAttributes());
	if (!m_pMemVertexBuffer) return false;

	m_pVMemVertexBuffer = pRenderer->createVMemVertexBuffer(m_pShader->getVertexAttributes());
	if (!m_pVMemVertexBuffer) return false;

	GLfloat vertAttribs[] = { -0.4f, -0.4f, 0.0f, // Pos
		0.0f, 0.0f,	  // UVs
		0.4f, -0.4f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.4f, 0.0f,
		0.5f, 1.0f };

	m_pMemVertexBuffer->uploadBuffer(vertAttribs, sizeof(vertAttribs));
	m_pVMemVertexBuffer->uploadBuffer(vertAttribs, sizeof(vertAttribs));

	return true;
}

void HelloGLES3App::terminate()
{
	SAFE_RELEASE(m_pVMemVertexBuffer);
	SAFE_RELEASE(m_pMemVertexBuffer);
	SAFE_DELETE(m_pLabel);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pShader);
}

void HelloGLES3App::update(float dt)
{
	m_elapseTime += dt;
	if (m_elapseTime > 1.0f)
	{
		m_elapseTime -= 1.0f;
		m_pLabel->setText(spank::StringBuilder::format("FPS: #0").add(m_fps).build());
		m_fps = 0;
	}

	++m_fps;
	m_rot += dt;
	if (m_rot > glm::pi<float>()*2.0f) m_rot -= glm::pi<float>()*2.0f;
}

void HelloGLES3App::render()
{
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glm::quat quaRot = glm::angleAxis(m_rot, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 matRot = glm::mat4_cast(quaRot);

	m_pShader->useProgram();
	m_pShader->setMatrix("u_matMVP", matRot);
	m_pShader->setTexture(m_pTexture, 0);
	m_pShader->drawBuffer(m_pVMemVertexBuffer, 0, 3);

	m_pLabel->render();
}
