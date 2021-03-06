/*!
 * \file IMgr.h
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#pragma once

#include "PlatformDefine.h"

namespace spank
{

class IMgr
{
public:
	IMgr();
	virtual ~IMgr();

	virtual bool initialize() = 0;
	virtual void terminate() = 0;

};

}
