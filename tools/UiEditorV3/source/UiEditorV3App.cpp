/*!
 * \file UiEditorV3App.cpp
 * \date 2015/01/18
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "UiEditorV3App.h"
#include "UiEditorV3Frame.h"

wxIMPLEMENT_APP(UiEditorV3App);

UiEditorV3App::UiEditorV3App()
{
}

UiEditorV3App::~UiEditorV3App()
{
}

bool UiEditorV3App::OnInit()
{
	wxInitAllImageHandlers();

	UiEditorV3Frame* frame = new UiEditorV3Frame(NULL);
	frame->Maximize(true);
	frame->Show(true);

	return true;
}
