/**
 * @file Abacus.cpp
 * @author L.M. Garvey
 *
 * Our main aquarium class
 *
 * created october 2023
 * updated november 2023
 */

#include "pch.h"

#include "Abacus.h"

/**
 * Constructor
 */
Abacus::Abacus()
{
    SetUpBeads();
}

/**
 * Sets up the initial beads, puts them into mEarthBeads and mHeavenlyBeads
 */
void Abacus::SetUpBeads()
{
    // for determining where to place the beads
    const std::vector<int> x_values = {975, 875, 775, 675, 575, 475, 375, 275, 175, 75};
    const std::vector<int> y_values = {300, 350, 400, 450};

    // earth beads
    int x_place = 0;
    int max_j = 4;
    int col_pos = -1;
    for (int x : x_values)
    {
        col_pos++;
        for (int y : y_values)
        {
            std::shared_ptr<Bead> bead = std::make_shared<Bead>(this);
            bead->SetLocation(x, y);

            // (for earthly) higher on screen --> toward bar, lower on screen --> away from bar
            bead->SetTowardFrom(y-80, y);
            bead->SetUpperLower(y-80, y);

            // for pow(10, col_pos) in getting this bead's value
            bead->SetColPos(col_pos);

            // 100s, 100.000s, ... place, tell bead it is a Location Bead
            if ((x == 175 || x == 475 || x == 775) && y == 300)
            {
                bead->SetIsRed();
            }

            mEarthBeads.push_back(bead);
        }

        // tell each bead about its neighbors
        for (int i = 0; i < 4; i++)
        {
            int curr_index = i + 4 * x_place;
            std::shared_ptr<Bead> curr_bead = mEarthBeads.at(curr_index);

            // beads below us
            for (int j = curr_index + 1; j < max_j; j++)
            {
                std::shared_ptr<Bead> neighbor = mEarthBeads.at(j);
                curr_bead->AddFromNeighbor(neighbor);
            }

            // beads above us
            for (int j = 4 * x_place; j < curr_index; j++)
            {
                std::shared_ptr<Bead> neighbor = mEarthBeads.at(j);
                curr_bead->AddTowardNeighbor(neighbor);
            }
        }
        max_j += 4;

        x_place++;
    }

    // heavenly beads
    x_place = 0;
    col_pos = 0;
    for (int x : x_values)
    {
        int y = 100;

        std::shared_ptr<Bead> bead = std::make_shared<Bead>(this);
        bead->SetLocation(x, y);

        // (for heavenly) lower on screen --> toward bar, upper on screen --> away from bar
        bead->SetTowardFrom(y + 120 - bead->GetHeight(), 100);
        bead->SetUpperLower(100, y + 120 - bead->GetHeight());

        bead->SetBaseValue(5);
        bead->SetColPos(col_pos);

        col_pos++;
        x_place++;

        mHeavenlyBeads.push_back(bead);
    }

    // default previous state is zeroes, initialize it here
    SaveState(true);
}


/**
 * Draws the frame and columns of the abacus (unchanging)
 * @param dc the device context to draw on
 */
void Abacus::DrawFrame(wxDC *dc)
{
    // draw the frame
    wxPen brownPen(wxColour(125, 77, 32), 10);
    dc->SetPen(brownPen);
    dc->DrawLine(50, 100, 1050, 100);     // top bar
    dc->DrawLine(50, 500, 1050, 500);     // bottom bar

    wxPen blackPen(wxColour(0, 0, 0), 7);
    dc->SetPen(blackPen);
    dc->DrawLine(50, 220, 1050, 220);     // heavenly bar

    // columns
    wxPen thinBlackPen(wxColour(0, 0, 0), 2);
    dc->SetPen(thinBlackPen);
    const std::vector<int> x_positions = {1005, 905, 805, 705, 605, 505, 405, 305, 205, 105};
    for (int x : x_positions)
    {
        dc->DrawLine(x, 100, x, 500);
    }
}


/**
 * Draws the integer value (LITE) display for the abacus
 * @param dc The device context to draw on
 */
void Abacus::DrawLITEDisplay(wxDC *dc)
{
    wxFont font(wxSize(10, 22),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(wxColour(0, 0, 0));
    dc->DrawText(L"integer value: \t\t", 100, 600);

    if (mFreezing)
    {
        dc->DrawText(mDisplayValue, 250, 600);
        return;
    }

    int64_t total = 0;
    for (const auto &bead : mEarthBeads)
    {
        if (bead->GetActivated())
        {
            total += bead->GetBaseValue() * (int64_t)pow(10, bead->GetColPos());
        }
    }
    for (const auto &bead: mHeavenlyBeads)
    {
        if (bead->GetActivated())
        {
            total += bead->GetBaseValue() * (int64_t)pow(10, bead->GetColPos());
        }
    }

    // put in spacers, 100 000 000 is easier to look at than 100000000
    // ^^ spacer after i=2, i=5, up to pos 8
    std::string original = std::to_string(total);
    mDisplayValue = "";
    for (int i = 0; i < original.size(); i++)
    {
        mDisplayValue += original.at(i);
        if ((original.size() - 1 - i) % 3 == 0)
        {
            mDisplayValue += " ";
        }
    }

    dc->DrawText(mDisplayValue, 250, 600);
}


/**
 * Draw the reset button
 * @param dc The device context to draw on
 */
void Abacus::DrawResetButton(wxDC *dc) const
{
    wxBrush yellowBrush(*wxYELLOW_BRUSH);
    dc->SetBrush(yellowBrush);
    wxPen yellowPen(wxColour(245, 194, 66), 2);
    dc->SetPen(yellowPen);
    // draw the reset button clicked down
    if (mReset)
    {
        dc->DrawRectangle(mResetX, mResetY + mResetHeight / 2, mResetWidth, mResetHeight / 2);
    }
    // draw the reset button released
    else
    {
        dc->DrawRectangle(mResetX, mResetY, mResetWidth, mResetHeight);
    }
}


/**
 * Draw the guide
 * @param dc The device context to draw on
 */
void Abacus::DrawGuide(wxDC *dc)
{
    wxFont font(wxSize(10, 22),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(wxColour(70, 70, 70));
    dc->DrawText(L"1", 1000, 520);
    dc->DrawText(L"10", 892, 520);
    dc->DrawText(L"100", 785, 520);
    dc->DrawText(L"100,000", 465, 520);
    dc->DrawText(L"100,000,000", 145, 520);

    dc->DrawText(L"5", 1070, 120);
    dc->DrawText(L"1", 1070, 235);
    dc->DrawText(L"2", 1070, 285);
    dc->DrawText(L"3", 1070, 335);
    dc->DrawText(L"4", 1070, 385);
}


/**
 * Draws the save, return, back, and forth buttons
 * @param dc The device context to draw on
 */
void Abacus::DrawGreenButtons(wxDC *dc) const
{
    wxColour darkGreen = wxColour(130, 180, 130);
    wxColour lightGreen = wxColour(180, 230, 180);

    wxPen buttonPen(darkGreen, 2);
    dc->SetPen(buttonPen);
    wxBrush buttonBrush(lightGreen);
    dc->SetBrush(buttonBrush);

    if (mSaving)
    {
        dc->SetBrush(darkGreen);
    }
    dc->DrawRoundedRectangle(300, 650, 80, 30, 5);  // save button
    dc->SetBrush(lightGreen);

    if (mFreezing)
    {
        dc->SetBrush(darkGreen);
    }
    dc->DrawRoundedRectangle(300, 685, 80, 30, 5);  // freeze button
    dc->SetBrush(lightGreen);

    if (mGoBack)
    {
        dc->SetBrush(darkGreen);
    }
    dc->DrawRoundedRectangle(400, 650, 85, 30, 5);  // go back button
    dc->SetBrush(lightGreen);

    if (mGoForth)
    {
        dc->SetBrush(darkGreen);
    }
    dc->DrawRoundedRectangle(400, 685, 85, 30, 5);  // go back button
    dc->SetBrush(lightGreen);


    wxFont font(wxSize(8, 18),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(wxColour(70, 70, 70));

    dc->DrawText(L"Save", 318, 653);
    dc->DrawText(L"Freeze", 312, 689);
    dc->DrawText(L"Go Back", 407, 653);
    dc->DrawText(L"Go Forth", 407, 689);

}


/**
 * Draw the abacus and its beads
 * calls DrawFrame for the frame and columns, which don't change
 * calls DrawLITEDisplay for the integer value display
 * calls DrawGuide for the guide display
 * calls DrawResetButton for the reset button
 * calls DrawSaveReturn for those two buttons
 * calls Draw function for each bead in mEarthBeads and mHeavenlyBeads
 * @param dc The device context to draw on
 */
void Abacus::OnDraw(wxDC *dc)
{
    DrawFrame(dc);

    if (mLITECheckBox->GetValue())
    {
        DrawLITEDisplay(dc);
    }

    if (mGuideCheckBox->GetValue())
    {
        DrawGuide(dc);
    }

    DrawResetButton(dc);

    DrawGreenButtons(dc);

    for (const auto& bead : mEarthBeads)
    {
        bead->Draw(dc);
    }
    for (const auto& bead : mHeavenlyBeads)
    {
        bead->Draw(dc);
    }
}


/**
 * Test an x,y click location to see if we clicked a bead or the reset button
 * @param x X location in pixels
 * @param y Y location in pixels
 * @return Pointer to bead we clicked, else nullptr
 */
std::shared_ptr<Bead> Abacus::HitTest(int x, int y)
{
    if (NonBeadHitTest(x, y))
    {
        // we hit a button or checkbox, we can stop early!
        return nullptr;
    }

    // check if we hit a bead
    for (const auto& bead : mEarthBeads)
    {
        if (bead->HitTest(x, y))
        {
            return bead;
        }
    }
    for (const auto& bead : mHeavenlyBeads)
    {
        if (bead->HitTest(x, y))
        {
            return bead;
        }
    }

    return nullptr;
}


/**
 * For running a hit test on the non-bead components
 * @param x X coordinate to test
 * @param y Y coordinate to test
 * @return true if we hit a non-bead, else false
 */
bool Abacus::NonBeadHitTest(int x, int y)
{
    // did we hit the reset button?
    if (x >= mResetX && x <= mResetX + mResetWidth && y >= mResetY && y <= mResetY + mResetHeight)
    {
        mReset = true;
        return true;
    }

    // did we hit the LITE display toggle?
    int left, top, width, height;
    mLITECheckBox->GetPosition(&left, &top);
    mLITECheckBox->GetSize(&width, &height);
    if (x >= left && x <= left + width && y >= top && y <= top + height)
    {
        // clicked the checkbox, flip its value and update whether to draw LITE display
        mLITECheckBox->SetValue(!mLITECheckBox->GetValue());
        return true;
    }

    // did we hit the guide display toggle?
    mGuideCheckBox->GetPosition(&left, &top);
    mGuideCheckBox->GetSize(&width, &height);
    if (x >= left && x <= left + width && y >= top && y <= top + height)
    {
        // clicked the checkbox, flip its value and update whether to draw LITE display
        mGuideCheckBox->SetValue(!mGuideCheckBox->GetValue());
        return true;
    }

    // did we hit the save button?
    if (x >= 300 && x <= 300 + 80 && y >= 650 && y <= 650 + 30)
    {
        mSaving = true;
        return true;
    }

    // did we hit the freeze button?
    if (x >= 300 && x <= 300 + 80 && y >= 685 && y <= 685 + 30)
    {
        mFreezing = !mFreezing;
        return true;
    }

    // did we hit the go back button?
    if (x >= 400 && x <= 400 + 85 && y >= 650 && y <= 650 + 30)
    {
        mGoBack = true;
        return true;
    }

    // did we hit the go forth button?
    if (x >= 400 && x <= 400 + 85 && y >= 685 && y <= 685 + 30)
    {
        mGoForth = true;
        return true;
    }

    return false;
}


/**
 * Reset all beads on the abacus to be inactivated
 * Also saves the state right before resetting to mPrevBeads
 */
void Abacus::ResetBeads()
{
    std::vector<bool> earthBeadBools;
    std::vector<bool> heavenlyBeadBools;

    for (auto &bead: mEarthBeads)
    {
        // for mPrevBeads
        if (bead->GetActivated())
            earthBeadBools.push_back(true);
        else
            earthBeadBools.push_back(false);

        bead->SetActivated(false);
        bead->SetLocation(bead->GetX(), bead->GetFromBar());
    }
    for (auto &bead: mHeavenlyBeads)
    {
        // for mPrevBeads
        if (bead->GetActivated())
            heavenlyBeadBools.push_back(true);
        else
            heavenlyBeadBools.push_back(false);

        bead->SetActivated(false);
        bead->SetLocation(bead->GetX(), bead->GetFromBar());
    }

    mPrevBeads = std::make_pair(earthBeadBools, heavenlyBeadBools);
    mReset = false;
}


/**
 * Save the current state of the abacus
 * @param prev Whether we are saving into the prevBeads (true) or the nextBeads
 */
void Abacus::SaveState(bool prev)
{
    std::vector<bool> earthBeadBools;
    std::vector<bool> heavenlyBeadBools;

    for (const auto &bead : mEarthBeads)
    {
        if (bead->GetActivated())
            earthBeadBools.push_back(true);
        else
            earthBeadBools.push_back(false);
    }
    for (const auto &bead : mHeavenlyBeads)
    {
        if (bead->GetActivated())
            heavenlyBeadBools.push_back(true);
        else
            heavenlyBeadBools.push_back(false);
    }

    if (prev)
    {
        mPrevBeads = std::make_pair(earthBeadBools, heavenlyBeadBools);
    }
    else
    {
        mNextBeads = std::make_pair(earthBeadBools, heavenlyBeadBools);
    }
    mSaving = false;
}


/**
 * Return back to the previously saved state of the abacus
 */
void Abacus::GoToPrev()
{
    std::vector<bool> earthBeadBools = mPrevBeads.first;
    std::vector<bool> heavenlyBeadBools = mPrevBeads.second;

    // save Current State so we can go back and forth
    SaveState(false);

    for (int i = 0; i < earthBeadBools.size(); i++)
    {
        auto bead = mEarthBeads.at(i);
        if (earthBeadBools.at(i))
        {
            bead->SetActivated(true);
            bead->SetLocation(bead->GetX(), bead->GetTowardBar());
        }
        else
        {
            bead->SetActivated(false);
            bead->SetLocation(bead->GetX(), bead->GetFromBar());
        }
    }
    for (int i = 0; i < heavenlyBeadBools.size(); i++)
    {
        auto bead = mHeavenlyBeads.at(i);
        if (heavenlyBeadBools.at(i))
        {
            bead->SetActivated(true);
            bead->SetLocation(bead->GetX(), bead->GetTowardBar());
        }
        else
        {
            bead->SetActivated(false);
            bead->SetLocation(bead->GetX(), bead->GetFromBar());
        }
    }

    mGoBack = false;
}


/**
 * Go forth to next saved state in abacus
 */
void Abacus::GoToNext()
{
    std::vector<bool> earthBeadBools = mNextBeads.first;
    std::vector<bool> heavenlyBeadBools = mNextBeads.second;

    // save Current State so we can go back and forth
    SaveState(true);

    for (int i = 0; i < earthBeadBools.size(); i++)
    {
        auto bead = mEarthBeads.at(i);
        if (earthBeadBools.at(i))
        {
            bead->SetActivated(true);
            bead->SetLocation(bead->GetX(), bead->GetTowardBar());
        }
        else
        {
            bead->SetActivated(false);
            bead->SetLocation(bead->GetX(), bead->GetFromBar());
        }
    }
    for (int i = 0; i < heavenlyBeadBools.size(); i++)
    {
        auto bead = mHeavenlyBeads.at(i);
        if (heavenlyBeadBools.at(i))
        {
            bead->SetActivated(true);
            bead->SetLocation(bead->GetX(), bead->GetTowardBar());
        }
        else
        {
            bead->SetActivated(false);
            bead->SetLocation(bead->GetX(), bead->GetFromBar());
        }
    }

    mGoForth = false;
}
