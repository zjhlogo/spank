/*!
 * \file SpineAnimation.cpp
 * \date 2-26-2015 17:28:24
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SpineAnimation.h"
#include <render/Texture.h>
#include <render/IRenderer.h>
#include <utils/FileUtil.h>

extern "C"
{

	void _spAtlasPage_createTexture(spAtlasPage* self, const char* path)
	{
		spank::Texture* pTexture = SpineAnimation::getRenderer()->createTexture(path);
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

spank::IRenderer* SpineAnimation::m_pRenderer = nullptr;
spank::Shader* SpineAnimation::m_pShader = nullptr;
spank::RenderCache<spank::VERT_ATTR_POS3_UV2>* SpineAnimation::m_pRenderCache = nullptr;

SpineAnimation::SpineAnimation()
{
	// TODO: 
}

SpineAnimation::~SpineAnimation()
{
	spAnimationStateData_dispose(m_pSkeletonState->data);
	spAnimationState_dispose(m_pSkeletonState);
	spSkeletonData_dispose(m_pSkeletonData);
	spAtlas_dispose(m_pAtlas);
	spSkeleton_dispose(m_pSkeleton);
}

void SpineAnimation::setRenderer(spank::IRenderer* pRenderer)
{
	m_pRenderer = pRenderer;

	SAFE_DELETE(m_pRenderCache);
	SAFE_RELEASE(m_pShader);

	if (m_pRenderer)
	{
		m_pRenderCache = new spank::RenderCache<spank::VERT_ATTR_POS3_UV2>(m_pRenderer, "data/shaders/pos3_uv2.attrs");
		m_pShader = m_pRenderer->createShader("data/shaders/pos3_uv2.shader");
	}
}

spank::IRenderer* SpineAnimation::getRenderer()
{
	return m_pRenderer;
}

bool SpineAnimation::loadFromFile(const tstring& strJson, const tstring& strAtlas)
{
	m_pAtlas = spAtlas_createFromFile(strAtlas.c_str(), nullptr);
	if (!m_pAtlas) return false;

	spSkeletonJson* json = spSkeletonJson_create(m_pAtlas);
	if (!json) return nullptr;
	json->scale = 1.0f;

	m_pSkeletonData = spSkeletonJson_readSkeletonDataFile(json, strJson.c_str());
	spSkeletonJson_dispose(json);
	if (!m_pSkeletonData) return false;

	m_pSkeleton = spSkeleton_create(m_pSkeletonData);
	if (!m_pSkeleton) return false;

	m_pSkeletonState = spAnimationState_create(spAnimationStateData_create(m_pSkeleton->data));
	spAnimationState_setAnimationByName(m_pSkeletonState, 0, "walk", true);

	return true;
}

void SpineAnimation::update(float dt)
{
	spSkeleton_update(m_pSkeleton, dt);
	spAnimationState_update(m_pSkeletonState, dt);
	spAnimationState_apply(m_pSkeletonState, m_pSkeleton);
	spSkeleton_updateWorldTransform(m_pSkeleton);
}

void SpineAnimation::render()
{
	static float s_vertices[MAX_VERTICES_CACHE];
	static const int s_quadTriangles[6] = { 0, 1, 2, 2, 3, 0 };

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

	m_pRenderCache->flush();
}

bool SpineAnimation::add(spank::Texture* pTexture, const float* pos, const float* uvs, int nVerts, const int* pIndis, int nIndis)
{
	std::vector<spank::VERT_ATTR_POS3_UV2> m_vertices;

	spank::VERT_ATTR_POS3_UV2 vert;
	vert.z = 0.0f;

	for (int i = 0; i < nVerts; ++i)
	{
		vert.x = pos[i * 2 + 0];
		vert.y = pos[i * 2 + 1];
		vert.u = uvs[i * 2 + 0];
		vert.v = 1.0f - uvs[i * 2 + 1];
		m_vertices.push_back(vert);
	}

	std::vector<short> m_indices;
	for (int i = 0; i < nIndis; ++i)
	{
		m_indices.push_back(static_cast<short>(pIndis[i]));
	}

	return m_pRenderCache->add(m_pShader, pTexture, m_vertices.data(), m_vertices.size(), m_indices.data(), m_indices.size());
}
