/*!
 * \file BitmapFont.h
 * \date 10-18-2014 14:33:38
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "IFont.h"
#include <vector>

namespace spank
{

class IRenderer;

class BitmapFont : public IFont
{
public:
	typedef std::vector<Texture*> TV_TEXTURE;

public:
	BitmapFont(const std::string& strId, IRenderer* pRenderer);
	virtual ~BitmapFont();

	bool loadFont(const std::string& filePath);

	virtual int getFontSize() const override { return m_nFontSize; };
	virtual const CHAR_INFO* getCharInfo(uint charId) override;

private:
	int m_nFontSize{ 0 };
	IRenderer* m_pRenderer{ nullptr };

	TV_TEXTURE m_textureList;
	TM_CHAR_INFO m_charInfoMap;

};

}
