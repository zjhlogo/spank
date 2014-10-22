/*!
 * \file ModelMgr.h
 * \date 10-22-2014 17:41:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "../base/IMgr.h"
#include <map>

namespace spank
{

class MeshData;
class IRenderer;

class ModelMgr : public IMgr
{
public:
	friend class MeshData;

	typedef std::map<std::string, MeshData*> TM_MESH_DATA;

public:
	ModelMgr(IRenderer* pRenderer);
	virtual ~ModelMgr();

	virtual bool initialize() override;
	virtual void terminate() override;

	MeshData* createMeshData(const std::string& filePath);

protected:
	bool removeMeshData(MeshData* pMeshData);

private:
	IRenderer* m_pRenderer{ nullptr };
	TM_MESH_DATA m_meshDataMap;

};

}
