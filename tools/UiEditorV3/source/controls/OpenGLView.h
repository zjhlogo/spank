/*!
 * \file OpenGLView.h
 * \date 11-16-2013 21:09:56
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __OPENGLVIEW_H__
#define __OPENGLVIEW_H__

#include <glm/glm.hpp>
#include <EGL/egl.h>

class OpenGLView;

class IOpenGLRenderer
{
public:
	enum STATE
	{
		REQUEST_FOCUS		= 0x00000001,
		DISABLE_RENDER		= 0x00000002,
	};

public:
	IOpenGLRenderer():m_nState(0),m_pView(NULL) {};
	virtual ~IOpenGLRenderer() {};

	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual void install() = 0;
	virtual void uninstall() = 0;
	virtual void resize(int width, int height) = 0;

	virtual void onLeftButtonDown(wxMouseEvent& event) {};
	virtual void onRightButtonDown(wxMouseEvent& event) {};
	virtual void onMouseMove(wxMouseEvent& event) {};
	virtual void onLeftButtonUp(wxMouseEvent& event) {};
	virtual void onChar(wxKeyEvent& event) {};
	virtual void onKeyDown(wxKeyEvent& event) {};
	virtual void setScrollPos(const glm::vec2& scrollPos) {};

	virtual bool setState(int state, bool set);
	inline bool checkState(int state) const { return ((m_nState & state) == state); };

	inline OpenGLView* getView() const { return m_pView; };
	inline void setView(OpenGLView* pView) { m_pView = pView; };

private:
	int m_nState;
	OpenGLView* m_pView;

};

class OpenGLView : public wxWindow
{
public:
	OpenGLView();
	OpenGLView(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0);
	virtual ~OpenGLView();

	void setRenderer(IOpenGLRenderer* pRenderer);
	inline IOpenGLRenderer* getRenderer() const { return m_pRenderer; };

	void render();

	void setScroller(wxScrollBar* scrollH, wxScrollBar* scrollV);
	void setScrollPos(float x, float y);
	int getScrollH() const;
	int getScrollV() const;

	const glm::vec2& getScrollPos() const { return m_currScrollPos; };

private:
	void Init();
	void onResized(wxSizeEvent& evt);
	void onPaint(wxPaintEvent& evt);
	void onIdle(wxIdleEvent& event);

	void onLeftButtonDown(wxMouseEvent& event);
	void onRightButtonDown(wxMouseEvent& event);
	void onMouseMove(wxMouseEvent& event);
	void onMouseWheel(wxMouseEvent& event);
	void onLeftButtonUp(wxMouseEvent& event);
	void onChar(wxKeyEvent& event);
	void onKeyDown(wxKeyEvent& event);

	bool createWindow(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0);

	bool createEglContext();
	void destroyEglContext();

	void updateScrollBar();

private:
	EGLNativeWindowType m_nativeWindow{ nullptr };
	EGLNativeDisplayType m_nativeDisplay{ nullptr };
	EGLDisplay m_eglDisplay{ nullptr };
	EGLSurface m_eglSurface{ nullptr };

	IOpenGLRenderer* m_pRenderer;
	int m_nLastTime;

	wxScrollBar* m_scrollEditorH;
	wxScrollBar* m_scrollEditorV;
	glm::vec2 m_currScrollPos;

	int m_nScrollRangeX;
	int m_nScrollRangeY;

};
#endif // __OPENGLVIEW_H__
