/*!
 * \file FileUtilAndroid.cpp
 *
 * \author zjhlogo
 * \date 2014/10/12
 *
 * 
 */
#include <utils/FileUtil.h>
#include <utils/LogUtil.h>
#include <android/asset_manager_jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_SpankActivityBase_initNativeAssetManager(JNIEnv* env, jclass cls, jobject assetManager);
};

AAssetManager* g_pAssetMgr = nullptr;

JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_SpankActivityBase_initNativeAssetManager(JNIEnv* env, jclass cls, jobject assetManager)
{
	g_pAssetMgr = AAssetManager_fromJava(env, assetManager);
}

namespace spank
{

bool FileUtil::readFile(BUFFER_DATA& bufferOut, const std::string& filePath)
{
	AAsset* pAsset = AAssetManager_open(g_pAssetMgr, filePath.c_str(), AASSET_MODE_UNKNOWN);
	if (!pAsset)
	{
		LOGE("Open file failed %s", filePath.c_str());
		return false;
	}

	size_t fileSize = AAsset_getLength(pAsset);
	bufferOut.clear();
	bufferOut.resize(fileSize);

	if (fileSize > 0)
	{
		AAsset_read(pAsset, bufferOut.data(), bufferOut.size());
	}
	AAsset_close(pAsset);

	return true;
}

}
