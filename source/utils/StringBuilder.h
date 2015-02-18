/*!
 * \file StringBuilder.h
 * \date 10-17-2014 14:12:48
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include "../base/PlatformDefine.h"
#include <sstream>
#include <iomanip>

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

	template <typename T> StringBuilder& add(T value, int width = 0, int precision = 0)
	{
		std::stringstream ss;
		if (width > 0) ss << std::setfill('0') << std::setw(width);
		if (precision > 0) ss << std::setprecision(precision);
		ss << value;

		std::string strValue;
		ss >> strValue;

		m_vReplacement.push_back(strValue);
		return (*this);
	}

	std::string build();

	static StringBuilder format(const char* pszFormat);

private:
	TV_REPLACE_INFO m_vReplaceInfo;
	TV_STRING m_vReplacement;

};

}
