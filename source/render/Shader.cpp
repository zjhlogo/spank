/*!
 * \file Shader.cpp
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#include "Shader.h"
#include "../utils/FileUtil.h"

Shader::Shader()
{

}

Shader::~Shader()
{
	glDeleteProgram(m_program);
	m_program = 0;

	glDeleteShader(m_vertexShader);
	m_vertexShader = 0;

	glDeleteShader(m_fragShader);
	m_fragShader = 0;
}

bool Shader::loadFromFile(const std::string& vertexShaderFile, const std::string& fragShaderFile)
{
	BUFFER_DATA fragShaderData;
	if (!FileUtil::readFile(fragShaderData, fragShaderFile)) return false;
	const char* pszFragShader = static_cast<const char*>(fragShaderData.data());

	// Create the fragment shader object
	m_fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Load the source code into it
	glShaderSource(m_fragShader, 1, &pszFragShader, NULL);

	// Compile the source code
	glCompileShader(m_fragShader);

	// TODO: Check if compilation succeeded

	BUFFER_DATA vertexShaderData;
	if (!FileUtil::readFile(vertexShaderData, vertexShaderFile)) return false;
	const char* pszVertexShader = static_cast<const char*>(vertexShaderData.data());

	// Create the fragment shader object
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Load the source code into it
	glShaderSource(m_vertexShader, 1, &pszVertexShader, NULL);

	// Compile the source code
	glCompileShader(m_vertexShader);

	// TODO: Check if compilation succeeded

	// Create the shader program
	m_program = glCreateProgram();

	// Attach the fragment and vertex shaders to it
	glAttachShader(m_program, m_fragShader);
	glAttachShader(m_program, m_vertexShader);

	// TODO: 
	// Bind the custom vertex attribute "myVertex" to location VERTEX_ARRAY
	glBindAttribLocation(m_program, 0, "myVertex");
	// Bind the custom vertex attribute "myUV" to location TEXCOORD_ARRAY
	glBindAttribLocation(m_program, 1, "myUV");

	// Link the program
	glLinkProgram(m_program);

	return true;
}

void Shader::useShader()
{
	glUseProgram(m_program);
}

bool Shader::setMatrix(const char* pszName, const float* pMatrix)
{
	// First gets the location of that variable in the shader using its name
	int i32Location = glGetUniformLocation(m_program, pszName);

	// Then passes the matrix to that variable
	glUniformMatrix4fv(i32Location, 1, GL_FALSE, pMatrix);

	return true;
}

bool Shader::setTexture(const char* pszName, Texture* pTexture)
{
	glUniform1i(glGetUniformLocation(m_program, pszName), 0);
	return true;
}
