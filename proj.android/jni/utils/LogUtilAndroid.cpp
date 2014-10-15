/*!
 * \file LogUtilAndroid.cpp
 * \date 10-11-2014 17:05:41
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <utils/LogUtil.h>
#include <stdarg.h>
#include <android/log.h>

namespace spank
{

void LogUtil::debug(const char* location, int line, LOG_PRIORITY prio, const char* format, ...)
{
	static std::mutex s_mutex;

	static const int PRIORITY_MAP[LPRIO_NUM_PRIO] =
	{
		ANDROID_LOG_INFO,
		ANDROID_LOG_DEBUG,
		ANDROID_LOG_ERROR,
	};

	s_mutex.lock();
	va_list marker;
	va_start(marker, format);

	__android_log_vprint(PRIORITY_MAP[prio], "tag", format, marker);
	va_end(marker);

	s_mutex.unlock();
}

}
