/*!
 * \file VertexAttributes.h
 * \date 10-14-2014 13:05:19
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "RenderObject.h"

class VertexAttributes : public RenderObject
{
public:
	enum CONST_DEFINE
	{
		MAX_ATTR_SIZE = 128,
		MAX_ATTRIBUTE_NAME_LENGTH = 32,
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
		GLuint size;
		ATTRIBUTE_ITEM_TYPE eItemType;
		GLenum eGlType;
		GLuint offset;
		char szParamName[MAX_ATTRIBUTE_NAME_LENGTH];
	} ATTRIBUTE_ITEM;

public:
	VertexAttributes();
	VertexAttributes(const ATTRIBUTE_ITEM* pAttrItems);
	virtual ~VertexAttributes();

	bool loadFromFile(const std::string& filePath);

	inline uint getStride() const { return m_attributeItems[m_numItems].offset; };
	inline int getNumAttributeItems() const { return m_numItems; };

	const ATTRIBUTE_ITEM* getAttributeItem(int nIndex) const;
	bool isEqual(const VertexAttributes* pVertexAttrs) const;

private:
	static GLenum getGlType(ATTRIBUTE_ITEM_TYPE eType);
	static GLuint getAttributeItemSize(uint nSize, ATTRIBUTE_ITEM_TYPE eType);
	static ATTRIBUTE_ITEM_TYPE getAttributeItemType(const std::string& strType);

	bool createVertexAttribute(const ATTRIBUTE_ITEM* pAttrItems);

private:
	int m_numItems;
	ATTRIBUTE_ITEM m_attributeItems[MAX_ATTRIBUTE_ITEMS + 1];

};
