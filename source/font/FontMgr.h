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
	typedef std::map<std::string, IFont*> TM_FONT;

public:
	FontMgr();
	~FontMgr();

	virtual bool initialize() override;
	virtual void terminate() override;

	void setRenderer(IRenderer* pRenderer) { m_pRenderer = pRenderer; };

	IFont* createFont(const std::string& filePath);

private:
	IRenderer* m_pRenderer{ nullptr };
	TM_FONT m_fontMap;

};

}
