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
    mClickedY = event.GetY();
    mGrabbedBead = mAbacus.HitTest(event.GetX(), event.GetY());
}

/**
 * Handle the left mouse button up event
 * @param event
 */
void AbacusView::OnLeftUp(wxMouseEvent &event)
{
    int deltaY = abs(event.GetY() - mClickedY);

    // clicking and dragging
    if (deltaY > mDelta)
    {
        OnMouseMove(event);
        return;
    }

    // single click, flip to be up or down
    if (mGrabbedBead != nullptr)
    {
        int x = mGrabbedBead->GetX();
        int y = mGrabbedBead->GetY();
        if (y == mGrabbedBead->GetLowerY())
        {
            y = mGrabbedBead->GetUpperY();
        }
        else
        {
            y = mGrabbedBead->GetLowerY();
        }
        mGrabbedBead->SetLocation(x, y);

        // the bead moved, update the LITE display and flip activation
        mGrabbedBead->SetActivated(!mGrabbedBead->GetActivated());
        int beadValue = mGrabbedBead->GetValue();
        if (!mGrabbedBead->GetActivated())
        {
            beadValue *= -1;
        }
        mAbacus.UpdateLITEValue(beadValue);

        mGrabbedBead = nullptr;

        Refresh();
    }
}

/**
 * Handle the mouse move event
 * @param event
 */
void AbacusView::OnMouseMove(wxMouseEvent &event)
{
    // are we holding a bead?
    if (mGrabbedBead != nullptr) {
        // beads stay on their column, only move vertically
        const int x = mGrabbedBead->GetX();

        // are we still clicking?
        if (event.LeftIsDown()) {
            mGrabbedBead->SetLocation(x, event.GetY());
        }
        // let go of mouse button -> let go of bead
        else {
            // snap bead up or down
            int upper_dst = abs(mGrabbedBead->GetUpperY() - event.GetY());
            int lower_dst = abs(mGrabbedBead->GetLowerY() - event.GetY());

            if (upper_dst < lower_dst)
            {
                // closer to up
                mGrabbedBead->SetLocation(x, mGrabbedBead->GetUpperY());
                mGrabbedBead->SetActivated(true);
            }
            else
            {
                // closer to down
                mGrabbedBead->SetLocation(x, mGrabbedBead->GetLowerY());
                mGrabbedBead->SetActivated(false);
            }

            // the bead moved, update the LITE display (activation is already set from above)
            int beadValue = mGrabbedBead->GetValue();
            if (!mGrabbedBead->GetActivated())
            {
                beadValue *= -1;
            }
            mAbacus.UpdateLITEValue(beadValue);

            mGrabbedBead = nullptr;
        }

        // force screen to redraw
        Refresh();
    }
}

/**
 * A bead has moved, so the integer display value needs to be updated
 */
void AbacusView::UpdateLITEValue()
{

}
