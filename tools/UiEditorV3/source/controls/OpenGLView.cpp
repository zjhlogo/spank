/*!
 * \file OpenGLView.cpp
 * \date 11-16-2013 21:10:00
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "OpenGLView.h"
#include <GLES2/gl2.h>

bool IOpenGLRenderer::setState(int state, bool set)
{
	int oldState = m_nState;
	if (set) m_nState |= state;
	else m_nState &= (~state);
	return (oldState != m_nState);
}

OpenGLView::OpenGLView()
{
	Init();
}

OpenGLView::OpenGLView(wxWindow *parent, wxWindowID id /* = wxID_ANY */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */)
{
	Init();
	createWindow(parent, id, pos, size, style);
	createEglContext();
}

void OpenGLView::Init()
{
	m_pRenderer = NULL;
	m_nLastTime = ::timeGetTime();

	m_scrollEditorH = NULL;
	m_scrollEditorV = NULL;
	m_nScrollRangeX = 0;
	m_nScrollRangeY = 0;

	Bind(wxEVT_PAINT, &OpenGLView::onPaint, this, wxID_ANY);
	Bind(wxEVT_SIZE, &OpenGLView::onResized, this, wxID_ANY);
	Bind(wxEVT_IDLE, &OpenGLView::onIdle, this, wxID_ANY);
	Bind(wxEVT_LEFT_DOWN, &OpenGLView::onLeftButtonDown, this, wxID_ANY);
	Bind(wxEVT_RIGHT_DOWN, &OpenGLView::onRightButtonDown, this, wxID_ANY);
	Bind(wxEVT_MOTION, &OpenGLView::onMouseMove, this, wxID_ANY);	
	Bind(wxEVT_LEFT_UP, &OpenGLView::onLeftButtonUp, this, wxID_ANY);
	Bind(wxEVT_CHAR, &OpenGLView::onChar, this, wxID_ANY);
	Bind(wxEVT_KEY_DOWN, &OpenGLView::onKeyDown, this, wxID_ANY);
	Bind(wxEVT_MOUSEWHEEL, &OpenGLView::onMouseWheel, this, wxID_ANY);
}

OpenGLView::~OpenGLView()
{
	destroyEglContext();
}

void OpenGLView::setRenderer(IOpenGLRenderer* pRenderer)
{
	if (m_pRenderer) m_pRenderer->uninstall();
	m_pRenderer = pRenderer;
	if (m_pRenderer)
	{
		m_pRenderer->setView(this);
		m_pRenderer->install();
		m_pRenderer->resize(GetSize().x, GetSize().y);
		setScrollPos(getScrollH(), getScrollV());
	}
}

void OpenGLView::onResized(wxSizeEvent& evt)
{
	updateScrollBar();
	if (m_pRenderer) m_pRenderer->resize(GetSize().x, GetSize().y);
	Refresh();
	glViewport(0, 0, GetSize().x, GetSize().y);
}

void OpenGLView::onPaint(wxPaintEvent& evt)
{
	wxPaintDC dc(this);

	render();
}

void OpenGLView::onIdle(wxIdleEvent& event)
{
	render();
	event.RequestMore();
}

void OpenGLView::render()
{
	if (!IsShownOnScreen()) return;

	int nCurrTime = ::timeGetTime();
	float dt = (nCurrTime - m_nLastTime) / 1000.0f;
	m_nLastTime = nCurrTime;

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_pRenderer)
	{
		m_pRenderer->update(dt);
		if (m_pRenderer) m_pRenderer->render();
	}

	eglSwapBuffers(m_eglDisplay, m_eglSurface);
}

void OpenGLView::setScroller(wxScrollBar* scrollH, wxScrollBar* scrollV)
{
	m_scrollEditorH = scrollH;
	m_scrollEditorV = scrollV;

	m_nScrollRangeX = m_scrollEditorH->GetRange();
	m_nScrollRangeY = m_scrollEditorV->GetRange();
}

void OpenGLView::setScrollPos(float x, float y)
{
	m_currScrollPos.x = x - m_nScrollRangeX / 2;
	m_currScrollPos.y = y - m_nScrollRangeY / 2;

	if (m_scrollEditorH) m_scrollEditorH->SetThumbPosition(x);
	if (m_scrollEditorV) m_scrollEditorV->SetThumbPosition(y);

	if (m_pRenderer)
	{
		m_pRenderer->setScrollPos(m_currScrollPos);
		render();
	}
}

int OpenGLView::getScrollH() const
{
	if (m_scrollEditorH) return m_scrollEditorH->GetThumbPosition();
	return 0;
}

int OpenGLView::getScrollV() const
{
	if (m_scrollEditorV) return m_scrollEditorV->GetThumbPosition();
	return 0;
}

static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;
	default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		break;
	}

	return 0;
}

bool OpenGLView::createWindow(wxWindow *parent, wxWindowID id /* = wxID_ANY */, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */)
{
    if (!CreateBase(parent, id, pos, size, style, wxDefaultValidator, "OpenGLView")) return false;
    parent->AddChild(this);

	HINSTANCE hInst = (HINSTANCE)GetModuleHandle(NULL);

	WNDCLASSEX wc = {sizeof(WNDCLASSEX),	// Specifies the size of this structure
		CS_OWNDC,							// Specifies the class style
		MainWndProc,						// Pointer to the window procedure
		0,									// Specifies the number of extra bytes to allocate following the window-class structure
		0,									// Specifies the number of extra bytes to allocate following the window instance
		hInst,								// Handle to the instance
		LoadIcon(NULL, IDI_APPLICATION),	// Handle to the class icon
		LoadCursor(NULL, IDC_ARROW),		// Handle to the class cursor
		(HBRUSH)COLOR_WINDOW,				// Handle to the class background brush
		NULL,								// resource name of the class menu
		wxT("OpenGLView"),				    // Pointer to a null-terminated string or is an atom
		LoadIcon(NULL, IDI_APPLICATION)};	// Handle to a small icon that is associated with the window class
	RegisterClassEx(&wc);

    /*
       A general rule with OpenGL and Win32 is that any window that will have a
       HGLRC built for it must have two flags:  WS_CLIPCHILDREN & WS_CLIPSIBLINGS.
       You can find references about this within the knowledge base and most OpenGL
       books that contain the wgl function descriptions.
     */
    WXDWORD exStyle = 0;
    DWORD msflags = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    msflags |= MSWGetStyle(style, &exStyle);

	// choose the position/size for the new window
	int x, y, w, h;
	(void)MSWGetCreateWindowCoords(pos, size, x, y, w, h);

	// controlId is menu handle for the top level windows, so set it to 0
	// unless we're creating a child window
	int controlId = style & WS_CHILD ? GetId() : 0;

	// do create the window
	wxWindowCreationHook hook(this);

	m_hWnd = CreateWindowEx(0,
		wxT("OpenGLView"),
		wxT("OpenGLView"),
		msflags,
		x, y, w, h,
		(HWND)MSWGetParent(),
		(HMENU)wxUIntToPtr(controlId),
		hInst,
		NULL                        // no extra data
		);
	m_nativeWindow = m_hWnd;

	if (!m_hWnd) return false;
	SubclassWin(m_hWnd);

	m_nativeDisplay = GetDC(m_hWnd);
	if (!m_nativeDisplay) return false;

	return true;
}

bool OpenGLView::createEglContext()
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

void OpenGLView::destroyEglContext()
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

void OpenGLView::updateScrollBar()
{
	if (m_scrollEditorH)
	{
		m_scrollEditorH->SetPageSize(GetSize().x);
		m_scrollEditorH->SetThumbSize(GetSize().x);
	}

	if (m_scrollEditorV)
	{
		m_scrollEditorV->SetPageSize(GetSize().y);
		m_scrollEditorV->SetThumbSize(GetSize().y);
	}
}

void OpenGLView::onLeftButtonDown(wxMouseEvent& event)
{
	if (m_pRenderer)
	{
		m_pRenderer->onLeftButtonDown(event);
		if (m_pRenderer->checkState(IOpenGLRenderer::REQUEST_FOCUS)) this->SetFocus();
	}
}

void OpenGLView::onRightButtonDown(wxMouseEvent& event)
{
	if (m_pRenderer)
	{
		m_pRenderer->onRightButtonDown(event);
		if (m_pRenderer->checkState(IOpenGLRenderer::REQUEST_FOCUS)) this->SetFocus();
	}
}

void OpenGLView::onMouseMove(wxMouseEvent& event)
{
	if (m_pRenderer) m_pRenderer->onMouseMove(event);
}

void OpenGLView::onMouseWheel(wxMouseEvent& event)
{	
	GetParent()->HandleWindowEvent(event);
}

void OpenGLView::onLeftButtonUp(wxMouseEvent& event)
{
	if (m_pRenderer) m_pRenderer->onLeftButtonUp(event);
}

void OpenGLView::onChar(wxKeyEvent& event)
{
	if (m_pRenderer) m_pRenderer->onChar(event);
}

void OpenGLView::onKeyDown(wxKeyEvent& event)
{
	if (m_pRenderer) m_pRenderer->onKeyDown(event);
}
