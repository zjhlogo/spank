/*!
 * \file StringBuilder.cpp
 * \date 10-14-2013 16:52:41
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "StringBuilder.h"
#include "StringUtil.h"

namespace spank
{

StringBuilder::StringBuilder(const char* pszFormat)
{
	int length = strlen(pszFormat);

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

StringBuilder::~StringBuilder()
{

}

tstring StringBuilder::build()
{
	tstring strFinal;

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

}
