/*!
 * \file DeviceWin32.h
 * \date 10-10-2014 12:22:25
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <EGL/egl.h>

namespace spank
{

class Framework;

class DeviceWin32
{
public:
	DeviceWin32();
	virtual ~DeviceWin32();

	bool initialize(HINSTANCE hInstance, int width, int height, const char* pszClassName, const char* pszWindowTitle);
	void terminate();

	static void setFramework(Framework* pFramework);
	static Framework* getFramework();

	inline EGLDisplay getEglDisplay() const { return m_eglDisplay; };
	inline EGLSurface getEglSurface() const { return m_eglSurface; };

	inline int getWidth() const { return m_width; };
	inline int getHeight() const { return m_height; };

private:
	bool createWindow(HINSTANCE hInstance, int width, int height, const char* pszClassName, const char* pszWindowTitle);
	void destroyWindow();

	bool createEglContext();
	void destroyEglContext();

	static LRESULT CALLBACK mainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	static Framework* s_pFramework;

	EGLNativeWindowType m_nativeWindow{ nullptr };
	EGLNativeDisplayType m_nativeDisplay{ nullptr };
	EGLDisplay m_eglDisplay{ nullptr };
	EGLSurface m_eglSurface{ nullptr };

	int m_width{ 0 };
	int m_height{ 0 };

};

}
