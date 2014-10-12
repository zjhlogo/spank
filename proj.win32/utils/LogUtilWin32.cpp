/*!
 * \file LogUtilWin32.cpp
 * \date 10-11-2014 16:17:24
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <utils/LogUtil.h>
#include <sstream>
#include <stdarg.h>
#include <windows.h>

void LogUtil::debug(const char* location, int line, PRIORITY prio, const char* format, ...)
{
	static std::mutex s_mutex;

	static const char* PRIORITY_MAP[NUM_PRIO] =
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

	vsprintf_s(g_szBuffer, MAX_BUFFER_SIZE, format, marker);
	va_end(marker);

	std::ostringstream strStream;
	strStream << location << "(" << line << "): " << PRIORITY_MAP[prio] << ": " << g_szBuffer << std::endl;
	OutputDebugString(strStream.str().c_str());
	s_mutex.unlock();
}
