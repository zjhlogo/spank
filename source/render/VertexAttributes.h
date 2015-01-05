/*!
 * \file VertexAttributes.h
 * \date 10-14-2014 13:05:19
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "RenderObject.h"

namespace spank
{

class IRenderer;

class VertexAttributes : public RenderObject
{
	friend class RendererGl2;

public:
	enum CONST_DEFINE
	{
		MAX_ATTR_SIZE = 128,
		MAX_ATTRIBUTE_ITEMS = 8,
	};

	enum ATTRIBUTE_ITEM_TYPE
	{
		AIT_UNKNOWN = 0,
		AIT_BYTE,
		AIT_UNSIGNED_BYTE,
		AIT_SHORT,
		AIT_UNSIGNED_SHORT,
		AIT_FLOAT,
		AIT_FIXED,
		NUM_AIT,
	};

	typedef struct ATTRIBUTE_ITEM_tag
	{
		GLuint size{ 0 };
		ATTRIBUTE_ITEM_TYPE attrType{ AIT_UNKNOWN };
		GLenum glType{ GL_FLOAT };
		GLuint offset{ 0 };
		std::string name;
	} ATTRIBUTE_ITEM;

public:
	bool loadFromFile(const std::string& filePath);

	inline uint getStride() const { return m_attributeItems[m_numItems].offset; };
	inline int getNumAttributeItems() const { return m_numItems; };

	const ATTRIBUTE_ITEM* getAttributeItem(int nIndex) const;
	bool isEqual(const VertexAttributes* pVertexAttrs) const;

protected:
	VertexAttributes(IRenderer* pRenderer);
	VertexAttributes(IRenderer* pRenderer, const ATTRIBUTE_ITEM* pAttrItems);
	virtual ~VertexAttributes();

	virtual void preDelete() override;

private:
	static GLenum getGlType(ATTRIBUTE_ITEM_TYPE eType);
	static GLuint getAttributeItemSize(uint nSize, ATTRIBUTE_ITEM_TYPE eType);
	static ATTRIBUTE_ITEM_TYPE getAttributeItemType(const std::string& strType);

	bool createVertexAttribute(const ATTRIBUTE_ITEM* pAttrItems);

private:
	IRenderer* m_pRenderer{ nullptr };
	int m_numItems{ 0 };
	ATTRIBUTE_ITEM m_attributeItems[MAX_ATTRIBUTE_ITEMS + 1];

};

// pre-define vertex attributes
typedef struct VERT_ATTR_POS3_tag
{
	float x, y, z;		// pos3
} VERT_ATTR_POS3;

typedef struct VERT_ATTR_POS3_UV2_tag
{
	float x, y, z;		// pos3
	float u, v;			// uv2
} VERT_ATTR_POS3_UV2;

}
