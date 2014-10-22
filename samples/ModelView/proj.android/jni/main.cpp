/*!
 * \file main.cpp
 * \date 10-11-2014 13:20:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "main.h"
#include <ModelViewApp.h>
#include <utils/LogUtil.h>

class FrameworkAndroid : public spank::Framework {};
FrameworkAndroid* g_pFrameworkAndroid = nullptr;
ModelViewApp* g_pModelViewApp = nullptr;

JNIEXPORT jboolean JNICALL Java_com_zjhlogo_libspank_GameEntry_initialize(JNIEnv* env, jobject obj, jint width, jint height)
{
	if (g_pFrameworkAndroid)
	{
		g_pFrameworkAndroid->getRenderer()->reload(false);
		return true;
	}

	// initialize framework
	g_pFrameworkAndroid = new FrameworkAndroid();
	if (!g_pFrameworkAndroid->initialize())
	{
		g_pFrameworkAndroid->terminate();
		SAFE_DELETE(g_pFrameworkAndroid);
		return false;
	}
	g_pFrameworkAndroid->getRenderer()->resize(width, height);

	// initialize app
	g_pModelViewApp = new ModelViewApp();
	g_pModelViewApp->setFramework(g_pFrameworkAndroid);
	if (!g_pModelViewApp->initialize())
	{
		g_pModelViewApp->terminate();
		SAFE_DELETE(g_pModelViewApp);

		g_pFrameworkAndroid->terminate();
		SAFE_DELETE(g_pFrameworkAndroid);

		return false;
	}

	return true;
}

JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_terminate(JNIEnv* env, jobject obj)
{
	LOGD("GameEntry terminate");

	g_pModelViewApp->terminate();
	SAFE_DELETE(g_pModelViewApp);

	g_pFrameworkAndroid->terminate();
	SAFE_DELETE(g_pFrameworkAndroid);
}

JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_resize(JNIEnv* env, jobject obj, jint width, jint height)
{
	g_pFrameworkAndroid->getRenderer()->resize(width, height);
}

JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_step(JNIEnv* env, jobject obj)
{
	g_pModelViewApp->step();
}