/*!
 * \file IFont.cpp
 * \date 10-18-2014 14:31:42
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "IFont.h"

namespace spank
{

IFont::IFont(const std::string& strId)
	:m_strFontId(strId)
{
	// TODO: 
}

IFont::~IFont()
{
	// TODO: 
}

bool IFont::setFontState(int state, bool set)
{
	int oldState = m_nFontState;
	if (set) m_nFontState |= state;
	else m_nFontState &= (~state);
	return (oldState != m_nFontState);
}

}
