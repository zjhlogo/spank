/*!
 * \file ModelMgr.cpp
 * \date 10-22-2014 17:41:08
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ModelMgr.h"
#include "MeshData.h"
#include "../utils/LogUtil.h"

namespace spank
{

ModelMgr::ModelMgr(IRenderer* pRenderer)
	:m_pRenderer(pRenderer)
{
	// TODO: 
}

ModelMgr::~ModelMgr()
{
	// TODO: 
}

bool ModelMgr::initialize()
{
	return true;
}

void ModelMgr::terminate()
{
	for (auto meshData : m_meshDataMap)
	{
		MeshData* pMeshData = meshData.second;
		LOGE("Un-released mesh data %s", pMeshData->getId().c_str());
		SAFE_DELETE(pMeshData);
	}
	m_meshDataMap.clear();
}

MeshData* ModelMgr::createMeshData(const std::string& filePath)
{
	// find from cache
	TM_MESH_DATA::iterator it = m_meshDataMap.find(filePath);
	if (it != m_meshDataMap.end()) return it->second;

	// create new one
	MeshData* pMeshData = new MeshData(this, m_pRenderer);
	if (!pMeshData->loadFromFile(filePath))
	{
		SAFE_DELETE(pMeshData);
		return NULL;
	}

	// cache it
	m_meshDataMap.insert(std::make_pair(filePath, pMeshData));
	return pMeshData;
}

bool ModelMgr::removeMeshData(MeshData* pMeshData)
{
	if (!pMeshData) return false;

	auto it = m_meshDataMap.find(pMeshData->getId());
	if (it == m_meshDataMap.end())
	{
		LOGE("can not find mesh data %s from map", pMeshData->getId().c_str());
		return false;
	}

	m_meshDataMap.erase(it);
	return true;
}

}
