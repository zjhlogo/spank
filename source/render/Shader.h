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

class IRenderer;
class Texture;
class RenderBuffer;
class MemRenderBuffer;
class VMemRenderBuffer;
class VertexAttributes;

class Shader : public RenderObject
{
public:
	Shader();
	virtual ~Shader();

	bool loadFromFile(const std::string& filePath, IRenderer* pRenderer);
	bool reload(bool freeOld);

	void useProgram();
	bool setMatrix(const char* pszName, const float* pMatrix);
	bool setTexture(const char* pszName, Texture* pTexture, int index = 0);
	void drawArrays(VMemRenderBuffer* pRenderBuffer, int start, int numVerts);

	inline const VertexAttributes* getVertexAttributes() const { return m_pVertAttributes; };
	inline GLuint getProgramId() const { return m_programId; };

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

};
