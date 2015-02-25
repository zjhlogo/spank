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
#include <render/VertexAttributes.h>

spank::IRenderer* g_pRenderer = nullptr;

extern "C"
{

void _spAtlasPage_createTexture(spAtlasPage* self, const char* path)
{
	spank::Texture* pTexture = g_pRenderer->createTexture(path);
	self->rendererObject = pTexture;
	self->width = pTexture->getWidth();
	self->height = pTexture->getHeight();
}

void _spAtlasPage_disposeTexture(spAtlasPage* self)
{
	spank::Texture* pTexture = reinterpret_cast<spank::Texture*>(self->rendererObject);
	SAFE_RELEASE(pTexture);
}

char* _spUtil_readFile(const char* path, int* length)
{
	void* pBuffer = nullptr;
	long size = 0;
	if (!spank::FileUtil::readFileDataOwnerFree(&pBuffer, size, path)) return nullptr;

	*length = size;
	return static_cast<char*>(pBuffer);
}

}

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

	g_pRenderer = getRenderer();

	m_pAtlas = spAtlas_createFromFile("data/spineboy.atlas", nullptr);
	if (!m_pAtlas) return false;

	spSkeletonJson* json = spSkeletonJson_create(m_pAtlas);
	if (!json) return nullptr;
	json->scale = 1.0f;

	m_pSkeletonData = spSkeletonJson_readSkeletonDataFile(json, "data/spineboy.json");
	spSkeletonJson_dispose(json);
	if (!m_pSkeletonData) return false;

	m_pSkeleton = spSkeleton_create(m_pSkeletonData);
	if (!m_pSkeleton) return false;

	m_pSkeleton->r = m_pSkeleton->g = m_pSkeleton->b = m_pSkeleton->a = 1.0f;

	m_pSkeletonState = spAnimationState_create(spAnimationStateData_create(m_pSkeleton->data));
	spAnimationState_setAnimationByName(m_pSkeletonState, 0, "walk", true);

	m_pShader = g_pRenderer->createShader("data/shaders/pos3_uv2.shader");
	if (!m_pShader) return false;

	m_pMemVertexBuffer = g_pRenderer->createVMemVertexBuffer(m_pShader->getVertexAttributes());
	m_pMemIndexBuffer = getRenderer()->createVMemIndexBuffer();

	return true;
}

void SpineApp::terminate()
{
	SAFE_RELEASE(m_pMemIndexBuffer);
	SAFE_RELEASE(m_pMemVertexBuffer);
	SAFE_RELEASE(m_pShader);

	spAnimationStateData_dispose(m_pSkeletonState->data);
	spAnimationState_dispose(m_pSkeletonState);
	spSkeletonData_dispose(m_pSkeletonData);
	spAtlas_dispose(m_pAtlas);
	spSkeleton_dispose(m_pSkeleton);

	BaseApp::terminate();
}

void SpineApp::update(float dt)
{
	updateFPS(dt);
	spSkeleton_update(m_pSkeleton, dt);
	spAnimationState_update(m_pSkeletonState, dt);
	spAnimationState_apply(m_pSkeletonState, m_pSkeleton);
	spSkeleton_updateWorldTransform(m_pSkeleton);
}

void SpineApp::render()
{
	static float s_vertices[MAX_VERTICES_CACHE];
	static const int s_quadTriangles[6] = { 0, 1, 2, 2, 3, 0 };

	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	int additive = -1;
	const float* uvs = nullptr;
	int verticesCount = 0;
	const int* triangles = nullptr;
	int trianglesCount = 0;
//	float r = 0, g = 0, b = 0, a = 0;

	for (int i = 0, n = m_pSkeleton->slotsCount; i < n; i++)
	{
		spSlot* slot = m_pSkeleton->drawOrder[i];
		if (!slot->attachment) continue;

		spank::Texture* pTexture = nullptr;
		switch (slot->attachment->type)
		{
		case SP_ATTACHMENT_REGION:
		{
			spRegionAttachment* attachment = reinterpret_cast<spRegionAttachment*>(slot->attachment);
			spRegionAttachment_computeWorldVertices(attachment, slot->bone, s_vertices);
			pTexture = reinterpret_cast<spank::Texture*>(reinterpret_cast<spAtlasRegion*>(attachment->rendererObject)->page->rendererObject);
			uvs = attachment->uvs;
			verticesCount = 8;
			triangles = s_quadTriangles;
			trianglesCount = 6;
// 			r = attachment->r;
// 			g = attachment->g;
// 			b = attachment->b;
// 			a = attachment->a;
		}
		break;
		case SP_ATTACHMENT_MESH:
		{
			spMeshAttachment* attachment = reinterpret_cast<spMeshAttachment*>(slot->attachment);
			spMeshAttachment_computeWorldVertices(attachment, slot, s_vertices);
			pTexture = reinterpret_cast<spank::Texture*>(reinterpret_cast<spAtlasRegion*>(attachment->rendererObject)->page->rendererObject);
			uvs = attachment->uvs;
			verticesCount = attachment->verticesCount;
			triangles = attachment->triangles;
			trianglesCount = attachment->trianglesCount;
// 			r = attachment->r;
// 			g = attachment->g;
// 			b = attachment->b;
// 			a = attachment->a;
		}
		break;
		case SP_ATTACHMENT_SKINNED_MESH:
		{
			spSkinnedMeshAttachment* attachment = reinterpret_cast<spSkinnedMeshAttachment*>(slot->attachment);
			spSkinnedMeshAttachment_computeWorldVertices(attachment, slot, s_vertices);
			pTexture = reinterpret_cast<spank::Texture*>(reinterpret_cast<spAtlasRegion*>(attachment->rendererObject)->page->rendererObject);
			uvs = attachment->uvs;
			verticesCount = attachment->uvsCount;
			triangles = attachment->triangles;
			trianglesCount = attachment->trianglesCount;
// 			r = attachment->r;
// 			g = attachment->g;
// 			b = attachment->b;
// 			a = attachment->a;
		}
		break;
		default:
			break;
		}

		if (pTexture)
		{
// 			if (slot->data->additiveBlending != additive)
// 			{
// 				batch->flush();
// 				ccGLBlendFunc(blendFunc.src, slot->data->additiveBlending ? GL_ONE : blendFunc.dst);
// 				additive = slot->data->additiveBlending;
// 			}
// 			ccColor4B color;
// 			color.a = skeleton->a * slot->a * a * 255;
// 			float multiplier = premultipliedAlpha ? color.a : 255;
// 			color.r = skeleton->r * slot->r * r * multiplier;
// 			color.g = skeleton->g * slot->g * g * multiplier;
// 			color.b = skeleton->b * slot->b * b * multiplier;

			add(pTexture, s_vertices, uvs, verticesCount, triangles, trianglesCount);
		}
	}

	flush();

	renderFPS();
}

bool SpineApp::add(spank::Texture* pTexture, const float* pos, const float* uvs, int nVerts, const int* pIndis, int nIndis)
{
	if (m_pCurrTexture != nullptr && pTexture != m_pCurrTexture)
	{
		flush();
	}
	m_pCurrTexture = pTexture;

	spank::VERT_ATTR_POS3_UV2 vert;
	vert.z = 0.0f;

	int baseIndex = m_vertices.size();
	for (int i = 0; i < nVerts; ++i)
	{
		vert.x = pos[i * 2 + 0];
		vert.y = pos[i * 2 + 1];
		vert.u = uvs[i * 2 + 0];
		vert.v = 1.0f - uvs[i * 2 + 1];
		m_vertices.push_back(vert);
	}

	for (int i = 0; i < nIndis; ++i)
	{
		m_vindices.push_back(baseIndex + pIndis[i]);
	}

	return true;
}

void SpineApp::flush()
{
	if (m_vertices.size() <= 0 || m_vindices.size() <= 0) return;
	if (!m_pCurrTexture) return;

	m_pMemVertexBuffer->uploadBuffer(&m_vertices[0], sizeof(spank::VERT_ATTR_POS3_UV2)*m_vertices.size());
	m_pMemIndexBuffer->uploadBuffer(&m_vindices[0], sizeof(short)*m_vindices.size());

	glm::mat4 matTrans = glm::mat4(1.0f);
	matTrans = glm::translate(matTrans, glm::vec3(0.0f, -300.0f, 0.0f));
	glm::mat4 matMVP = getRenderer()->getOrthoMatrix() * matTrans;

	m_pShader->useProgram();
	m_pShader->setUniform("u_matMVP", matMVP);
	m_pShader->setTexture(m_pCurrTexture, 0);
	m_pShader->drawBuffer(m_pMemVertexBuffer, m_pMemIndexBuffer);

	m_pCurrTexture = nullptr;
	m_vertices.clear();
	m_vindices.clear();
}
