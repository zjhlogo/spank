/*!
 * \file TimeUtilAndroid.cpp
 * \date 10-11-2014 14:33:27
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <utils/TimeUtil.h>
#include <time.h>

int TimeUtil::getNowTime()
{
	timespec res;
	clock_gettime(CLOCK_REALTIME, &res);
	return res.tv_sec * 1000 + res.tv_nsec / 1e6;
}
