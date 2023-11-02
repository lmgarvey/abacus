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
 * @param event Event to handle
 */
void AbacusView::OnLeftDown(wxMouseEvent &event)
{
    mClickedY = event.GetY();
    mPreviousMouseY = event.GetY();
    mGrabbedBead = mAbacus.HitTest(event.GetX(), event.GetY());
}

/**
 * Handle the left mouse button up event
 * @param event Event to handle
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
        UpdateLITEValueClicked();
        mGrabbedBead = nullptr;
        Refresh();
    }
}

/**
 * Handle the mouse move event
 * @param event Event to handle
 */
void AbacusView::OnMouseMove(wxMouseEvent &event)
{
    // are we holding a bead?
    if (mGrabbedBead != nullptr) {
        // beads stay on their column, only move vertically
        const int x = mGrabbedBead->GetX();

        // are we still clicking? if so, keep moving this bead and its neighbors
        if (event.LeftIsDown()) {
            mGrabbedBead->SetLocation(x, event.GetY());

            // moving up on the screen
            if (event.GetY() < mPreviousMouseY)
            {
                // move everyone above us that we are touching (they are currently deactivated)
                int height_mul = (int)mGrabbedBead->GetTowardNeighbors().size();
                for (auto & neighbor : mGrabbedBead->GetTowardNeighbors())
                {
                    if (!neighbor->GetActivated())
                    {
                        neighbor->SetLocation(x, event.GetY() - neighbor->GetHeight() * height_mul);
                    }
                    height_mul--;
                }
                // snap everyone below us to be deactivated
                for (auto & neighbor : mGrabbedBead->GetFromNeighbors())
                {
                    neighbor->SetLocation(x, neighbor->GetFromBar());
                    neighbor->SetActivated(false);
                }
            }
            // moving down on the screen
            else if (event.GetY() > mPreviousMouseY)
            {
                // move everyone below us that we are touching (they are currently activated)
                int height_mul = 1;
                for (auto & neighbor : mGrabbedBead->GetFromNeighbors())
                {
                    if (neighbor->GetActivated()) {
                        neighbor->SetLocation(x, event.GetY() + neighbor->GetHeight() * height_mul);
                        height_mul++;
                    }
                }

                // snap everyone above us to be activated
                for (auto & neighbor : mGrabbedBead->GetTowardNeighbors())
                {
                    neighbor->SetLocation(x, neighbor->GetTowardBar());
                    neighbor->SetActivated(true);
                }
            }
            mPreviousMouseY = event.GetY();
        }   // of event.LeftIsDown()

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
            // TK snap its neighbors

            UpdateLITEValueDragged();

            mGrabbedBead = nullptr;
        }   // of !event.LeftIsDown()

        // force screen to redraw
        Refresh();
    }
}

/**
 * Clicking a bead flips its position, update on the abacus
 */
void AbacusView::UpdateLITEValueClicked()
{
    int y = mGrabbedBead->GetTowardBar();   // assume we Are Activating and moving Toward bar

    // if it's at the bar already, move it away
    if (mGrabbedBead->GetActivated())
    {
        y = mGrabbedBead->GetFromBar();
    }

    mGrabbedBead->SetLocation(mGrabbedBead->GetX(), y);
    mGrabbedBead->SetActivated(!mGrabbedBead->GetActivated());

    int beadValue;
    if (mGrabbedBead->GetActivated())
    {
        beadValue = HandleActivation();
    }
    else
    {
        beadValue = HandleDeactivation();
    }

    mAbacus.UpdateLITEValue(beadValue);
}

/**
 * Determines if the LITE value has changed, update on the abacus if so
 * Get here after left mouse up, so all beads are either at 'toward' or 'from'
 */
void AbacusView::UpdateLITEValueDragged()
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
        // TK this for long long
        int beadValue;
        if (now_activated)
        {
            beadValue = HandleActivation();
        }
        else
        {
            beadValue = HandleDeactivation();
        }

        mAbacus.UpdateLITEValue(beadValue);
    }
}

/**
 * Handle the case of an earth bead being activated, also moves beads above it
 * @return the final LITE value
 */
int AbacusView::HandleActivation()
{
    int LITE = (int)pow(mGrabbedBead->GetBaseValue(), mGrabbedBead->GetColPos());
    // moving toward the bar, move all beads above us
    for (const auto& neighbor : mGrabbedBead->GetTowardNeighbors())
    {
        // only move, activate, and add if they weren't already activated
        if (!neighbor->GetActivated())
        {
            neighbor->SetLocation(neighbor->GetX(), neighbor->GetTowardBar());
            neighbor->SetActivated(true);

            LITE += (int)pow(neighbor->GetBaseValue(), neighbor->GetColPos());
        }
    }
    return LITE;
}

/**
 * Handle the case of an earth bead being deactivated, also moves beads below it
 * @return the final LITEvalue
 */
int AbacusView::HandleDeactivation()
{
    int LITE = (int)pow(mGrabbedBead->GetBaseValue(), mGrabbedBead->GetColPos()) * -1;
    for (const auto& neighbor : mGrabbedBead->GetFromNeighbors())
    {
        // only move, deactivate, and subtract if they were activated (they are Being deactivated)
        if (neighbor->GetActivated())
        {
            neighbor->SetLocation(neighbor->GetX(), neighbor->GetFromBar());
            neighbor->SetActivated(false);
            LITE -= (int)pow(neighbor->GetBaseValue(), neighbor->GetColPos());
        }
    }
    return LITE;
}
