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
        int y = mGrabbedBead->GetTowardBar();   // assume we Are Activating, move Toward bar

        // if it's at the bar already, move it away
        if (mGrabbedBead->GetActivated())
        {
            y = mGrabbedBead->GetFromBar();
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
            int toward_dst = abs(mGrabbedBead->GetTowardBar() - event.GetY());
            int from_dst = abs(mGrabbedBead->GetFromBar() - event.GetY());

            if (toward_dst < from_dst)
            {
                // closer to bar, snap there
                mGrabbedBead->SetLocation(x, mGrabbedBead->GetTowardBar());
                mGrabbedBead->SetActivated(true);
            }
            else
            {
                // farther from bar, snap away from it
                mGrabbedBead->SetLocation(x, mGrabbedBead->GetFromBar());
                mGrabbedBead->SetActivated(false);
            }

            UpdateLITEValue();

            mGrabbedBead = nullptr;
        }

        // force screen to redraw
        Refresh();
    }
}

/**
 * Determines if the LITE value has changed, and updates it on the abacus if so
 */
void AbacusView::UpdateLITEValue()
{
    int original_toward_dst = abs(mClickedY - mGrabbedBead->GetTowardBar());
    int original_from_dst = abs(mClickedY - mGrabbedBead->GetFromBar());

    // if it was initially toward the bar
    bool originally_activated = original_toward_dst < original_from_dst;

    // if it's currently toward the bar
    bool now_activated = mGrabbedBead->GetY() == mGrabbedBead->GetTowardBar();

    // if it changed positions wrt the bar
    if (originally_activated != now_activated)
    {
        int beadValue = mGrabbedBead->GetValue();
        if (!mGrabbedBead->GetActivated()) {
            beadValue *= -1;
        }
        mAbacus.UpdateLITEValue(beadValue);
    }
}
