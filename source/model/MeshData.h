/*!
 * \file MeshData.h
 * \date 10-22-2014 17:03:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "../base/PlatformDefine.h"
#include "../render/RenderObject.h"
#include "MeshFileFormat.h"

namespace spank
{

class BufferStream;
class VertexAttributes;
class VMemVertexBuffer;
class VMemIndexBuffer;
class Texture;
class IRenderer;
class ModelMgr;

/*
 * the class hold the mesh data info-s
 * each mesh file contain serval pieces, each piece contain the rendering data for render (pos, uv, ...)
 */
class MeshData : public RenderObject
{
public:
	friend class ModelMgr;

	typedef struct MATERIAL_ITEM_tag
	{
		MeshFileFormat::MATERIAL_INFO materialInfo;
		std::string texDiffuseFullPath;
		Texture* pTexDiffuse{ nullptr };
	} MATERIAL_ITEM;
	typedef std::vector<MATERIAL_ITEM> TV_MATERIAL_ITEM;

	typedef struct RENDER_PIECE_INFO_tag
	{
		MeshFileFormat::PIECE_INFO pieceInfo;
		VertexAttributes* pVertAttrs{ nullptr };
		VMemVertexBuffer* pVertexBuffer{ nullptr };
		VMemIndexBuffer* pIndexBuffer{ nullptr };
	} RENDER_PIECE_INFO;
	typedef std::vector<RENDER_PIECE_INFO*> TV_RENDER_PIECE_INFO;

public:
	/*!
	 * \brief load mesh from file
	 * \param filePath the mesh file path
	 * \return return true if success, otherwise return false
	 */
	bool loadFromFile(const std::string& filePath);

	Texture* getMaterialTexDiffuse(int materialId);

protected:
	MeshData(ModelMgr* pModelMgr, IRenderer* pRenderer);
	~MeshData();

	virtual void preDelete() override;

private:
	/*!
	 * \brief parse mesh file from data stream
	 * \param pReader the stream of mesh file
	 * \return return true if parse success, otherwise return false
	 */
	bool parseMeshFile(BufferStream* pStream, const std::string& baseDir);

	/*!
	 * \brief destroy all resources
	 * \return 
	 */
	void destroy();

public:
	MeshFileFormat::FILE_HEADER header;
	TV_RENDER_PIECE_INFO renderPieceInfoList;

private:
	IRenderer* m_pRenderer{ nullptr };
	ModelMgr* m_pModelMgr{ nullptr };
	TV_MATERIAL_ITEM m_materialItemList;

};

}
