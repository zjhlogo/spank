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
		std::string name;
	} TEXTURE_INFO;

	typedef std::map<int, TEXTURE_INFO> TM_TEXTURE_INFO;

public:
	bool loadFromFile(const std::string& filePath);
	bool reload(bool freeOld);

	void useProgram();
	bool setMatrix(const char* pszName, const glm::mat4& mat4);
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
	GLuint compileShader(GLuint shaderType, const std::string& shaderData);
	bool getShaderErrorLog(GLuint shaderId);
	bool getProgramErrorLog(GLuint programId);

private:
	GLuint m_programId{ 0 };

	IRenderer* m_pRenderer{ nullptr };
	VertexAttributes* m_pVertAttributes{ nullptr };

	std::string m_vertexShaderData;
	std::string m_fragShaderData;
	std::string m_errorLog;

	TM_TEXTURE_INFO m_textureInfoMap;

};

}
