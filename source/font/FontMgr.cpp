/*!
 * \file FontMgr.cpp
 * \date 8-22-2013 19:57:51
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FontMgr.h"
#include "BitmapFont.h"

namespace spank
{

FontMgr::FontMgr()
{
	// TODO: 
}

FontMgr::~FontMgr()
{
	// TODO: 
}

bool FontMgr::initialize()
{
	// TODO: 
	return true;
}

void FontMgr::terminate()
{
	for (auto font : m_fontMap)
	{
		IFont* pFont = font.second;
		SAFE_DELETE(pFont);
	}
	m_fontMap.clear();
}

IFont* FontMgr::createFont(const std::string& filePath)
{
	// font font first
	TM_FONT::iterator it = m_fontMap.find(filePath);
	if (it != m_fontMap.end()) return it->second;

	// create new one
	BitmapFont* pBitmapFont = new BitmapFont(filePath, m_pRenderer);
	if (!pBitmapFont->loadFont(filePath)) return nullptr;

	// cache font into map
	m_fontMap.insert(std::make_pair(filePath, pBitmapFont));
	return pBitmapFont;
}

}
