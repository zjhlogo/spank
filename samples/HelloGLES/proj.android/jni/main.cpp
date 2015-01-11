/*!
 * \file main.cpp
 * \date 10-11-2014 13:20:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "main.h"
#include <HelloGLESApp.h>
#include <utils/LogUtil.h>

class FrameworkAndroid : public spank::Framework {};
FrameworkAndroid* g_pFrameworkAndroid = nullptr;
HelloGLESApp* g_pHelloGLESApp = nullptr;

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
	g_pHelloGLESApp = new HelloGLESApp();
	g_pHelloGLESApp->setFramework(g_pFrameworkAndroid);
	if (!g_pHelloGLESApp->initialize())
	{
		g_pHelloGLESApp->terminate();
		SAFE_DELETE(g_pHelloGLESApp);

		g_pFrameworkAndroid->terminate();
		SAFE_DELETE(g_pFrameworkAndroid);

		return false;
	}

	return true;
}

JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_terminate(JNIEnv* env, jobject obj)
{
	LOGD("GameEntry terminate");

	g_pHelloGLESApp->terminate();
	SAFE_DELETE(g_pHelloGLESApp);

	g_pFrameworkAndroid->terminate();
	SAFE_DELETE(g_pFrameworkAndroid);
}

JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_resize(JNIEnv* env, jobject obj, jint width, jint height)
{
	g_pFrameworkAndroid->getRenderer()->resize(width, height);
}

JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_step(JNIEnv* env, jobject obj)
{
	g_pHelloGLESApp->step();
}

JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_touchEvent(JNIEnv* env, jobject obj, jint actionType, jfloat x, jfloat y)
{
	glm::vec2 touchPos(x, y);
	g_pFrameworkAndroid->getTouchDelegateMgr()->handleTouchEvent((spank::ITouchDelegate::ACTION_TYPE_ID)actionType, touchPos);
}

JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_zoom(JNIEnv* env, jobject obj, jfloat zoom)
{
	g_pFrameworkAndroid->getTouchDelegateMgr()->handleZoomEvent(zoom);
}
