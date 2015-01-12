/*!
 * \file StringBuilder.cpp
 * \date 10-14-2013 16:52:41
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "StringBuilder.h"
#include "StringUtil.h"
#include <stdarg.h>

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


StringBuilder::StringBuilder(const char* pszFormat)
{
	parseFormat(pszFormat);
}

StringBuilder::~StringBuilder()
{

}

StringBuilder& StringBuilder::add(int nValue, const char* pszFormat /*= NULL*/)
{
	std::string strValue;
	if (!pszFormat) strValue = StringUtil::int2str(nValue);
	else strformat(strValue, pszFormat, nValue);

	m_vReplacement.push_back(strValue);
	return (*this);
}

StringBuilder& StringBuilder::add(uint nValue, const char* pszFormat /*= NULL*/)
{
	std::string strValue;
	if (!pszFormat) strValue = StringUtil::int2str(nValue);
	else strformat(strValue, pszFormat, nValue);

	m_vReplacement.push_back(strValue);
	return (*this);
}

StringBuilder& StringBuilder::add(int64 nValue, const char* pszFormat /*= NULL*/)
{
	std::string strValue;
	if (!pszFormat) strValue = StringUtil::int642str(nValue);
	else strformat(strValue, pszFormat, nValue);

	m_vReplacement.push_back(strValue);
	return (*this);
}

StringBuilder& StringBuilder::add(uint64 nValue, const char* pszFormat /*= NULL*/)
{
	std::string strValue;
	if (!pszFormat) strValue = StringUtil::int642str(nValue);
	else strformat(strValue, pszFormat, nValue);

	m_vReplacement.push_back(strValue);
	return (*this);
}

StringBuilder& StringBuilder::add(float fValue, const char* pszFormat /*= NULL*/)
{
	std::string strValue;
	if (!pszFormat) strValue = StringUtil::float2str(fValue);
	else strformat(strValue, pszFormat, fValue);

	m_vReplacement.push_back(strValue);
	return (*this);
}

StringBuilder& StringBuilder::add(double dValue, const char* pszFormat /*= NULL*/)
{
	std::string strValue;
	if (!pszFormat) strValue = StringUtil::double2str(dValue);
	else strformat(strValue, pszFormat, dValue);

	m_vReplacement.push_back(strValue);
	return (*this);
}

StringBuilder& StringBuilder::add(const std::string& strValue)
{
	m_vReplacement.push_back(strValue);
	return (*this);
}

std::string StringBuilder::build()
{
	std::string strFinal;

	for (TV_REPLACE_INFO::iterator it = m_vReplaceInfo.begin(); it != m_vReplaceInfo.end(); ++it)
	{
		REPLACE_INFO& replaceInfo = (*it);
		strFinal += replaceInfo.strString;
		if (replaceInfo.index >= 0 && replaceInfo.index < (int)m_vReplacement.size())
		{
			strFinal += m_vReplacement[replaceInfo.index];
		}
	}

	return strFinal;
}

StringBuilder StringBuilder::format(const char* pszFormat)
{
	return StringBuilder(pszFormat);
}

void StringBuilder::parseFormat(const char* pszFormat)
{
	m_vReplaceInfo.clear();

	int length = 0;
	while (pszFormat[length] != '\0') ++length;

	REPLACE_INFO replaceInfo;
	replaceInfo.strString.clear();
	replaceInfo.index = -1;

	for (int i = 0; i < length; ++i)
	{
		if (pszFormat[i] == '#')
		{
			if (i < (length - 1))
			{
				if (pszFormat[i + 1] == '#')
				{
					replaceInfo.strString.push_back('#');
				}
				else if (pszFormat[i + 1] >= '0' && pszFormat[i + 1] <= '9')
				{
					replaceInfo.index = pszFormat[i + 1] - '0';
					m_vReplaceInfo.push_back(replaceInfo);

					replaceInfo.strString.clear();
					replaceInfo.index = -1;
				}
				else
				{
					replaceInfo.strString.push_back('#');
					replaceInfo.strString.push_back(pszFormat[i + 1]);
				}

				++i;
			}
			else
			{
				replaceInfo.strString.push_back(pszFormat[i]);
			}
		}
		else
		{
			replaceInfo.strString.push_back(pszFormat[i]);
		}
	}

	if (!replaceInfo.strString.empty() || replaceInfo.index != -1)
	{
		m_vReplaceInfo.push_back(replaceInfo);
	}
}

bool StringBuilder::strformat(std::string& strOut, const char* strFormat, ...)
{
	static const int MAX_BUFF_COUNT = 1024 * 10;
	static char s_strBuff[MAX_BUFF_COUNT];

	va_list marker;
	va_start(marker, strFormat);

	int nLength = _vsntprintf(s_strBuff, MAX_BUFF_COUNT, strFormat, marker);
	strOut = s_strBuff;
	va_end(marker);

	return true;
}

}
