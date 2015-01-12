/*!
 * \file MeshData.cpp
 * \date 10-22-2014 17:08:57
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "MeshData.h"
#include "ModelMgr.h"
#include "../render/RenderBuffer.h"
#include "../render/VertexAttributes.h"
#include "../render/IRenderer.h"
#include "../render/Texture.h"
#include "../render/Shader.h"
#include "../utils/BufferStream.h"
#include "../utils/FileUtil.h"
#include "../utils/StringUtil.h"
#include "../utils/LogUtil.h"

namespace spank
{

MeshData::MeshData(ModelMgr* pModelMgr, IRenderer* pRenderer)
	:m_pModelMgr(pModelMgr)
	,m_pRenderer(pRenderer)
{

}

MeshData::~MeshData()
{
	// destroy
	destroy();
}

bool MeshData::loadFromFile(const std::string& filePath)
{
	BUFFER_DATA bufferData;
	if (!FileUtil::readFile(bufferData, filePath)) return false;

	std::string baseDir = StringUtil::getFileDir(filePath);

	BufferStream bufferStream(bufferData);
	if (parseMeshFile(&bufferStream, baseDir))
	{
		setId(filePath);
		return true;
	}

	return false;
}

Texture* MeshData::getMaterialTexDiffuse(int materialId)
{
	if (materialId < 0 || materialId >= (int)m_materialItemList.size()) return nullptr;
	if (m_materialItemList[materialId].pTexDiffuse) return m_materialItemList[materialId].pTexDiffuse;

	m_materialItemList[materialId].pTexDiffuse = m_pRenderer->createTexture(m_materialItemList[materialId].texDiffuseFullPath);
	return m_materialItemList[materialId].pTexDiffuse;
}

void MeshData::preDelete()
{
	m_pModelMgr->removeMeshData(this);
}

bool MeshData::parseMeshFile(BufferStream* pStream, const std::string& baseDir)
{
	destroy();

	if (!pStream) return false;

	// 1, read the header info
	pStream->read(&header, sizeof(header));

	// check file format valid
	if (header.nMagicNumber != MeshFileFormat::MAGIC_NUMBER || header.nVersion != MeshFileFormat::CURRENT_VERSION) return false;

	// 2, read material list
	if (header.nNumMaterials > 0)
	{
		m_materialItemList.resize(header.nNumMaterials);
		for (int i = 0; i < header.nNumMaterials; ++i)
		{
			pStream->read(&m_materialItemList[i].materialInfo, sizeof(m_materialItemList[i].materialInfo));
			m_materialItemList[i].texDiffuseFullPath = baseDir + "/" + m_materialItemList[i].materialInfo.szTexDiffuse;
		}
	}

	// 3, read piece info into list
	MeshFileFormat::TV_PIECE_INFO pieceInfoList;
	if (header.nNumPieces > 0)
	{
		pieceInfoList.resize(header.nNumPieces);
		pStream->read(&pieceInfoList[0], sizeof(MeshFileFormat::PIECE_INFO)*header.nNumPieces);
	}

	BUFFER_DATA verts;
	BUFFER_DATA indis;

	// 4, for each piece read the vertex attributes into piece info
	for (const auto& pieceInfo : pieceInfoList)
	{
		// create shader for piece
		std::string shaderFullPath = m_pRenderer->getShaderBaseDir() + "/" + pieceInfo.szShader;
		Shader* pShader = m_pRenderer->createShader(shaderFullPath);
		if (!pShader)
		{
			LOGE("Get piece shader failed, shader file=%s", shaderFullPath.data());
			return false;
		}

		RENDER_PIECE_INFO* pRenderPieceInfo = new RENDER_PIECE_INFO();
		pRenderPieceInfo->pieceInfo = pieceInfo;

		// read vertex data
		verts.resize(pieceInfo.nSizeOfVerts);
		pStream->read(verts.data(), pieceInfo.nSizeOfVerts);

		// read index data
		indis.resize(pieceInfo.nSizeOfIndis);
		pStream->read(indis.data(), pieceInfo.nSizeOfIndis);

		// create vertex buffer object
		pRenderPieceInfo->pShader = pShader;
		pRenderPieceInfo->pVertexBuffer = m_pRenderer->createVMemVertexBuffer(pShader->getVertexAttributes());
		pRenderPieceInfo->pVertexBuffer->uploadBuffer(verts.data(), verts.size());

		// create index buffer object
		pRenderPieceInfo->pIndexBuffer = m_pRenderer->createVMemIndexBuffer();
		pRenderPieceInfo->pIndexBuffer->uploadBuffer(indis.data(), indis.size());

		renderPieceInfoList.push_back(pRenderPieceInfo);
	}

	return true;
}

void MeshData::destroy()
{
	for (auto& renderPieceInfo : renderPieceInfoList)
	{
		SAFE_RELEASE(renderPieceInfo->pShader);
		SAFE_RELEASE(renderPieceInfo->pVertexBuffer);
		SAFE_RELEASE(renderPieceInfo->pIndexBuffer);
		SAFE_DELETE(renderPieceInfo);
	}
	renderPieceInfoList.clear();

	for (auto& materialItem : m_materialItemList)
	{
		SAFE_RELEASE(materialItem.pTexDiffuse);
	}
	m_materialItemList.clear();
}

}
