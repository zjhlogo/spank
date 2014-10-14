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

class Texture;
class Shader;
class RenderBuffer;
class MemRenderBuffer;
class VMemRenderBuffer;
class VertexAttributes;

class IRenderer : public IMgr
{
public:
	IRenderer();
	virtual ~IRenderer();

	virtual void reload(bool freeOld) = 0;

	virtual Texture* createTexture(const std::string& filePath) = 0;
	virtual bool releaseTexture(Texture* pTexture) = 0;

	virtual Shader* createShader(const std::string& filePath) = 0;
	virtual bool releaseShader(Shader* pShader) = 0;

	virtual VMemRenderBuffer* createVMemRenderBuffer(const VertexAttributes* pVertAttrs) = 0;
	virtual bool releaseVMemRenderBuffer(VMemRenderBuffer* pBuffer) = 0;

	virtual VertexAttributes* createVertexAttributes(const std::string& filePath) = 0;
	virtual bool releaseVertexAttributes(VertexAttributes* pVertAttrs) = 0;

};
