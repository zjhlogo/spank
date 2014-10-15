/*!
 * \file LogUtil.h
 * \date 10-11-2014 16:13:32
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <mutex>

namespace spank
{

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

}

#define LOGI(...) (spank::LogUtil::debug(__FILE__, __LINE__, spank::LogUtil::LPRIO_INFO, __VA_ARGS__))
#define LOGD(...) (spank::LogUtil::debug(__FILE__, __LINE__, spank::LogUtil::LPRIO_DEBUG, __VA_ARGS__))
#define LOGE(...) (spank::LogUtil::debug(__FILE__, __LINE__, spank::LogUtil::LPRIO_ERROR, __VA_ARGS__))
