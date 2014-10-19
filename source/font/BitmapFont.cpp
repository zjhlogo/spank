/*!
 * \file BitmapFont.cpp
 * \date 9-5-2013 15:01:08
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "BitmapFont.h"
#include "../render/IRenderer.h"
#include "../render/VertexAttributes.h"
#include "../render/Texture.h"
#include "../utils/FileUtil.h"
#include "../utils/LogUtil.h"
#include "../utils/StringUtil.h"

#include <libTinyxml2/source/tinyxml2.h>

namespace spank
{

BitmapFont::BitmapFont(const std::string& strId, IRenderer* pRenderer)
	:IFont(strId)
	, m_pRenderer(pRenderer)
{
	m_pVertAttrs = m_pRenderer->createVertexAttributes("data/shaders/pos3_uv2.attrs");
}

BitmapFont::~BitmapFont()
{
	SAFE_RELEASE(m_pVertAttrs);

	for (auto pTexture : m_textureList)
	{
		SAFE_RELEASE(pTexture);
	}
	m_textureList.clear();
}

const IFont::CHAR_INFO& BitmapFont::getCharInfo(uint charId)
{
	static const CHAR_INFO s_charInfo;

	TM_CHAR_INFO::iterator it = m_charInfoMap.find(charId);
	if (it == m_charInfoMap.end()) return s_charInfo;
	return it->second;
}

bool BitmapFont::loadFont(const std::string& filePath)
{
	std::string xmlData;
	if (!FileUtil::readStringFile(xmlData, filePath))
	{
		LOGE("Load Bitmap font failed %s", filePath.c_str());
		return false;
	}

	tinyxml2::XMLDocument doc;
	if (doc.Parse(xmlData.c_str()) != tinyxml2::XML_SUCCESS)
	{
		LOGE("Parse bitmap font failed %s", filePath.c_str());
		return false;
	}

	std::string strDir = StringUtil::getFileDir(filePath);

	tinyxml2::XMLElement* pXmlFont = doc.RootElement();
	if (!pXmlFont) return false;

	tinyxml2::XMLElement* pXmlInfo = pXmlFont->FirstChildElement("info");
	if (!pXmlInfo) return false;

	tinyxml2::XMLElement* pXmlCommon = pXmlFont->FirstChildElement("common");
	if (!pXmlCommon) return false;

	pXmlCommon->QueryIntAttribute("lineHeight", &m_lineHeight);
	pXmlCommon->QueryIntAttribute("base", &m_lineBase);
	int lineBaseInv = m_lineHeight - m_lineBase;

	float texWidth = 1.0f;
	float texHeight = 1.0f;
	pXmlCommon->QueryFloatAttribute("scaleW", &texWidth);
	pXmlCommon->QueryFloatAttribute("scaleH", &texHeight);

	tinyxml2::XMLElement* pXmlPageType = pXmlFont->FirstChildElement("pages");
	tinyxml2::XMLElement* pXmlPage = pXmlPageType->FirstChildElement("page");
	while (pXmlPage)
	{
		std::string strTexturePath = pXmlPage->Attribute("file");
		strTexturePath = strDir + "/" + strTexturePath;

		Texture* pFontTexture = m_pRenderer->createTexture(strTexturePath);
		if (!pFontTexture) return false;

		m_textureList.push_back(pFontTexture);

		pXmlPage = pXmlPage->NextSiblingElement("page");
	}

	tinyxml2::XMLElement* pXmlFontType = pXmlFont->FirstChildElement("chars");
	tinyxml2::XMLElement* pXmlChar = pXmlFontType->FirstChildElement("char");
	while (pXmlChar)
	{
		int pageIndex = 0;
		pXmlChar->QueryIntAttribute("page", &pageIndex);
		if (pageIndex < 0 || pageIndex >= (int)m_textureList.size())
		{
			LOGE("Load bitmap font failed, pageIndex = %d error", pageIndex);
			return false;
		}

		CHAR_INFO charInfo;
		pXmlChar->QueryUnsignedAttribute("id", &charInfo.charId);

		pXmlChar->QueryFloatAttribute("width", &charInfo.size.x);
		pXmlChar->QueryFloatAttribute("height", &charInfo.size.y);

		pXmlChar->QueryFloatAttribute("x", &charInfo.uv.x);
		pXmlChar->QueryFloatAttribute("y", &charInfo.uv.y);

		charInfo.uv.x /= texWidth;
		charInfo.uv.y = 1.0f - (charInfo.uv.y + charInfo.size.y) / texHeight;

		charInfo.duv.x = charInfo.size.x / texWidth;
		charInfo.duv.y = charInfo.size.y / texHeight;

		pXmlChar->QueryFloatAttribute("xoffset", &charInfo.offset.x);
		pXmlChar->QueryFloatAttribute("yoffset", &charInfo.offset.y);
		charInfo.offset.y = m_lineHeight - charInfo.size.y - charInfo.offset.y + lineBaseInv;
		pXmlChar->QueryFloatAttribute("xadvance", &charInfo.xadvance);
		charInfo.pTexture = m_textureList[pageIndex];
		charInfo.pFont = this;

		m_charInfoMap.insert(std::make_pair(charInfo.charId, charInfo));

		pXmlChar = pXmlChar->NextSiblingElement("char");
	}

	return true;
}

}
