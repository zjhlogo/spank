/*!
 * \file RenderObject.h
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#pragma once

#include "../base/PlatformDefine.h"
#include <GLES2/gl2.h>

class RenderObject
{
public:
	RenderObject();
	virtual ~RenderObject();

	inline void setId(const std::string& strId) { m_strId = strId; };
	inline const std::string getId() const { return m_strId; };

private:
	std::string m_strId;

};

#define GL_ERROR_CHECK() {GLenum glErrCode = glGetError(); if (glErrCode != GL_NO_ERROR) LOGE("gl Error Code: 0x%x");}
