/*!
 * \file TimeUtilWin32.cpp
 * \date 10-10-2014 14:24:08
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <utils/TimeUtil.h>
#include <windows.h>

namespace spank
{

int TimeUtil::getNowTime()
{
	return timeGetTime();
}

}
