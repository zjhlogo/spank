/*!
 * \file TimeUtilWin32.cpp
 * \date 10-10-2014 14:24:08
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "TimeUtilWin32.h"
#include <windows.h>

int TimeUtil::getNowTime()
{
	return timeGetTime();
}
