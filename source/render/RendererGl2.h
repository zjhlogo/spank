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

namespace spank
{

class RendererGl2 : public IRenderer
{
public:
	typedef std::map<tstring, Texture*> TM_TEXTURE;
	typedef std::map<tstring, Shader*> TM_SHADER;
	typedef std::set<RenderBuffer*> TS_RENDER_BUFFER;
	typedef std::map<tstring, VertexAttributes*> TM_VERTEX_ATTRIBUTE;

public:
	RendererGl2();
	virtual ~RendererGl2();

	virtual bool initialize() override;
	virtual void terminate() override;

	virtual void reload(bool freeOld) override;
	virtual void resize(int width, int height) override;
	virtual const glm::vec2& getSurfaceSize() const override;
	virtual const glm::mat4& getOrthoMatrix() const override;
	virtual const glm::mat4& getPerspectiveMatrix() const override;

	virtual Texture* createTexture(const tstring& filePath) override;
	virtual Shader* createShader(const tstring& filePath) override;

	virtual MemVertexBuffer* createMemVertexBuffer(const VertexAttributes* pVertAttrs) override;
	virtual VMemVertexBuffer* createVMemVertexBuffer(const VertexAttributes* pVertAttrs) override;

	virtual MemIndexBuffer* createMemIndexBuffer() override;
	virtual VMemIndexBuffer* createVMemIndexBuffer() override;

	virtual VertexAttributes* createVertexAttributes(const tstring& filePath) override;

protected:
	virtual bool removeTexture(Texture* pTexture) override;
	virtual bool removeShader(Shader* pShader) override;
	virtual bool removeRenderBuffer(RenderBuffer* pBuffer) override;
	virtual bool removeVertexAttributes(VertexAttributes* pVertAttrs) override;

private:
	glm::vec2 m_surfaceSize;
	glm::mat4 m_matOrtho;
	glm::mat4 m_matPerspective;

	TM_TEXTURE m_textureMap;
	TM_SHADER m_shaderMap;
	TS_RENDER_BUFFER m_renderBufferSet;

	TM_VERTEX_ATTRIBUTE m_vertexAttributeMap;

};

}
