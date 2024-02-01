/**
 * @file AbacusView.cpp
 * @author L.M. Garvey
 *
 * View class for the abacus
 *
 * created october 2023
 * updated november 2023
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

    wxPoint LITEpoint(100, 650);
    wxSize LITEsize(140, 30);
    mLITECheckBox.Create(parent, wxID_ANY, L"Show integer display", LITEpoint, LITEsize);
    mLITECheckBox.SetValue(true);

    wxPoint guidePoint(100, 685);
    wxSize guideSize(140, 30);
    mGuideCheckBox.Create(parent, wxID_ANY, L"Show guide", guidePoint, guideSize);
    mGuideCheckBox.SetValue(true);

    // the checkboxes are members in 2 places because they go out of scope after this
    mAbacus.AssignLITECheckBox(&mLITECheckBox);
    mAbacus.AssignGuideCheckBox(&mGuideCheckBox);
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

    // redraw the checkboxes each time, or they disappear
    mLITECheckBox.Refresh();
    mGuideCheckBox.Refresh();
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
    if (mGrabbedBead == nullptr)
    {
        Refresh();  // refresh in case a button or checkbox was clicked
    }

}

/**
 * Handle the left mouse button up event
 * @param event Event to handle
 */
void AbacusView::OnLeftUp(wxMouseEvent &event)
{
    // were we clicking the reset button?
    if (mAbacus.GetReset())
    {
        mAbacus.ResetBeads();
        Refresh();
        return;
    }

    // were we clicking the save button?
    if (mAbacus.GetSaving())
    {
        mAbacus.SaveState(true);
        Refresh();
        return;
    }

    // were we clicking the go back button?
    if (mAbacus.GetGoingBack())
    {
        mAbacus.GoToState(true);
        Refresh();
        return;
    }

    // were we clicking the go forth button?
    if (mAbacus.GetGoingForth())
    {
        mAbacus.GoToState(false);
        Refresh();
        return;
    }

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
        HandleSingleClick(event);
    }
}

/**
 * Handles a single click on a bead
 * Flips its position/activation, as well as for all relevant neighbors
 * @param event Event to handle
 */
void AbacusView::HandleSingleClick(wxMouseEvent &event)
{
    bool wasActivated = mGrabbedBead->GetActivated();
    // deactivating
    if (wasActivated)
    {
        mGrabbedBead->SetActivated(false);
        mGrabbedBead->SetLocation(mGrabbedBead->GetX(), mGrabbedBead->GetFromBar());
        for (auto &neighbor : mGrabbedBead->GetFromNeighbors())
        {
            neighbor->SetLocation(neighbor->GetX(), neighbor->GetFromBar());
            neighbor->SetActivated(false);
        }
    }
    // activating
    else
    {
        mGrabbedBead->SetActivated(true);
        mGrabbedBead->SetLocation(mGrabbedBead->GetX(), mGrabbedBead->GetTowardBar());
        for (auto &neighbor : mGrabbedBead->GetTowardNeighbors())
        {
            neighbor->SetLocation(neighbor->GetX(), neighbor->GetTowardBar());
            neighbor->SetActivated(true);
        }
    }
    mGrabbedBead = nullptr;
    Refresh();
}

/**
 * Handle the mouse move event
 * @param event Event to handle
 */
void AbacusView::OnMouseMove(wxMouseEvent &event)
{
    // are we holding a bead?
    if (mGrabbedBead != nullptr)
    {
        if (event.LeftIsDown())
        {
            HandleDragging(event);
        }
        else
        {
            HandleReleasing(event);
            mGrabbedBead = nullptr;
        }

        // force screen to redraw
        Refresh();
    }
}


/**
 * Handles a bead being clicked and dragged (not release)
 * @param event Event to handle
 */
void AbacusView::HandleDragging(wxMouseEvent &event)
{
    const int x = mGrabbedBead->GetX();
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
                height_mul--;
            }
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
            if (neighbor->GetActivated())
            {
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
}

/**
 * Handles the mouse click releasing after dragging
 * @param event Event to handle
 */
void AbacusView::HandleReleasing(wxMouseEvent &event)
{
    const int x = mGrabbedBead->GetX();

    // snap bead up or down
    int toward_dst = abs(mGrabbedBead->GetTowardBar() - event.GetY());
    int from_dst = abs(mGrabbedBead->GetFromBar() - event.GetY());

    if (toward_dst < from_dst)
    {
        // closer to bar, snap there for us and those between us and it
        mGrabbedBead->SetLocation(x, mGrabbedBead->GetTowardBar());
        mGrabbedBead->SetActivated(true);
        for (auto &neighbor : mGrabbedBead->GetTowardNeighbors())
        {
            neighbor->SetLocation(neighbor->GetX(), neighbor->GetTowardBar());
            neighbor->SetActivated(true);
        }
        // also if we were pushing any FromNeighbors, they need to go back up
        for (auto &neighbor : mGrabbedBead->GetFromNeighbors())
        {
            if (neighbor->GetActivated())
            {
                neighbor->SetLocation(neighbor->GetX(), neighbor->GetTowardBar());
            }
        }
    }

    else
    {
        // farther from bar, snap away from it for us and all neighbors
        mGrabbedBead->SetLocation(x, mGrabbedBead->GetFromBar());
        mGrabbedBead->SetActivated(false);
        for (auto &neighbor: mGrabbedBead->GetFromNeighbors())
        {
            neighbor->SetLocation(neighbor->GetX(), neighbor->GetFromBar());
            neighbor->SetActivated(false);
        }
        // also if we were pushing any TowardNeighbors, they need to come back down
        for (auto &neighbor: mGrabbedBead->GetTowardNeighbors())
        {
            if (!neighbor->GetActivated())
            {
                neighbor->SetLocation(neighbor->GetX(), neighbor->GetFromBar());
            }
        }
    }
}
