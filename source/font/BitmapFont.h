﻿/*!
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
	BitmapFont(const tstring& strId, IRenderer* pRenderer);
	virtual ~BitmapFont();

	bool loadFont(const tstring& filePath);

	virtual int getLineHeight() const override { return m_lineHeight; };
	virtual int getLineBase() const override { return m_lineBase; };

	virtual const CHAR_INFO& getCharInfo(uint charId) override;
	virtual VertexAttributes* getVertexAttributes() override { return m_pVertAttrs; };

private:
	int m_lineHeight{ 0 };
	int m_lineBase{ 0 };

	IRenderer* m_pRenderer{ nullptr };
	VertexAttributes* m_pVertAttrs{ nullptr };

	TV_TEXTURE m_textureList;
	TM_CHAR_INFO m_charInfoMap;

};

}
