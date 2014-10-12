/*!
 * \file FileUtilWin32.cpp
 *
 * \author zjhlogo
 * \date 2014/10/12
 *
 * 
 */
#include <utils/FileUtil.h>
#include <utils/LogUtil.h>

bool FileUtil::readFile(BUFFER_DATA& bufferOut, const std::string& filePath)
{
	FILE* pFile = nullptr;
	int result = fopen_s(&pFile, filePath.c_str(), "rb");
	if (result != 0)
	{
		LOGE("Open file failed %s", filePath.c_str());
		return false;
	}

	fseek(pFile, 0, SEEK_END);
	int fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	bufferOut.clear();
	bufferOut.resize(fileSize);
	if (fileSize > 0)
	{
		fread(bufferOut.data(), sizeof(char), bufferOut.size(), pFile);
	}

	fclose(pFile);

	return true;
}
