/*!
 * \file SpineApp.h
 * \date 10-10-2014 14:03:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <BaseApp.h>
#include <render/VertexAttributes.h>
#include <spine/spine.h>

class SpineApp : public BaseApp
{
public:
	enum CONST_DEFINE
	{
		MAX_VERTICES_CACHE = 1000,
	};

	typedef std::vector<spank::VERT_ATTR_POS3_UV2> TV_VERT_ATTR_POS3_UV2;
	typedef std::vector<short> TV_SHORT;

public:
	SpineApp();
	virtual ~SpineApp();

	virtual bool initialize() override;
	virtual void terminate() override;

protected:
	virtual void update(float dt) override;
	virtual void render() override;

private:
	bool add(spank::Texture* pTexture, const float* pos, const float* uvs, int nVerts, const int* pIndis, int nIndis);
	void flush();

private:
	spAtlas* m_pAtlas = nullptr;
	spSkeletonData* m_pSkeletonData = nullptr;
	spSkeleton* m_pSkeleton = nullptr;

	spank::Texture* m_pCurrTexture = nullptr;

	spank::Shader* m_pShader = nullptr;
	spank::MemVertexBuffer* m_pMemVertexBuffer = nullptr;
	spank::MemIndexBuffer* m_pMemIndexBuffer = nullptr;
	TV_VERT_ATTR_POS3_UV2 m_vertices;
	TV_SHORT m_vindices;

};
