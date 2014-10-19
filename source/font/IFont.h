/*!
 * \file IFont.h
 * \date 10-18-2014 14:28:13
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "../base/PlatformDefine.h"
#include <glm/glm.hpp>
#include <map>

namespace spank
{

class Texture;
class VertexAttributes;

class IFont
{
public:
	typedef struct CHAR_INFO_tag
	{
		uint charId{ 0 };
		glm::vec2 size;
		glm::vec2 uv;
		glm::vec2 duv;
		glm::vec2 offset;
		float xadvance{ 0.0f };
		Texture* pTexture{ nullptr };
		IFont* pFont{ nullptr };
	} CHAR_INFO;

	typedef std::map<uint, CHAR_INFO> TM_CHAR_INFO;

	enum FONT_STATE
	{
		FONT_STATE_NO_DISTANCE_FIELD = 0x00000001,
	};

public:
	IFont(const std::string& strId);
	virtual ~IFont();

	inline const std::string& getFontId() const { return m_strFontId; };

	virtual int getLineHeight() const = 0;
	virtual int getLineBase() const = 0;

	virtual const CHAR_INFO& getCharInfo(uint charId) = 0;
	virtual VertexAttributes* getVertexAttributes() { return nullptr; };

	bool setFontState(int state, bool set);
	inline bool checkFontState(int state) const { return ((m_nFontState & state) == state); };

private:
	std::string m_strFontId;
	int m_nFontState{ 0 };

};

}
