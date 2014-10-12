/*!
 * \file LogUtilAndroid.cpp
 * \date 10-11-2014 17:05:41
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "LogUtilAndroid.h"
#include <stdarg.h>
#include <android/log.h>

void LogUtil::debug(const char* location, int line, PRIORITY prio, const char* format, ...)
{
	static const int PRIORITY_MAP[NUM_PRIO] =
	{
		ANDROID_LOG_INFO,
		ANDROID_LOG_DEBUG,
		ANDROID_LOG_ERROR,
	};

	m_mutex.lock();
	va_list marker;
	va_start(marker, format);

	__android_log_vprint(PRIORITY_MAP[prio], "tag", format, marker);
	va_end(marker);

	m_mutex.unlock();
}
