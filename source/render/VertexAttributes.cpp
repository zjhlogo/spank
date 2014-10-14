/*!
 * \file VertexAttributes.cpp
 * \date 10-14-2014 13:05:25
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "VertexAttributes.h"
#include <libTinyxml2/source/tinyxml2.h>
#include <utils/FileUtil.h>

VertexAttributes::VertexAttributes()
{
	// TODO: 
}

VertexAttributes::VertexAttributes(const ATTRIBUTE_ITEM* pAttrItems)
{
	m_numItems = 0;
	memset(m_attributeItems, 0, sizeof(m_attributeItems));
	createVertexAttribute(pAttrItems);
}

VertexAttributes::~VertexAttributes()
{
	// TODO: 
}

bool VertexAttributes::loadFromFile(const std::string& filePath)
{
	std::string xmlData;
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
		attrItems[attrIndex].eItemType = getAttributeItemType(pszType);
		attrItems[attrIndex].eGlType = getGlType(attrItems[attrIndex].eItemType);
		strncpy(attrItems[attrIndex].szParamName, pszType, MAX_ATTRIBUTE_NAME_LENGTH);

		++attrIndex;
	}

	if (attrIndex <= 0 || attrIndex > MAX_ATTRIBUTE_ITEMS) return false;

	attrItems[attrIndex].size = 0;
	attrItems[attrIndex].eItemType = AIT_UNKNOWN;
	attrItems[attrIndex].eGlType = getGlType(attrItems[attrIndex].eItemType);
	attrItems[attrIndex].offset = 0;
	attrItems[attrIndex].szParamName[0] = '\0';

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
		if (m_attributeItems[i].eItemType != pAttrItem->eItemType) return false;
		if (strncmp(m_attributeItems[i].szParamName, pAttrItem->szParamName, MAX_ATTRIBUTE_NAME_LENGTH) != 0) return false;
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

VertexAttributes::ATTRIBUTE_ITEM_TYPE VertexAttributes::getAttributeItemType(const std::string& strType)
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
	while (pCurrItem && pCurrItem->eItemType != AIT_UNKNOWN)
	{
		nNumItems++;
		pCurrItem++;
	}

	if (nNumItems <= 0 || nNumItems > MAX_ATTRIBUTE_ITEMS) return false;

	m_numItems = nNumItems;
	uint nOffset = 0;
	for (int i = 0; i < nNumItems; ++i)
	{
		m_attributeItems[i].size = pAttrItems[i].size;
		m_attributeItems[i].eItemType = pAttrItems[i].eItemType;
		m_attributeItems[i].eGlType = pAttrItems[i].eGlType;
		m_attributeItems[i].offset = nOffset;
		strncpy(m_attributeItems[i].szParamName, pAttrItems[i].szParamName, MAX_ATTRIBUTE_NAME_LENGTH);
		nOffset += getAttributeItemSize(m_attributeItems[i].size, m_attributeItems[i].eItemType);
	}

	m_attributeItems[m_numItems].size = 0;
	m_attributeItems[m_numItems].eItemType = AIT_UNKNOWN;
	m_attributeItems[m_numItems].eGlType = getGlType(AIT_UNKNOWN);
	m_attributeItems[m_numItems].offset = nOffset;
	m_attributeItems[m_numItems].szParamName[0] = '\0';

	return true;
}
