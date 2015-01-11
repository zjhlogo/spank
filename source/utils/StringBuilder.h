/*!
 * \file StringBuilder.h
 * \date 10-17-2014 14:12:48
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "../base/PlatformDefine.h"

namespace spank
{

class StringBuilder
{
public:
	typedef struct REPLACE_INFO_tag
	{
		std::string strString;
		int index;
	} REPLACE_INFO;

	typedef std::vector<REPLACE_INFO> TV_REPLACE_INFO;
	typedef std::vector<std::string> TV_STRING;

public:
	StringBuilder(const char* pszFormat);
	~StringBuilder();

	StringBuilder& add(int nValue, const char* pszFormat = NULL);
	StringBuilder& add(uint nValue, const char* pszFormat = NULL);

	StringBuilder& add(int64 nValue, const char* pszFormat = NULL);
	StringBuilder& add(uint64 nValue, const char* pszFormat = NULL);

	StringBuilder& add(float fValue, const char* pszFormat = NULL);
	StringBuilder& add(double dValue, const char* pszFormat = NULL);
	StringBuilder& add(const std::string& strValue);

	std::string build();

	static StringBuilder format(const char* pszFormat);

private:
	void parseFormat(const char* pszFormat);
	static bool strformat(std::string& strOut, const char* strFormat, ...);

private:
	TV_REPLACE_INFO m_vReplaceInfo;
	TV_STRING m_vReplacement;

};

}
