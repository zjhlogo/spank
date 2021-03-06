/*!
 * \file VertexAttributes.cpp
 * \date 10-14-2014 13:05:25
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "VertexAttributes.h"
#include "IRenderer.h"
#include "../utils/FileUtil.h"

#include <libTinyxml2/source/tinyxml2.h>

namespace spank
{

VertexAttributes::VertexAttributes(IRenderer* pRenderer)
	:m_pRenderer(pRenderer)
{
	// TODO: 
}

VertexAttributes::VertexAttributes(IRenderer* pRenderer, const ATTRIBUTE_ITEM* pAttrItems)
	:m_pRenderer(pRenderer)
{
	createVertexAttribute(pAttrItems);
}

VertexAttributes::~VertexAttributes()
{
	// TODO: 
}

bool VertexAttributes::loadFromFile(const tstring& filePath)
{
	tstring xmlData;
	if (!FileUtil::readStringFile(xmlData, filePath)) return false;

	tinyxml2::XMLDocument doc;
	if (doc.Parse(xmlData.data()) != tinyxml2::XML_SUCCESS) return false;

	tinyxml2::XMLElement* pXmlRoot = doc.RootElement();
	if (!pXmlRoot) return false;

	ATTRIBUTE_ITEM attrItems[MAX_ATTRIBUTE_ITEMS + 1];
	int attrIndex = 0;

	for (tinyxml2::XMLElement* pXmlAttr = pXmlRoot->FirstChildElement(); pXmlAttr != nullptr; pXmlAttr = pXmlAttr->NextSiblingElement())
	{
		int size = 0;
		pXmlAttr->QueryAttribute("size", &size);
		if (size <= 0 || size > MAX_ATTR_SIZE) return false;

		const char* pszType = pXmlAttr->Attribute("type");
		if (!pszType) return false;

		const char* pszName = pXmlAttr->Attribute("name");
		if (!pszName) return false;

		attrItems[attrIndex].size = size;
		attrItems[attrIndex].attrType = getAttributeItemType(pszType);
		attrItems[attrIndex].glType = getGlType(attrItems[attrIndex].attrType);
		attrItems[attrIndex].name = pszName;

		++attrIndex;
	}

	if (attrIndex <= 0 || attrIndex > MAX_ATTRIBUTE_ITEMS) return false;

	attrItems[attrIndex].size = 0;
	attrItems[attrIndex].attrType = AIT_UNKNOWN;
	attrItems[attrIndex].glType = getGlType(attrItems[attrIndex].attrType);
	attrItems[attrIndex].offset = 0;
	attrItems[attrIndex].name.clear();

	if (createVertexAttribute(attrItems))
	{
		setId(filePath);
		return true;
	}

	return false;
}

const VertexAttributes::ATTRIBUTE_ITEM* VertexAttributes::getAttributeItem(int nIndex) const
{
	if (nIndex < 0 || nIndex >= m_numItems) return NULL;
	return &m_attributeItems[nIndex];
}

bool VertexAttributes::isEqual(const VertexAttributes* pVertexAttrs) const
{
	if (!pVertexAttrs) return false;

	if (m_numItems != pVertexAttrs->getNumAttributeItems()) return false;

	for (int i = 0; i < m_numItems; ++i)
	{
		const ATTRIBUTE_ITEM* pAttrItem = pVertexAttrs->getAttributeItem(i);

		if (m_attributeItems[i].size != pAttrItem->size) return false;
		if (m_attributeItems[i].attrType != pAttrItem->attrType) return false;
		if (m_attributeItems[i].name != pAttrItem->name) return false;
	}

	return true;
}

GLenum VertexAttributes::getGlType(ATTRIBUTE_ITEM_TYPE eType)
{
	static const GLenum s_GlType[NUM_AIT] =
	{
		GL_FLOAT,			// AT_UNKNOWN,
		GL_BYTE,			// AT_BYTE,
		GL_UNSIGNED_BYTE,	// AT_UNSIGNED_BYTE,
		GL_SHORT,			// AT_SHORT,
		GL_UNSIGNED_SHORT,	// AT_UNSIGNED_SHORT,
		GL_FLOAT,			// AT_FLOAT,
		GL_FIXED,			// AT_FIXED,
	};

	if (eType < AIT_UNKNOWN || eType >= NUM_AIT) return GL_FLOAT;
	return s_GlType[eType];
}

GLuint VertexAttributes::getAttributeItemSize(uint nSize, ATTRIBUTE_ITEM_TYPE eType)
{
	static const int s_ItemSizes[NUM_AIT] =
	{
		0, // AIT_UNKNOWN,
		1, // AIT_BYTE,
		1, // AIT_UNSIGNED_BYTE,
		2, // AIT_SHORT,
		2, // AIT_UNSIGNED_SHORT,
		4, // AIT_FLOAT,
		4, // AIT_FIXED,
	};

	if (eType <= AIT_UNKNOWN || eType >= NUM_AIT) return 0;
	return nSize*s_ItemSizes[eType];
}

VertexAttributes::ATTRIBUTE_ITEM_TYPE VertexAttributes::getAttributeItemType(const tstring& strType)
{
	if (strType == "AIT_UNKNOWN") return AIT_UNKNOWN;
	else if (strType == "AIT_BYTE") return AIT_BYTE;
	else if (strType == "AIT_UNSIGNED_BYTE") return AIT_UNSIGNED_BYTE;
	else if (strType == "AIT_SHORT") return AIT_SHORT;
	else if (strType == "AIT_UNSIGNED_SHORT") return AIT_UNSIGNED_SHORT;
	else if (strType == "AIT_FLOAT") return AIT_FLOAT;
	else if (strType == "AIT_FIXED") return AIT_FIXED;
	return AIT_UNKNOWN;
}

bool VertexAttributes::createVertexAttribute(const ATTRIBUTE_ITEM* pAttrItems)
{
	int nNumItems = 0;
	const ATTRIBUTE_ITEM* pCurrItem = pAttrItems;
	while (pCurrItem && pCurrItem->attrType != AIT_UNKNOWN)
	{
		nNumItems++;
		pCurrItem++;
	}

	if (nNumItems <= 0 || nNumItems > MAX_ATTRIBUTE_ITEMS) return false;

	m_numItems = nNumItems;
	uint currOffset = 0;
	for (int i = 0; i < nNumItems; ++i)
	{
		m_attributeItems[i].size = pAttrItems[i].size;
		m_attributeItems[i].attrType = pAttrItems[i].attrType;
		m_attributeItems[i].glType = pAttrItems[i].glType;
		m_attributeItems[i].offset = currOffset;
		m_attributeItems[i].name = pAttrItems[i].name;
		currOffset += getAttributeItemSize(m_attributeItems[i].size, m_attributeItems[i].attrType);
	}

	m_attributeItems[m_numItems].size = 0;
	m_attributeItems[m_numItems].attrType = AIT_UNKNOWN;
	m_attributeItems[m_numItems].glType = getGlType(AIT_UNKNOWN);
	m_attributeItems[m_numItems].offset = currOffset;
	m_attributeItems[m_numItems].name.clear();

	return true;
}

void VertexAttributes::preDelete()
{
	m_pRenderer->removeVertexAttributes(this);
}

}
