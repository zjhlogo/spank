/*!
 * \file LogUtil.h
 * \date 10-11-2014 16:13:32
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <mutex>

class LogUtil
{
public:
	enum LOG_PRIORITY
	{
		LPRIO_INFO = 0,
		LPRIO_DEBUG,
		LPRIO_ERROR,
		LPRIO_NUM_PRIO,
	};

public:
	static void debug(const char* location, int line, LOG_PRIORITY prio, const char* format, ...);

};

#define LOGI(...) (LogUtil::debug(__FILE__, __LINE__, LogUtil::LPRIO_INFO, __VA_ARGS__))
#define LOGD(...) (LogUtil::debug(__FILE__, __LINE__, LogUtil::LPRIO_DEBUG, __VA_ARGS__))
#define LOGE(...) (LogUtil::debug(__FILE__, __LINE__, LogUtil::LPRIO_ERROR, __VA_ARGS__))
