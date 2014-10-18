/*!
 * \file Label.h
 * \date 10-18-2014 15:33:50
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "../base/PlatformDefine.h"

namespace spank
{

class IRenderer;
class IFont;
class VMemVertexBuffer;

class Label
{
public:
	Label(IRenderer* pRenderer, IFont* pFont);
	virtual ~Label();

	void setText(const std::string& text);
	inline const std::string& getText() const { return m_text; };

private:
	void clearElement();
	bool createElement(const std::string& text);

private:
	IRenderer* m_pRenderer{ nullptr };
	IFont* m_pFont{ nullptr };
	std::string m_text;

	VMemVertexBuffer* m_vertexBuffer{ nullptr };
	VMemVertexBuffer* m_indexBuffer{ nullptr };

};

}
