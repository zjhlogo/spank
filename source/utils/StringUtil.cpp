/*!
 * \file StringUtil.cpp
 * \date 10-14-2014 13:56:16
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "StringUtil.h"
#include <stdlib.h>

#ifdef WIN32
	#define _tstoi      atoi
	#define _tstoi64    _atoi64
	#define _tstof      atof
	#define _stscanf      sscanf
	#define _sntprintf    _snprintf
	#define _vsntprintf   _vsnprintf
	#define _tcsncpy    strncpy
#else
	#define _tstoi      atoi
	#define _tstoi64    atoll
	#define _tstof      atof
	#define _stscanf      sscanf
	#define _sntprintf    snprintf
	#define _vsntprintf   vsnprintf
	#define _tcsncpy    strncpy
#endif

namespace spank
{

int StringUtil::str2int(const char* pstrIn)
{
	return _tstoi(pstrIn);
}

std::string StringUtil::int2str(int value)
{
	static char s_strBuffer[1024];

	std::string strValue;
	_sntprintf(s_strBuffer, 1024, "%d", value);
	strValue.append(s_strBuffer);
	return strValue;
}

int64 StringUtil::str2int64(const char* pstrIn)
{
	return _tstoi64(pstrIn);
}

std::string StringUtil::int642str(int64 value)
{
	static char s_strBuffer[1024];

	std::string strValue;
	_sntprintf(s_strBuffer, 1024, "%lld", value);
	strValue.append(s_strBuffer);
	return strValue;
}

float StringUtil::str2float(const char* pstrIn)
{
	return (float)_tstof(pstrIn);
}

std::string StringUtil::float2str(float value)
{
	static char s_strBuffer[1024];

	std::string strValue;
	_sntprintf(s_strBuffer, 1024, "%f", value);
	strValue.append(s_strBuffer);
	return strValue;
}

std::string StringUtil::getFileDir(const std::string& strIn)
{
	std::string strDir;
	size_t nPosEnd = strIn.find_last_of("/\\");

	if (nPosEnd == std::string::npos) return strDir;

	return strIn.substr(0, nPosEnd);
}

std::string StringUtil::getFileExt(const std::string& strIn)
{
	std::string strExt;

	size_t nPos = strIn.rfind('.');
	if (nPos != std::string::npos)
	{
		strExt = strIn.substr(nPos + 1, std::string::npos);
	}

	return strExt;
}

}
