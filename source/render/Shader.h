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
#include "Texture.h"

class Shader : public RenderObject
{
public:
	Shader();
	virtual ~Shader();

	bool loadFromFile(const std::string& vertexShaderFile, const std::string& fragShaderFile);

	void useShader();
	bool setMatrix(const char* pszName, const float* pMatrix);
	bool setTexture(const char* pszName, Texture* pTexture);

private:
	GLuint m_vertexShader{ 0 };
	GLuint m_fragShader{ 0 };
	GLuint m_program{ 0 };

};
