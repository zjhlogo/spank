/*!
 * \file main.cpp
 * \date 10-11-2014 13:20:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "main.h"
#include <HelloGLES3App.h>
#include <utils/LogUtil.h>

class FrameworkAndroid : public Framework {};
FrameworkAndroid* g_pFrameworkAndroid = nullptr;
HelloGLES3App* g_pHelloGLES3App = nullptr;

JNIEXPORT jboolean JNICALL Java_com_zjhlogo_libspank_GameEntry_initialize(JNIEnv* env, jobject obj)
{
	LOGD("GameEntry initialize");

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

	// initialize app
	g_pHelloGLES3App = new HelloGLES3App();
	g_pHelloGLES3App->setFramework(g_pFrameworkAndroid);
	if (!g_pHelloGLES3App->initialize(g_pFrameworkAndroid))
	{
		g_pHelloGLES3App->terminate();
		SAFE_DELETE(g_pHelloGLES3App);

		g_pFrameworkAndroid->terminate();
		SAFE_DELETE(g_pFrameworkAndroid);

		return false;
	}

	return true;
}

JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_terminate(JNIEnv* env, jobject obj)
{
	LOGD("GameEntry terminate");

	g_pHelloGLES3App->terminate();
	SAFE_DELETE(g_pHelloGLES3App);

	g_pFrameworkAndroid->terminate();
	SAFE_DELETE(g_pFrameworkAndroid);
}

JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_resize(JNIEnv* env, jobject obj, jint width, jint height)
{
	LOGD("GameEntry resize %dx%d", width, height);
}

JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_step(JNIEnv* env, jobject obj)
{
	g_pHelloGLES3App->step();
}
