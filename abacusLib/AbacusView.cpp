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
    Bind(wxEVT_LEFT_DOWN, &AbacusView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &AbacusView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &AbacusView::OnMouseMove, this);
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

/**
 * Handle the left mouse button down event
 * @param event
 */
void AbacusView::OnLeftDown(wxMouseEvent &event)
{
    auto bead = mAbacus.HitTest(event.GetX(), event.GetY());
}

/**
 * Handle the left mouse button up event
 * @param event
 */
void AbacusView::OnLeftUp(wxMouseEvent &event)
{

}

/**
 * Handle the mouse move event
 * @param event
 */
void AbacusView::OnMouseMove(wxMouseEvent &event)
{

}
