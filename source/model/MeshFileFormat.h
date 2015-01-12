/*!
 * \file MeshFileFormat.h
 * \date 10-22-2014 16:55:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "../base/PlatformDefine.h"

namespace spank
{

class MeshFileFormat
{
public:
	enum CONST_DEFINE
	{
		MAGIC_NUMBER = 0x4853454D,		// file magic number ('MESH')
		CURRENT_VERSION = 120,
		PIECE_NAME_SIZE = 32,
		MAX_FILE_LENGTH = 64,
		MAX_NUMBER_OF_PIECE = 256,
		MAX_TEX_COORDS = 8,
	};

	// attributes for each vertex
	enum VERTEX_ATTRIBUTES
	{
		VA_POSITION		= 0x00000001,
		VA_TEXCOORD0	= 0x00000002,
		VA_TEXCOORD1	= 0x00000004,
		VA_TEXCOORD2	= 0x00000008,
		VA_TEXCOORD3	= 0x00000010,
		VA_TEXCOORD4	= 0x00000020,
		VA_TEXCOORD5	= 0x00000040,
		VA_TEXCOORD6	= 0x00000080,
		VA_TEXCOORD7	= 0x00000100,
		VA_COLOR		= 0x00000200,
		VA_NORMAL		= 0x00000400,
		VA_TANGENT		= 0x00000800,
		VA_BINORMAL		= 0x00001000,
		VA_SKELETON		= 0x00002000,
	};

	// the mesh piece mask
	enum PIECE_MASK
	{
		PM_VISIBLE		= 0x00000001,
		PM_TRANSPARENT	= 0x00000002,
	};

	// the .mesh file format organize as following:
	// 1, the file header
	typedef struct FILE_HEADER_tag
	{
		uint nMagicNumber{ MAGIC_NUMBER };				// always MAGIC_NUMBER
		int nVersion{ CURRENT_VERSION };				// CURRENT_VERSION

		float fBoundingBoxMin[3]{};
		float fBoundingBoxMax[3]{};

		int nNumMaterials{ 0 };
		int nNumSkelectons{ 0 };
		int nNumPieces{ 0 };
	} FILE_HEADER;

	// 2, the nNumMaterials of MATERIAL_INFO
	typedef struct MATERIAL_INFO_tag
	{
		int id{ -1 };
		char szTexDiffuse[MAX_FILE_LENGTH] {};
	} MATERIAL_INFO;
	typedef std::vector<MATERIAL_INFO> TV_MATERIAL_INFO;

	// 3, the nNumSkelectons of SKELECTON_INFO
	typedef struct SKELECTION_INFO_tag
	{
		float matTransform[16];

	} SKELECTON_INFO;

	// 4, the nNumPieces of PIECE_INFO
	typedef struct PIECE_INFO_tag
	{
		char szName[PIECE_NAME_SIZE] {};
		uint nPieceMask{ 0 };					// see PIECE_MASK
		uint nVertexAttributes{ 0 };			// see VERTEX_ATTRIBUTES

		int nMaterialId{ -1 };					// see material id
		char szShader[MAX_FILE_LENGTH] {};

		int nNumVerts{ 0 };
		uint nOffVerts{ 0 };
		uint nSizeOfVerts{ 0 };					// = sizeof(VERTEX)*nNumVerts

		int nNumIndis{ 0 };
		uint nOffIndis{ 0 };
		uint nSizeOfIndis{ 0 };					// = sizeof(ushort)*nNumIndis*3
	} PIECE_INFO;
	typedef std::vector<PIECE_INFO> TV_PIECE_INFO;

};

}
