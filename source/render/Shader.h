/*!
 * \file Shader.h
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#pragma once

#include "RenderObject.h"
#include <map>

namespace spank
{

class IRenderer;
class Texture;
class RenderBuffer;
class MemVertexBuffer;
class VMemVertexBuffer;
class MemIndexBuffer;
class VMemIndexBuffer;
class VertexAttributes;

class Shader : public RenderObject
{
public:
	friend class RendererGl2;

	typedef struct TEXTURE_INFO_tag
	{
		int slotId{ 0 };
		tstring name;
	} TEXTURE_INFO;

	typedef std::map<int, TEXTURE_INFO> TM_TEXTURE_INFO;

public:
	bool loadFromFile(const tstring& filePath);
	bool reload(bool freeOld);

	void useProgram();
	bool setUniform(const char* pszName, float value);
	bool setUniform(const char* pszName, const glm::vec2& v);
	bool setUniform(const char* pszName, const glm::vec3& v);
	bool setUniform(const char* pszName, const glm::mat4& mat4);
	bool setTexture(Texture* pTexture, int index);

	void drawBuffer(MemVertexBuffer* pVertexBuffer, int start, int numVerts);
	void drawBuffer(VMemVertexBuffer* pVertexBuffer, int start, int numVerts);
	void drawBuffer(MemVertexBuffer* pVertexBuffer, MemIndexBuffer* pIndexBuffer);
	void drawBuffer(VMemVertexBuffer* pVertexBuffer, VMemIndexBuffer* pIndexBuffer);

	inline const VertexAttributes* getVertexAttributes() const { return m_pVertAttributes; };
	inline GLuint getProgramId() const { return m_programId; };

protected:
	Shader(IRenderer* pRenderer);
	virtual ~Shader();

	virtual void preDelete() override;

private:
	void destroyProgram();
	GLuint compileShader(GLuint shaderType, const tstring& shaderData);
	bool getShaderErrorLog(GLuint shaderId);
	bool getProgramErrorLog(GLuint programId);

private:
	GLuint m_programId{ 0 };

	IRenderer* m_pRenderer{ nullptr };
	VertexAttributes* m_pVertAttributes{ nullptr };

	tstring m_vertexShaderData;
	tstring m_fragShaderData;
	tstring m_errorLog;

	TM_TEXTURE_INFO m_textureInfoMap;

};

}
