/*!
 * \file Label.cpp
 * \date 10-18-2014 15:34:07
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Label.h"
#include "../font/IFont.h"
#include "../render/RenderBuffer.h"

namespace spank
{

Label::Label(IRenderer* pRenderer, IFont* pFont)
	:m_pRenderer(pRenderer)
	, m_pFont(pFont)
{
	// TODO: 
}

Label::~Label()
{
	// TODO: 
}

void Label::setText(const std::string& text)
{
	if (m_text == text) return;
	m_text = text;

	// 
	createElement(m_text);
}

void Label::clearElement()
{
	// TODO: 
}

bool Label::createElement(const std::string& text)
{
// 	clearElement();
// 
// 	if (!m_vertexBuffer)
// 	{
// 		m_vertexBuffer = m_pRenderer->createVMemRenderBuffer(m_pFont->getVertexAttribute());
// 		if (!m_vertexBuffer) return false;
// 	}
// 
// 	if (!m_indexBuffer)
// 	{
// 		m_indexBuffer = m_pRenderer->createVMemRenderBuffer(m_pFont->getVertexAttribute());
// 		if (!m_vertexBuffer) return false;
// 	}
// 
// 	glm::vec2 currPos;
// 	for (const auto& charId : text)
// 	{
// 		const IFont::CHAR_INFO* pCharInfo = m_pFont->getCharInfo(charId);
// 		if (!pCharInfo) continue;
// 
// 		CharElement* pCharElement = new CharElement();
// 		if (!pCharElement->initialize(m_strFontId, charId, fontSize, NULL))
// 		{
// 			SAFE_DELETE(pCharElement);
// 		}
// 		else
// 		{
// 			m_vRootElements.push_back(pCharElement);
// 		}
// 	}
// 
// 	for (TV_CHAR_INFO::const_iterator it = m_vCharInfo.begin(); it != m_vCharInfo.end(); ++it)
// 	{
// 		const CHAR_INFO* pCharInfo = (*it);
// 
// 		if (pCharInfo->nID == '\n')
// 		{
// 			fBasePosY += m_pFont->GetLineHeight();
// 			fBasePosX = pos.x;
// 			continue;
// 		}
// 
// 		QUAD_VERT_POS_UV quad;
// 
// 		float fCharPosX = fBasePosX + pCharInfo->offsetx;
// 		float fCharPosY = fBasePosY + pCharInfo->offsety;
// 
// 		quad.verts[0].x = fCharPosX;
// 		quad.verts[0].y = fCharPosY + pCharInfo->height;
// 		quad.verts[0].z = 0.0f;
// 		quad.verts[0].u = pCharInfo->u;
// 		quad.verts[0].v = pCharInfo->v;
// 
// 		quad.verts[1].x = fCharPosX;
// 		quad.verts[1].y = fCharPosY;
// 		quad.verts[1].z = 0.0f;
// 		quad.verts[1].u = pCharInfo->u;
// 		quad.verts[1].v = pCharInfo->v + pCharInfo->dv;
// 
// 		quad.verts[2].x = fCharPosX + pCharInfo->width;
// 		quad.verts[2].y = fCharPosY + pCharInfo->height;
// 		quad.verts[2].z = 0.0f;
// 		quad.verts[2].u = pCharInfo->u + pCharInfo->du;
// 		quad.verts[2].v = pCharInfo->v;
// 
// 		quad.verts[3].x = fCharPosX + pCharInfo->width;
// 		quad.verts[3].y = fCharPosY;
// 		quad.verts[3].z = 0.0f;
// 		quad.verts[3].u = pCharInfo->u + pCharInfo->du;
// 		quad.verts[3].v = pCharInfo->v + pCharInfo->dv;
// 
// 		if (IRendererUI::GetInstance().ClipRect(quad, clipRectPos, clipRectSize))
// 		{
// 			IRendererUI::GetInstance().SetTexture(pCharInfo->pTexture);
// 			IRendererUI::GetInstance().DrawRect(quad);
// 		}
// 
// 		fBasePosX += pCharInfo->advance;
// 	}

	return false;
}

}
