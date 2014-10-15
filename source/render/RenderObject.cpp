/*!
 * \file RenderObject.cpp
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#include "RenderObject.h"
#include "../utils/LogUtil.h"

namespace spank
{

RenderObject::RenderObject()
{

}

RenderObject::~RenderObject()
{

}

void RenderObject::release()
{
	if (decRef() <= 0)
	{
		if (m_ref < 0) LOGE("Render object release more then create %d", m_ref);

		preDelete();
		delete this;
	}
}

void RenderObject::preDelete()
{
	// TODO: 
}

}
