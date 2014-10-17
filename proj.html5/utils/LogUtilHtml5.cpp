/*!
 * \file LogUtilHtml5.cpp
 * \date 10-11-2014 17:05:41
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <utils/LogUtil.h>
#include <iostream>

namespace spank
{

void LogUtil::debug(const char* location, int line, LOG_PRIORITY prio, const char* format, ...)
{
	static std::mutex s_mutex;

	static const char* PRIORITY_MAP[LPRIO_NUM_PRIO] =
	{
		"Info",
		"Debug",
		"Error",
	};

	static const int MAX_BUFFER_SIZE = 1024 * 4;
	static char g_szBuffer[MAX_BUFFER_SIZE];

	s_mutex.lock();
	va_list marker;
	va_start(marker, format);

	vsprintf(g_szBuffer, format, marker);
	va_end(marker);

	std::cout << location << "(" << line << "): " << PRIORITY_MAP[prio] << ": " << g_szBuffer << std::endl;
	s_mutex.unlock();
}

}
