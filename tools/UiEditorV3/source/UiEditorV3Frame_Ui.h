/////////////////////////////////////////////////////////////////////////////
// Name:        UiEditorV3Frame_Ui.h
// Purpose:     
// Author:      zjhlogo
// Modified by: 
// Created:     18/01/2015 13:40:23
// RCS-ID:      
// Copyright:   zjhlogo (C) 2011-2012
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 18/01/2015 13:40:23

#ifndef _UIEDITORV3FRAME_UI_H_
#define _UIEDITORV3FRAME_UI_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/aui/framemanager.h"
#include "wx/frame.h"
#include "wx/toolbar.h"
#include "wx/notebook.h"
#include "wx/treectrl.h"
#include "wx/glcanvas.h"
#include "wx/scrolbar.h"
#include "wx/statusbr.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class wxMenu;
class wxTreeCtrl;
class wxPropertyGrid;
class OpenGLView;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define SYMBOL_UIEDITORV3FRAME_UI_STYLE wxDEFAULT_FRAME_STYLE
#define SYMBOL_UIEDITORV3FRAME_UI_TITLE _("Ui Editor V3")
#define SYMBOL_UIEDITORV3FRAME_UI_IDNAME ID_UI_EDITOR_FRAME
#define SYMBOL_UIEDITORV3FRAME_UI_SIZE wxSize(800, 600)
#define SYMBOL_UIEDITORV3FRAME_UI_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * UiEditorV3Frame_Ui class declaration
 */

class UiEditorV3Frame_Ui: public wxFrame
{    
	DECLARE_CLASS( UiEditorV3Frame_Ui )
	DECLARE_EVENT_TABLE()

public:
	/// Constructors
	UiEditorV3Frame_Ui();
	UiEditorV3Frame_Ui( wxWindow* parent, wxWindowID id = SYMBOL_UIEDITORV3FRAME_UI_IDNAME, const wxString& caption = SYMBOL_UIEDITORV3FRAME_UI_TITLE, const wxPoint& pos = SYMBOL_UIEDITORV3FRAME_UI_POSITION, const wxSize& size = SYMBOL_UIEDITORV3FRAME_UI_SIZE, long style = SYMBOL_UIEDITORV3FRAME_UI_STYLE );

	bool Create( wxWindow* parent, wxWindowID id = SYMBOL_UIEDITORV3FRAME_UI_IDNAME, const wxString& caption = SYMBOL_UIEDITORV3FRAME_UI_TITLE, const wxPoint& pos = SYMBOL_UIEDITORV3FRAME_UI_POSITION, const wxSize& size = SYMBOL_UIEDITORV3FRAME_UI_SIZE, long style = SYMBOL_UIEDITORV3FRAME_UI_STYLE );

	/// Destructor
	~UiEditorV3Frame_Ui();

	/// Initialises member variables
	void Init();

	/// Creates the controls and sizers
	void CreateControls();

////@begin UiEditorV3Frame_Ui event handler declarations

////@end UiEditorV3Frame_Ui event handler declarations

////@begin UiEditorV3Frame_Ui member function declarations

	/// Returns the AUI manager object
	wxAuiManager& GetAuiManager() { return m_auiManager; }

	/// Retrieves bitmap resources
	wxBitmap GetBitmapResource( const wxString& name );

	/// Retrieves icon resources
	wxIcon GetIconResource( const wxString& name );
////@end UiEditorV3Frame_Ui member function declarations

	/// Should we show tooltips?
	static bool ShowToolTips();

////@begin UiEditorV3Frame_Ui member variables
	wxAuiManager m_auiManager;
	wxMenu* m_editMenu;
	wxMenu* m_toolMenu;
	wxToolBar* m_toolBar;
	wxTreeCtrl* m_treeProjects;
	wxPropertyGrid* m_properties;
	OpenGLView* m_glView;
	wxScrollBar* m_scrollV;
	wxScrollBar* m_scrollH;
	/// Control identifiers
	enum {
		ID_UI_EDITOR_FRAME = 10000,
		IDM_EDIT_REPLACE = 10112,
		IDM_EDIT_MAKE_BEST_SIZE = 10043,
		IDM_EDIT_DUPLICATE_WINDOWS = 10003,
		IDM_EDIT_RENAME_SELECTIONS = 10061,
		IDM_ELEMENTS_ADD_DIALOG = 10011,
		IDM_ELEMENTS_REMOVE_DIALOG = 10014,
		IDM_ELEMENTS_RENAME_DIALOG = 10015,
		IDM_ELEMENTS_COMMENT_DIALOG = 10051,
		IDM_ELEMENTS_ADD_ATTRIBUTE = 10027,
		IDM_ELEMENTS_REMOVE_ATTRIBUTE = 10028,
		IDM_ALIGN_LEFT = 10026,
		IDM_ALIGN_CENTER = 10012,
		IDM_ALIGN_RIGHT = 10030,
		IDM_ALIGN_TOP = 10031,
		IDM_ALIGN_MIDDLE = 10013,
		IDM_ALIGN_BOTTOM = 10032,
		IDM_ALIGN_GAP_HORIZONTAL = 10033,
		IDM_ALIGN_GAP_VERTICAL = 10034,
		IDM_ALIGN_MAKE_SAME_WIDTH = 10029,
		IDM_ALIGN_MAKE_SAME_HEIGHT = 10039,
		IDM_ALIGN_MAKE_SAME_SIZE = 10040,
		IDM_LAYER_UP = 10009,
		IDM_LAYER_DOWN = 10018,
		IDM_LAYER_IN = 10020,
		IDM_LAYER_OUT = 10021,
		IDM_VIEW_PREVIEW = 10038,
		IDM_VIEW_LANGUAGES = 10017,
		IDM_VIEW_SHOW_SELECTION = 10024,
		IDM_VIEW_CURRENT_USING_TEX = 10050,
		IDM_VIEW_SET_BG = 10048,
		IDM_VIEW_CLEAR_BG = 10049,
		IDM_TOOLS_GEN_BINDING_CODE_CPP = 10025,
		IDM_TOOLS_GET_CONTROL_PATH = 10002,
		IDM_TOOLS_GEN_CHARSET = 10111,
		IDT_MAIN_TOOLBAR = 10010,
		IDM_ALIGN_SAME_WIDTH = 10035,
		IDM_ALIGN_SAME_HEIGHT = 10036,
		IDM_ALIGN_SAME_SIZE = 10037,
		ID_NOTEBOOK_LAYOUT_LEFT = 10001,
		ID_TREECTRL_PROJECTS = 10016,
		ID_NOTEBOOK_LAYOUT_RIGHT = 10004,
		ID_PROPERTIES = 10019,
		ID_NOTEBOOK_LAYOUT_CENTER = 10005,
		ID_PANEL = 10006,
		ID_GLCANVAS = 10007,
		ID_SCROLLBAR_V = 10008,
		ID_SCROLLBAR_H = 10022,
		ID_STATUSBAR = 10023
	};
////@end UiEditorV3Frame_Ui member variables
};

#endif
	// _UIEDITORV3FRAME_UI_H_
