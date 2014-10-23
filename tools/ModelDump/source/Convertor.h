/*!
 * \file Convertor.h
 * \date 10-22-2014 11:09:16
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <model/MeshFileFormat.h>

#include <glm/glm.hpp>
#include <libAssimp/include/assimp/cimport.h>
#include <libAssimp/include/assimp/scene.h>
#include <libAssimp/include/assimp/postprocess.h>

#include <string>
#include <set>

namespace spank
{
class Convertor
{
public:
	typedef struct BONE_INFO_tag
	{
		int boneId{ -1 };
		float weight{ 0.0f };
	} BONE_INFO;
	typedef std::vector<BONE_INFO> TV_BONE_INFO;

	typedef struct FULL_VERT_ATTRS_tag
	{
		glm::vec3 pos;
		glm::vec2 uv[MeshFileFormat::MAX_TEX_COORDS];
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 binormal;
		TV_BONE_INFO boneInfoList;
	} FULL_VERT_ATTRS;
	typedef std::vector<FULL_VERT_ATTRS> TV_FULL_VERT_ATTRS;

	typedef std::vector<uint16> TV_UINT16;

	typedef struct MATERIAL_tag
	{
		int id;
		std::string texDiffuse;
	} MATERIAL;
	typedef std::vector<MATERIAL> TV_MATERIAL;

	typedef struct MESH_tag
	{
		std::string name;					// piece name
		const MATERIAL* pMaterial{ nullptr };
		uint vertAttrFlag{ 0 };				// see MeshFileFormat::VERTEX_ATTRIBUTES
		TV_FULL_VERT_ATTRS verts;
		TV_UINT16 indis;
	} MESH;
	typedef std::vector<MESH*> TV_MESH;

public:
	Convertor();
	~Convertor();

	bool openModelFile(const char* pszFilePath);
	bool saveFile(const char* pszFilePath);
	void reset();

private:
	bool collectPieceInfo(const aiScene* pScene);

	bool copyVertexPos(MESH* pPieceInfo, const aiVector3D* pPos, uint numVerts);
	bool copyVertexUv(MESH* pPieceInfo, int channel, const aiVector3D* pUv, uint numVerts);
	bool copyVertexNormal(MESH* pPieceInfo, const aiVector3D* pNormal, uint numVerts);
	bool copyVertexTangentAndBinormal(MESH* pPieceInfo, const aiVector3D* pTangent, const aiVector3D* pBinormal, uint numVerts);
	bool copyBoneInfo(MESH* pPieceInfo, aiBone**const pBones, uint numBones);
	bool copyFaceIndex(MESH* pPieceInfo, const aiFace* pFace, uint numFace);
	uint calculateStride(uint vertAttrs);

private:
	uint m_processFlag
	{
//		aiProcess_CalcTangentSpace | // calculate tangents and bitangents if possible
		aiProcess_JoinIdenticalVertices | // join identical vertices/ optimize indexing
		aiProcess_ValidateDataStructure | // perform a full validation of the loader's output
		aiProcess_ImproveCacheLocality | // improve the cache locality of the output vertices
		aiProcess_RemoveRedundantMaterials | // remove redundant materials
		aiProcess_FindDegenerates | // remove degenerated polygons from the import
		aiProcess_FindInvalidData | // detect invalid model data, such as invalid normal vectors
		aiProcess_GenUVCoords | // convert spherical, cylindrical, box and planar mapping to proper UVs
		aiProcess_TransformUVCoords | // preprocess UV transformations (scaling, translation ...)
		aiProcess_FindInstances | // search for instanced meshes and remove them by references to one master
		aiProcess_LimitBoneWeights | // limit bone weights to 4 per vertex
		aiProcess_OptimizeMeshes | // join small meshes, if possible;
		aiProcess_SplitByBoneCount | // split meshes with too many bones. Necessary for our (limited) hardware skinning shader
		aiProcess_GenSmoothNormals | // generate smooth normal vectors if not existing
		aiProcess_SplitLargeMeshes | // split large, unrenderable meshes into submeshes
		aiProcess_Triangulate | // triangulate polygons with more than 3 edges
//		aiProcess_ConvertToLeftHanded | // convert everything to D3D left handed space
		aiProcess_SortByPType | // make 'clean' meshes which consist of a single typ of primitives
		0
	};

	const aiScene* m_pScene{ nullptr };

	TV_MATERIAL m_materialList;
	TV_MESH m_meshList;

};

}
