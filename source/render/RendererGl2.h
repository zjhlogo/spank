/*!
 * \file RendererGl2.h
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#pragma once

#include "IRenderer.h"
#include <map>
#include <set>

class RendererGl2 : public IRenderer
{
public:
	typedef std::map<std::string, Texture*> TM_TEXTURE;
	typedef std::map<std::string, Shader*> TM_SHADER;
	typedef std::set<RenderBuffer*> TS_RENDER_BUFFER;
	typedef std::map<std::string, VertexAttributes*> TM_VERTEX_ATTRIBUTE;

public:
	RendererGl2();
	virtual ~RendererGl2();

	virtual bool initialize() override;
	virtual void terminate() override;
	virtual void reload(bool freeOld) override;

	virtual Texture* createTexture(const std::string& filePath) override;
	virtual Shader* createShader(const std::string& filePath) override;
	virtual MemRenderBuffer* createMemRenderBuffer(const VertexAttributes* pVertAttrs) override;
	virtual VMemRenderBuffer* createVMemRenderBuffer(const VertexAttributes* pVertAttrs) override;
	virtual VertexAttributes* createVertexAttributes(const std::string& filePath) override;

protected:
	virtual bool removeTexture(Texture* pTexture) override;
	virtual bool removeShader(Shader* pShader) override;
	virtual bool removeRenderBuffer(RenderBuffer* pBuffer) override;
	virtual bool removeVertexAttributes(VertexAttributes* pVertAttrs) override;

private:
	TM_TEXTURE m_textureMap;
	TM_SHADER m_shaderMap;
	TS_RENDER_BUFFER m_renderBufferSet;
	TM_VERTEX_ATTRIBUTE m_vertexAttributeMap;

};