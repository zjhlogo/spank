/*!
 * \file main.h
 * \date 10-11-2014 13:19:57
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <jni.h>
#include <GLES2/gl2.h>

extern "C"
{
	JNIEXPORT jboolean JNICALL Java_com_zjhlogo_libspank_GameEntry_initialize(JNIEnv* env, jobject obj, jint width, jint height);
	JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_terminate(JNIEnv* env, jobject obj);
	JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_resize(JNIEnv* env, jobject obj, jint width, jint height);
	JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_step(JNIEnv* env, jobject obj);
	JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_touchEvent(JNIEnv* env, jobject obj, jint actionType, jfloat x, jfloat y);
	JNIEXPORT void JNICALL Java_com_zjhlogo_libspank_GameEntry_zoom(JNIEnv* env, jobject obj, jfloat zoom);

};

