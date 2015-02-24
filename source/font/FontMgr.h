/*!
 * \file FontMgr.h
 * \date 10-18-2014 14:56:55
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "../base/IMgr.h"
#include "IFont.h"
#include <map>

namespace spank
{

class IRenderer;

class FontMgr : public IMgr
{
public:
	typedef std::map<tstring, IFont*> TM_FONT;

public:
	FontMgr(IRenderer* pRenderer);
	~FontMgr();

	virtual bool initialize() override;
	virtual void terminate() override;

	IFont* createFont(const tstring& filePath);

private:
	IRenderer* m_pRenderer{ nullptr };
	TM_FONT m_fontMap;

};

}
