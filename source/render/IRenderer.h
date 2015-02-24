/*!
 * \file IRenderer.h
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#pragma once

#include "../base/IMgr.h"
#include <glm/glm.hpp>

namespace spank
{

class Texture;
class Shader;
class RenderBuffer;
class MemVertexBuffer;
class VMemVertexBuffer;
class MemIndexBuffer;
class VMemIndexBuffer;
class VertexAttributes;

class IRenderer : public IMgr
{
	friend class Texture;
	friend class Shader;
	friend class RenderBuffer;
	friend class VertexAttributes;

public:
	IRenderer();
	virtual ~IRenderer();

	virtual void reload(bool freeOld) = 0;
	virtual void resize(int width, int height) = 0;

	virtual const glm::vec2& getSurfaceSize() const = 0;
	virtual const glm::mat4& getOrthoMatrix() const = 0;
	virtual const glm::mat4& getPerspectiveMatrix() const = 0;

	virtual Texture* createTexture(const tstring& filePath) = 0;
	virtual Shader* createShader(const tstring& filePath) = 0;

	virtual MemVertexBuffer* createMemVertexBuffer(const VertexAttributes* pVertAttrs) = 0;
	virtual VMemVertexBuffer* createVMemVertexBuffer(const VertexAttributes* pVertAttrs) = 0;

	virtual MemIndexBuffer* createMemIndexBuffer() = 0;
	virtual VMemIndexBuffer* createVMemIndexBuffer() = 0;

	virtual VertexAttributes* createVertexAttributes(const tstring& filePath) = 0;

	inline void setShaderBaseDir(const tstring& shaderBaseDir) { m_shaderBaseDir = shaderBaseDir; };
	inline const tstring& getShaderBaseDir() const { return m_shaderBaseDir; };

protected:
	virtual bool removeTexture(Texture* pTexture) = 0;
	virtual bool removeShader(Shader* pShader) = 0;
	virtual bool removeRenderBuffer(RenderBuffer* pBuffer) = 0;
	virtual bool removeVertexAttributes(VertexAttributes* pVertAttrs) = 0;

private:
	tstring m_shaderBaseDir;

};

}
