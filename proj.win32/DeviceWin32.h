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

class DeviceWin32
{
public:
	DeviceWin32();
	virtual ~DeviceWin32();

	bool initialize(HINSTANCE hInstance, int width, int height);
	void terminate();

	inline EGLDisplay getEglDisplay() const { return m_eglDisplay; };
	inline EGLSurface getEglSurface() const { return m_eglSurface; };

private:
	bool createWindow(HINSTANCE hInstance, int width, int height);
	void destroyWindow();

	bool createEglContext();
	void destroyEglContext();

	static LRESULT CALLBACK mainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	EGLNativeWindowType m_nativeWindow{ nullptr };
	EGLNativeDisplayType m_nativeDisplay{ nullptr };
	EGLDisplay m_eglDisplay{ nullptr };
	EGLSurface m_eglSurface{ nullptr };

};

}
