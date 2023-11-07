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
 * Sets up the initial beads and gets them into mBeads
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
}

/**
 * Draws the frame and columns of the abacus (unchanging)
 * @param dc the device context to draw on
 */
void Abacus::OnDrawFrame(wxDC *dc)
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

    // LITE display
    wxFont font(wxSize(10, 22),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(wxColour(0, 0, 0));
    dc->DrawText(L"integer value: \t\t", 100, 600);
}

/**
 * Draws the integer value (LITE) display for the abacus
 * @param dc The device context to draw on
 */
void Abacus::OnDrawLITEDisplay(wxDC *dc)
{
    // building the string backwards, from 1's place to 100..'s place
    std::string original;
    int column_total = 0;
    int j = 0;
    for (int i = 0; i < mEarthBeads.size(); i++)
    {
        const auto bead = mEarthBeads.at(i);
        if (bead->GetActivated())
        {
            column_total += bead->GetBaseValue();
        }

        // starting a new column
        if ((i+1) % 4 == 0 && i != 0)
        {
            auto heavBead = mHeavenlyBeads.at(j);
            if (heavBead->GetActivated())
            {
                column_total += heavBead->GetBaseValue();
            }
            original += std::to_string(column_total);
            column_total = 0;
            j++;
        }
    }
    std::reverse(original.begin(), original.end());

    // put in spacers, 100 000 000 is easier to look at than 100000000
    // ^^ spacer after i=2, i=5, up to pos 8
    std::string displayValue;
    for (int i = 0; i < original.size(); i++)
    {
        displayValue += original.at(i);
        if ((original.size() - 1 - i) % 3 == 0)
        {
            displayValue += " ";
        }
    }

    dc->DrawText(displayValue, 250, 600);
}

/**
 * Draw the abacus and its beads
 * calls OnDrawFrame for the frame and columns, which don't change
 * calls OnDrawLITEDisplay for the integer value display
 * calls OnDraw function for each bead in mEarthBeads and mHeavenlyBeads
 * @param dc The device context to draw on
 */
void Abacus::OnDraw(wxDC *dc)
{
    OnDrawFrame(dc);

    OnDrawLITEDisplay(dc);

    for (const auto& bead : mEarthBeads)
    {
        bead->Draw(dc);
    }
    for (const auto& bead : mHeavenlyBeads)
    {
        bead->Draw(dc);
    }

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
 * Test an x,y click location to see if we clicked a bead or RESET
 * @param x X location in pixels
 * @param y Y location in pixels
 * @return Pointer to bead we clicked, else nullptr
 */
std::shared_ptr<Bead> Abacus::HitTest(int x, int y)
{
    // first check if we hit the reset button
    if (x >= mResetX && x <= mResetX + mResetWidth && y >= mResetY && y <= mResetY + mResetHeight)
    {
        mReset = true;
        Refresh();
        return nullptr;
    }

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
 * Reset all beads on the abacus to be inactivated
 */
void Abacus::ResetBeads()
{
    for (auto &bead: mEarthBeads)
    {
        bead->SetActivated(false);
        bead->SetLocation(bead->GetX(), bead->GetFromBar());
    }
    for (auto &bead: mHeavenlyBeads)
    {
        bead->SetActivated(false);
        bead->SetLocation(bead->GetX(), bead->GetFromBar());
    }
}
