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
#include "input/TouchDelegateMgr.h"
#include "font/FontMgr.h"
#include "model/ModelMgr.h"

namespace spank
{

class Framework : public IMgr
{
public:
	virtual bool initialize() override;
	virtual void terminate() override;

	inline IRenderer* getRenderer() const { return m_pRenderer; };
	inline ModelMgr* getModelMgr() const { return m_pModelMgr; };
	inline TouchDelegateMgr* getTouchDelegateMgr() const { return m_pTouchDelegateMgr; };
	inline FontMgr* getFontMgr() const { return m_pFontMgr; };

protected:
	Framework();
	virtual ~Framework();

private:
	IRenderer* m_pRenderer{ nullptr };
	ModelMgr* m_pModelMgr{ nullptr };
	TouchDelegateMgr* m_pTouchDelegateMgr{ nullptr };
	FontMgr* m_pFontMgr{ nullptr };

};

}
