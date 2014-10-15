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

namespace spank
{

class Texture;
class Shader;
class RenderBuffer;
class MemRenderBuffer;
class VMemRenderBuffer;
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

	virtual Texture* createTexture(const std::string& filePath) = 0;
	virtual Shader* createShader(const std::string& filePath) = 0;
	virtual MemRenderBuffer* createMemRenderBuffer(const VertexAttributes* pVertAttrs) = 0;
	virtual VMemRenderBuffer* createVMemRenderBuffer(const VertexAttributes* pVertAttrs) = 0;
	virtual VertexAttributes* createVertexAttributes(const std::string& filePath) = 0;

protected:
	virtual bool removeTexture(Texture* pTexture) = 0;
	virtual bool removeShader(Shader* pShader) = 0;
	virtual bool removeRenderBuffer(RenderBuffer* pBuffer) = 0;
	virtual bool removeVertexAttributes(VertexAttributes* pVertAttrs) = 0;

};

}
