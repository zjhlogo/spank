/*!
 * \file StringUtil.cpp
 * \date 10-14-2014 13:56:16
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "StringUtil.h"

namespace spank
{

tstring StringUtil::getFileDir(const tstring& strIn)
{
	tstring strDir;
	size_t nPosEnd = strIn.find_last_of("/\\");

	if (nPosEnd == tstring::npos) return strDir;

	return strIn.substr(0, nPosEnd);
}

tstring StringUtil::getFileExt(const tstring& strIn)
{
	tstring strExt;

	size_t nPos = strIn.rfind('.');
	if (nPos != tstring::npos)
	{
		strExt = strIn.substr(nPos + 1, tstring::npos);
	}

	return strExt;
}
int StringUtil::splitString(TV_STRING& arrOut, const tstring& strIn, const tstring& strSplit)
{
	int totalSplit = 0;
	size_t startIndex = 0;
	size_t endIndex = 0;

	endIndex = strIn.find(strSplit, startIndex);
	while (endIndex != tstring::npos)
	{
		arrOut.push_back(strIn.substr(startIndex, endIndex - startIndex));
		++totalSplit;

		startIndex = endIndex;
		startIndex += strSplit.length();
		endIndex = strIn.find(strSplit, startIndex);
	}

	if (totalSplit <= 0)
	{
		arrOut.push_back(strIn);
		++totalSplit;
		return totalSplit;
	}

	arrOut.push_back(strIn.substr(startIndex));
	++totalSplit;

	return totalSplit;
}

tstring StringUtil::joinString(const TV_STRING& arrIn, const tstring& strSplit, bool reverse /* = false */)
{
	tstring strOut;

	int nLength = int(arrIn.size());
	if (nLength <= 0) return strOut;

	if (reverse)
	{
		strOut += arrIn[nLength - 1];

		for (int i = nLength - 2; i >= 0; --i)
		{
			strOut += strSplit;
			strOut += arrIn[i];
		}
	}
	else
	{
		strOut += arrIn[0];

		for (int i = 1; i < nLength; ++i)
		{
			strOut += strSplit;
			strOut += arrIn[i];
		}
	}

	return strOut;
}

int StringUtil::replaceString(tstring& strInOut, const tstring& strSearch, const tstring& strReplace)
{
	TV_STRING arrSubString;
	StringUtil::splitString(arrSubString, strInOut, strSearch);

	int numSubString = (int)arrSubString.size();
	if (numSubString > 1)
	{
		strInOut = StringUtil::joinString(arrSubString, strReplace);
		return numSubString;
	}

	return 0;
}

}
