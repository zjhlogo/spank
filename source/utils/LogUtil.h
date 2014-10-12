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
	enum PRIORITY
	{
		INFO = 0,
		DEBUG,
		ERROR,
		NUM_PRIO,
	};

public:
	static void debug(const char* location, int line, PRIORITY prio, const char* format, ...);

private:
	static std::mutex m_mutex;

};

#define LOGI(...) (LogUtil::debug(__FILE__, __LINE__, LogUtil::INFO, __VA_ARGS__))
#define LOGD(...) (LogUtil::debug(__FILE__, __LINE__, LogUtil::DEBUG, __VA_ARGS__))
#define LOGE(...) (LogUtil::debug(__FILE__, __LINE__, LogUtil::ERROR, __VA_ARGS__))
