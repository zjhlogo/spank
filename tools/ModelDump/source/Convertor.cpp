/*!
 * \file Convertor.cpp
 * \date 10-22-2014 11:09:22
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Convertor.h"

namespace spank
{

Convertor::Convertor()
{
	// TODO: 
}

Convertor::~Convertor()
{
	reset();
}

bool Convertor::openModelFile(const char* pszFilePath)
{
	reset();

	m_pScene = aiImportFile(pszFilePath, m_processFlag);
	if (!m_pScene) return false;

	collectPieceInfo(m_pScene, m_pScene->mRootNode);

	return true;
}

bool Convertor::saveFile(const char* pszFilePath)
{
	if (m_meshList.empty()) return false;

	FILE* pFile = fopen(pszFilePath, "wb");
	if (!pFile) return false;

	// wirte file header
	MeshFileFormat::FILE_HEADER fileHeader;
	fileHeader.nNumPieces = (int)m_meshList.size();
	fwrite(&fileHeader, sizeof(fileHeader), 1, pFile);

	// write piece list
	long pieceListAddr = ftell(pFile);
	MeshFileFormat::TV_PIECE_INFO pieceList;
	pieceList.resize(fileHeader.nNumPieces);
	fwrite(pieceList.data(), sizeof(MeshFileFormat::PIECE_INFO), pieceList.size(), pFile);

	for (int i = 0; i < fileHeader.nNumPieces; ++i)
	{
		const MESH* pMesh = m_meshList[i];

		// copy piece info
		strncpy(pieceList[i].szName, pMesh->name.c_str(), MeshFileFormat::PIECE_NAME_SIZE);
		pieceList[i].nVertexAttributes = pMesh->vertAttrFlag;
		pieceList[i].nNumVerts = pMesh->verts.size();
		pieceList[i].nOffVerts = ftell(pFile);
		pieceList[i].nSizeOfVerts = calculateStride(pMesh->vertAttrFlag) * pMesh->verts.size();

		for (const auto& vert : pMesh->verts)
		{
			if ((pMesh->vertAttrFlag & MeshFileFormat::VA_POSITION) == MeshFileFormat::VA_POSITION)
			{
				fwrite(&vert.pos.x, sizeof(float), 1, pFile);
				fwrite(&vert.pos.y, sizeof(float), 1, pFile);
				fwrite(&vert.pos.z, sizeof(float), 1, pFile);
			}

			for (int channel = 0; channel < MeshFileFormat::MAX_TEX_COORDS; ++channel)
			{
				if ((pMesh->vertAttrFlag & (MeshFileFormat::VA_TEXCOORD0 << channel)) == (MeshFileFormat::VA_TEXCOORD0 << channel))
				{
					fwrite(&vert.uv[channel].x, sizeof(float), 1, pFile);
					fwrite(&vert.uv[channel].y, sizeof(float), 1, pFile);
				}
			}

			if ((pMesh->vertAttrFlag & MeshFileFormat::VA_NORMAL) == MeshFileFormat::VA_NORMAL)
			{
				fwrite(&vert.normal.x, sizeof(float), 1, pFile);
				fwrite(&vert.normal.y, sizeof(float), 1, pFile);
				fwrite(&vert.normal.z, sizeof(float), 1, pFile);
			}

			if ((pMesh->vertAttrFlag & MeshFileFormat::VA_TANGENT) == MeshFileFormat::VA_TANGENT)
			{
				fwrite(&vert.tangent.x, sizeof(float), 1, pFile);
				fwrite(&vert.tangent.y, sizeof(float), 1, pFile);
				fwrite(&vert.tangent.z, sizeof(float), 1, pFile);
			}

			if ((pMesh->vertAttrFlag & MeshFileFormat::VA_BINORMAL) == MeshFileFormat::VA_BINORMAL)
			{
				fwrite(&vert.binormal.x, sizeof(float), 1, pFile);
				fwrite(&vert.binormal.y, sizeof(float), 1, pFile);
				fwrite(&vert.binormal.z, sizeof(float), 1, pFile);
			}
		}

		pieceList[i].nNumIndis = pMesh->indis.size();
		pieceList[i].nOffIndis = ftell(pFile);
		pieceList[i].nSizeOfIndis = pMesh->indis.size() * sizeof(uint16);

		fwrite(pMesh->indis.data(), sizeof(uint16), pMesh->indis.size(), pFile);
	}

	fseek(pFile, pieceListAddr, SEEK_SET);
	fwrite(pieceList.data(), sizeof(MeshFileFormat::PIECE_INFO), pieceList.size(), pFile);
	fclose(pFile);

	return true;
}

void Convertor::reset()
{
	if (m_pScene)
	{
		aiReleaseImport(m_pScene);
		m_pScene = nullptr;
	}

	for (auto& pieceInfo : m_meshList)
	{
		SAFE_DELETE(pieceInfo);
	}
	m_meshList.clear();
}

bool Convertor::collectPieceInfo(const aiScene* pScene, const aiNode* pNode)
{
	// collect mesh
	for (uint i = 0; i < pNode->mNumMeshes; ++i)
	{
		const aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[i]];

		MESH* pPieceInfo = new MESH();
		pPieceInfo->name = pMesh->mName.C_Str();

		// copy verts pos
		if (pMesh->HasPositions())
		{
			pPieceInfo->vertAttrFlag |= MeshFileFormat::VA_POSITION;
			copyVertexPos(pPieceInfo, pMesh->mVertices, pMesh->mNumVertices);
		}

		// copy verts uv
		for (int uvChannel = 0; uvChannel < MeshFileFormat::MAX_TEX_COORDS; ++uvChannel)
		{
			if (pMesh->HasTextureCoords(uvChannel))
			{
				pPieceInfo->vertAttrFlag |= (MeshFileFormat::VA_TEXCOORD0 << uvChannel);
				copyVertexUv(pPieceInfo, uvChannel, pMesh->mTextureCoords[uvChannel], pMesh->mNumVertices);
			}
		}

		// copy normal
		if (pMesh->HasNormals())
		{
			pPieceInfo->vertAttrFlag |= MeshFileFormat::VA_NORMAL;
			copyVertexNormal(pPieceInfo, pMesh->mNormals, pMesh->mNumVertices);
		}

		// copy tangent and binotmal
		if (pMesh->HasTangentsAndBitangents())
		{
			pPieceInfo->vertAttrFlag |= (MeshFileFormat::VA_TANGENT | MeshFileFormat::VA_BINORMAL);
			copyVertexTangentAndBinormal(pPieceInfo, pMesh->mTangents, pMesh->mBitangents, pMesh->mNumVertices);
		}

		// TODO: copy skelecton
// 		if (pMesh->HasBones())
// 		{
// 			pPieceInfo->vertAttrFlag |= VA_SKELETON;
// 		}

		// collect face index
		if (pMesh->HasFaces())
		{
			copyFaceIndex(pPieceInfo, pMesh->mFaces, pMesh->mNumFaces);
		}

		m_meshList.push_back(pPieceInfo);
	}

	for (uint i = 0; i < pNode->mNumChildren; ++i)
	{
		collectPieceInfo(pScene, pNode->mChildren[i]);
	}

	return true;
}

bool Convertor::copyVertexPos(MESH* pPieceInfo, const aiVector3D* pPos, uint numVerts)
{
	if (pPieceInfo->verts.size() < numVerts) pPieceInfo->verts.resize(numVerts);

	for (uint i = 0; i < numVerts; ++i)
	{
		pPieceInfo->verts[i].pos.x = pPos[i].x;
		pPieceInfo->verts[i].pos.y = pPos[i].y;
		pPieceInfo->verts[i].pos.z = pPos[i].z;
	}

	return true;
}

bool Convertor::copyVertexUv(MESH* pPieceInfo, int channel, const aiVector3D* pUv, uint numVerts)
{
	if (pPieceInfo->verts.size() < numVerts) pPieceInfo->verts.resize(numVerts);

	for (uint i = 0; i < numVerts; ++i)
	{
		pPieceInfo->verts[i].uv[channel].x = pUv[i].x;
		pPieceInfo->verts[i].uv[channel].y = pUv[i].y;
	}

	return true;
}

bool Convertor::copyVertexNormal(MESH* pPieceInfo, const aiVector3D* pNormal, uint numVerts)
{
	if (pPieceInfo->verts.size() < numVerts) pPieceInfo->verts.resize(numVerts);

	for (uint i = 0; i < numVerts; ++i)
	{
		pPieceInfo->verts[i].normal.x = pNormal[i].x;
		pPieceInfo->verts[i].normal.y = pNormal[i].y;
		pPieceInfo->verts[i].normal.z = pNormal[i].z;
	}

	return true;
}

bool Convertor::copyVertexTangentAndBinormal(MESH* pPieceInfo, const aiVector3D* pTangent, const aiVector3D* pBinormal, uint numVerts)
{
	if (pPieceInfo->verts.size() < numVerts) pPieceInfo->verts.resize(numVerts);

	for (uint i = 0; i < numVerts; ++i)
	{
		pPieceInfo->verts[i].tangent.x = pTangent[i].x;
		pPieceInfo->verts[i].tangent.y = pTangent[i].y;
		pPieceInfo->verts[i].tangent.z = pTangent[i].z;

		pPieceInfo->verts[i].binormal.x = pBinormal[i].x;
		pPieceInfo->verts[i].binormal.y = pBinormal[i].y;
		pPieceInfo->verts[i].binormal.z = pBinormal[i].z;
	}

	return true;
}

bool Convertor::copyFaceIndex(MESH* pPieceInfo, const aiFace* pFace, uint numFace)
{
	std::set<uint> vertsList;

	for (uint i = 0; i < numFace; ++i)
	{
		if (pFace[i].mNumIndices != 3) return false;

		// add face index
		pPieceInfo->indis.push_back(pFace[i].mIndices[0]);
		pPieceInfo->indis.push_back(pFace[i].mIndices[1]);
		pPieceInfo->indis.push_back(pFace[i].mIndices[2]);

		vertsList.insert(pFace[i].mIndices[0]);
		vertsList.insert(pFace[i].mIndices[1]);
		vertsList.insert(pFace[i].mIndices[2]);
	}

	return true;
}

uint Convertor::calculateStride(uint vertAttrs)
{
	static const uint s_attrSize[14] =
	{
		12,	// VA_POSITION = 0x00000001,
		8,	// VA_TEXCOORD0 = 0x00000002,
		8,	// VA_TEXCOORD1 = 0x00000004,
		8,	// VA_TEXCOORD2 = 0x00000008,
		8,	// VA_TEXCOORD3 = 0x00000010,
		8,	// VA_TEXCOORD4 = 0x00000020,
		8,	// VA_TEXCOORD5 = 0x00000040,
		8,	// VA_TEXCOORD6 = 0x00000080,
		8,	// VA_TEXCOORD7 = 0x00000100,
		4,	// VA_COLOR = 0x00000200,
		12,	// VA_NORMAL = 0x00000400,
		12,	// VA_TANGENT = 0x00000800,
		12,	// VA_BINORMAL = 0x00001000,
		32,	// VA_SKELETON = 0x00002000,
	};

	uint totalSize = 0;
	for (int i = 0; i < 14; ++i)
	{
		if (vertAttrs & (0x01 << i)) totalSize += s_attrSize[i];
	}

	return totalSize;
}

}
