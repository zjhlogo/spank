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
	typedef std::set<VMemRenderBuffer*> TS_VMEM_RENDER_BUFFER;
	typedef std::map<std::string, VertexAttributes*> TM_VERTEX_ATTRIBUTE;

public:
	RendererGl2();
	virtual ~RendererGl2();

	virtual bool initialize() override;
	virtual void terminate() override;
	virtual void reload(bool freeOld) override;

	virtual Texture* createTexture(const std::string& filePath) override;
	virtual bool releaseTexture(Texture* pTexture) override;

	virtual Shader* createShader(const std::string& filePath) override;
	virtual bool releaseShader(Shader* pShader) override;

	virtual VMemRenderBuffer* createVMemRenderBuffer(const VertexAttributes* pVertAttrs) override;
	virtual bool releaseVMemRenderBuffer(VMemRenderBuffer* pBuffer) override;

	virtual VertexAttributes* createVertexAttributes(const std::string& filePath) override;
	virtual bool releaseVertexAttributes(VertexAttributes* pVertAttrs) override;

private:
	TM_TEXTURE m_textureMap;
	TM_SHADER m_shaderMap;
	TS_VMEM_RENDER_BUFFER m_vmemRenderBufferSet;
	TM_VERTEX_ATTRIBUTE m_vertexAttributeMap;

};