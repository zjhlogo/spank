/*!
 * \file Label.h
 * \date 10-18-2014 15:33:50
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

class IRenderer;
class Shader;
class Texture;
class IFont;
class VMemVertexBuffer;
class VMemIndexBuffer;

class Label
{
public:
	typedef std::vector<uint16> TV_UINT16;

	typedef struct INDEX_BUFFER_INFO_tag
	{
		Texture* pTexture{ nullptr };
		TV_UINT16 vIndis;
		VMemIndexBuffer* pIndexBuffer{ nullptr };
	} INDEX_BUFFER_INFO;

	typedef std::map<Texture*, INDEX_BUFFER_INFO*> TM_INDEX_BUFFER_INFO;

public:
	Label(IRenderer* pRenderer, IFont* pFont);
	virtual ~Label();

	void setText(const std::string& text);
	inline const std::string& getText() const { return m_text; };

	inline void setPos(const glm::vec2& pos) { m_pos = pos; };
	inline const glm::vec2& getPos() const { return m_pos; };

	glm::vec2 calcTextSize(const std::string& text);

	void render();

private:
	void clearBuffer();
	bool createBuffer(const std::string& text);

	INDEX_BUFFER_INFO* findIndexBuffer(Texture* pTexture);

private:
	IRenderer* m_pRenderer{ nullptr };
	Shader* m_pShader{ nullptr };
	Texture* m_pTexture{ nullptr };
	IFont* m_pFont{ nullptr };

	std::string m_text;
	glm::vec2 m_pos;

	VMemVertexBuffer* m_vertexBuffer{ nullptr };
	TM_INDEX_BUFFER_INFO m_indexBufferInfoMap;

};

}
