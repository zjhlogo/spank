/*!
 * \file SpineAnimation.h
 * \date 2-26-2015 17:28:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <render/RenderCache.h>
#include <spine/spine.h>

class SpineAnimation
{
public:
	enum CONST_DEFINE
	{
		MAX_VERTICES_CACHE = 1000,
	};

public:
	SpineAnimation();
	virtual ~SpineAnimation();

	static void setRenderer(spank::IRenderer* pRenderer);
	static spank::IRenderer* getRenderer();

	bool loadFromFile(const tstring& strJson, const tstring& strAtlas);

	void setAnimation(const tstring& animName, int trackIndex, bool loop);
	void addAnimation(const tstring& animName, int trackIndex, bool loop, float delay);
	void setMix(const tstring& fromAnimName, const tstring& toAnimName, float duration);

	void update(float dt);
	void render();

private:
	bool add(spank::Texture* pTexture, const float* pos, const float* uvs, int nVerts, const int* pIndis, int nIndis);
	static void internalRender(spank::Shader* pShader, spank::Texture* pTexture, spank::VMemVertexBuffer* pVertexBuffer, spank::VMemIndexBuffer* pIndexBuffer);

private:
	static spank::IRenderer* m_pRenderer;
	static spank::Shader* m_pShader;
	static spank::RenderCache<spank::VERT_ATTR_POS3_UV2>* m_pRenderCache;

	spAtlas* m_pAtlas = nullptr;
	spSkeletonData* m_pSkeletonData = nullptr;
	spSkeleton* m_pSkeleton = nullptr;
	spAnimationState* m_pSkeletonState = nullptr;

};
