/*!
 * \file Framework.h
 * \date 10-10-2014 11:44:30
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "base/IMgr.h"
#include "render/IRenderer.h"
#include "render/Texture.h"
#include "render/Shader.h"
#include "render/RenderBuffer.h"
#include "render/VertexAttributes.h"

class Framework : public IMgr
{
public:
	virtual bool initialize() override;
	virtual void terminate() override;

	inline IRenderer* getRenderer() const { return m_pRenderer; };

protected:
	Framework();
	virtual ~Framework();

private:
	IRenderer* m_pRenderer{ nullptr };

};
