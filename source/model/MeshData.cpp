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
#include "../utils/BufferStream.h"
#include "../utils/FileUtil.h"

namespace spank
{

MeshData::MeshData(ModelMgr* pModelMgr, IRenderer* pRenderer)
	:m_pModelMgr(pModelMgr)
	,m_pRenderer(pRenderer)
{

}

MeshData::~MeshData()
{
	// destroy buffers
	destroyBuffers();
}

bool MeshData::loadFromFile(const std::string& filePath)
{
	BUFFER_DATA bufferData;
	if (!FileUtil::readFile(bufferData, filePath)) return false;

	BufferStream bufferStream(bufferData);
	if (parseMeshFile(&bufferStream))
	{
		setId(filePath);
		return true;
	}

	return false;
}

void MeshData::preDelete()
{
	m_pModelMgr->removeMeshData(this);
}

bool MeshData::parseMeshFile(BufferStream* pStream)
{
	if (!pStream) return false;

	// first, read the header info
	pStream->read(&header, sizeof(header));

	// check file format valid
	if (header.nMagicNumber != MeshFileFormat::MAGIC_NUMBER || header.nVersion != MeshFileFormat::CURRENT_VERSION) return false;

	// second, read piece info into list
	MeshFileFormat::TV_PIECE_INFO pieceInfoList;
	if (header.nNumPieces > 0)
	{
		pieceInfoList.resize(header.nNumPieces);
		pStream->read(&pieceInfoList[0], sizeof(MeshFileFormat::PIECE_INFO)*header.nNumPieces);
	}

	BUFFER_DATA verts;
	BUFFER_DATA indis;

	// final, for each piece read the vertex attributes into piece info
	for (const auto& pieceInfo : pieceInfoList)
	{
		RENDER_PIECE_INFO* pRenderPieceInfo = new RENDER_PIECE_INFO();
		pRenderPieceInfo->pieceInfo = pieceInfo;

		// read vertex data
		verts.resize(pieceInfo.nSizeOfVerts);
		pStream->read(verts.data(), pieceInfo.nSizeOfVerts);

		// read index data
		indis.resize(pieceInfo.nSizeOfIndis);
		pStream->read(indis.data(), pieceInfo.nSizeOfIndis);

		// create vertex buffer object
		pRenderPieceInfo->pVertAttrs = m_pRenderer->createVertexAttributes("data/shaders/pos3_uv2_normal.attrs");
		pRenderPieceInfo->pVertexBuffer = m_pRenderer->createVMemVertexBuffer(pRenderPieceInfo->pVertAttrs);
		pRenderPieceInfo->pVertexBuffer->uploadBuffer(verts.data(), verts.size());

		// create index buffer object
		pRenderPieceInfo->pIndexBuffer = m_pRenderer->createVMemIndexBuffer();
		pRenderPieceInfo->pIndexBuffer->uploadBuffer(indis.data(), indis.size());

		renderPieceInfoList.push_back(pRenderPieceInfo);
	}

	return true;
}

void MeshData::destroyBuffers()
{
	for (auto& renderPieceInfo : renderPieceInfoList)
	{
		SAFE_RELEASE(renderPieceInfo->pVertAttrs);
		SAFE_RELEASE(renderPieceInfo->pVertexBuffer);
		SAFE_RELEASE(renderPieceInfo->pIndexBuffer);
		SAFE_DELETE(renderPieceInfo);
	}
	renderPieceInfoList.clear();
}

}
