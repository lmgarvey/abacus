/**
 * @file AbacusView.cpp
 * @author L.M. Garvey
 *
 * View class for the abacus
 *
 * created october 2023
 * updated october 2023
 */

#include "pch.h"

#include <wx/dcbuffer.h>

#include "AbacusView.h"

/**
 * Initialize the abacus view class
 * @param parent The parent window for this class
 */
void AbacusView::Initialize(wxFrame *parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &AbacusView::OnPaint, this);
}


/**
 * Paint event, draws the window
 * @param event Paint event object
 */
void AbacusView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxLIGHT_GREY_BRUSH);
    dc.SetBackground(background);
    dc.Clear();

    mAbacus.OnDraw(&dc);
}
