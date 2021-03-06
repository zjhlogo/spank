/*!
 * \file DeviceWin32.cpp
 * \date 10-10-2014 12:22:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "DeviceWin32.h"
#include <Framework.h>

namespace spank
{

Framework* DeviceWin32::s_pFramework{ nullptr };

DeviceWin32::DeviceWin32()
{
	// TODO: 
}

DeviceWin32::~DeviceWin32()
{
	// TODO: 
}

bool DeviceWin32::initialize(HINSTANCE hInstance, int width, int height, const char* pszClassName, const char* pszWindowTitle)
{
	if (!createWindow(hInstance, width, height, pszClassName, pszWindowTitle)) return false;
	m_width = width;
	m_height = height;

	if (!createEglContext()) return false;
	return true;
}

void DeviceWin32::terminate()
{
	destroyEglContext();
	destroyWindow();
}

void DeviceWin32::setFramework(Framework* pFramework)
{
	s_pFramework = pFramework;
}

Framework* DeviceWin32::getFramework()
{
	return s_pFramework;
}

bool DeviceWin32::createWindow(HINSTANCE hInstance, int width, int height, const char* pszClassName, const char* pszWindowTitle)
{
	WNDCLASS winClass;
	memset(&winClass, 0, sizeof(winClass));
	winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winClass.lpfnWndProc = (WNDPROC)DeviceWin32::mainWndProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = hInstance;
	winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = pszClassName;
	RegisterClass(&winClass);

	// screen width, height
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	// window width, height
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, dwStyle, FALSE);
	int nAdjustWidth = rc.right - rc.left;
	int nAdjustHeight = rc.bottom - rc.top;

	// create the window
	m_nativeWindow = CreateWindow(pszClassName,
								  pszWindowTitle,
								  dwStyle,
								  (nScreenWidth - nAdjustWidth) / 2, (nScreenHeight - nAdjustHeight) / 2,
								  nAdjustWidth, nAdjustHeight,
								  NULL, NULL, hInstance, NULL);

	// Get the associated device context from the window
	m_nativeDisplay = GetDC(m_nativeWindow);

	ShowWindow(m_nativeWindow, SW_SHOW);
	SetForegroundWindow(m_nativeWindow);
	SetFocus(m_nativeWindow);

	return true;
}

void DeviceWin32::destroyWindow()
{
	// Release the device context.
	if (m_nativeDisplay)
	{
		ReleaseDC(m_nativeWindow, m_nativeDisplay);
		m_nativeDisplay = nullptr;
	}

	// Destroy the window
	if (m_nativeWindow)
	{
		DestroyWindow(m_nativeWindow);
		m_nativeWindow = nullptr;
	}
}

bool DeviceWin32::createEglContext()
{
	// get display
	m_eglDisplay = eglGetDisplay(m_nativeDisplay);
	if (m_eglDisplay == EGL_NO_DISPLAY) return false;

	// initialize egl
	EGLint eglMajorVersion = 0;
	EGLint eglMinorVersion = 0;
	if (!eglInitialize(m_eglDisplay, &eglMajorVersion, &eglMinorVersion)) return false;

	// choose egl config
	const EGLint configurationAttributes[] =
	{
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};
	EGLConfig eglConfig = nullptr;
	EGLint configsReturned = 0;
	if (!eglChooseConfig(m_eglDisplay, configurationAttributes, &eglConfig, 1, &configsReturned)) return false;

	// create surface
	m_eglSurface = eglCreateWindowSurface(m_eglDisplay, eglConfig, m_nativeWindow, nullptr);
	if (m_eglSurface == EGL_NO_SURFACE) return false;

	// setup context
	EGLint contextAttributes[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};
	EGLContext eglContext = eglCreateContext(m_eglDisplay, eglConfig, NULL, contextAttributes);
	if (eglContext == EGL_NO_CONTEXT) return false;

	if (!eglBindAPI(EGL_OPENGL_ES_API)) return false;

	if (!eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, eglContext)) return false;

	return true;
}

void DeviceWin32::destroyEglContext()
{
	if (m_eglDisplay)
	{
		// To release the resources in the context, first the context has to be released from its binding with the current thread.
		eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

		// Terminate the display, and any resources associated with it (including the EGLContext)
		eglTerminate(m_eglDisplay);

		m_eglDisplay = nullptr;
	}
}

LRESULT CALLBACK DeviceWin32::mainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static bool s_bLButtonDown = false;

	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	{
		s_bLButtonDown = true;
		int posx = (int)(short)LOWORD(lParam);
		int posy = (int)(short)HIWORD(lParam);
		glm::vec2 touchPos(posx, posy);
		s_pFramework->getTouchDelegateMgr()->handleTouchEvent(ITouchDelegate::TOUCH_BEGIN, touchPos);
	}
		break;
	case WM_MOUSEMOVE:
	{
		if (s_bLButtonDown)
		{
			int posx = (int)(short)LOWORD(lParam);
			int posy = (int)(short)HIWORD(lParam);
			glm::vec2 touchPos(posx, posy);
			s_pFramework->getTouchDelegateMgr()->handleTouchEvent(ITouchDelegate::TOUCH_MOVE, touchPos);
		}
	}
		break;
	case WM_LBUTTONUP:
	{
		s_bLButtonDown = false;
		int posx = (int)(short)LOWORD(lParam);
		int posy = (int)(short)HIWORD(lParam);
		glm::vec2 touchPos(posx, posy);
		s_pFramework->getTouchDelegateMgr()->handleTouchEvent(ITouchDelegate::TOUCH_END, touchPos);
	}
		break;
	case WM_MOUSEWHEEL:
	{
		short wheel = HIWORD(wParam);
		float zoom = 0.5f;
		if (wheel < 0) zoom = 2.0f;
		s_pFramework->getTouchDelegateMgr()->handleZoomEvent(zoom);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}

}
