/**
 * @file Abacus.cpp
 * @author L.M. Garvey
 *
 * Our main aquarium class
 *
 * created october 2023
 * updated october 2023
 */

#include "pch.h"

#include "Abacus.h"
#include "EarthBead.h"
#include "HeavenlyBead.h"

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
    for (int x : x_values)
    {
        x_place++;

        int bead_value = 1;
        for (int y : y_values)
        {
            std::shared_ptr<Bead> bead = std::make_shared<EarthBead>(this);
            bead->SetLocation(x, y);

            // 1's bead ranges from 300 (lower) to 220 (upper)
            // so beads range from y (lower) to y - 80 (upper)
            bead->SetUpperLower(y-80, y);
            bead->SetValue(bead_value);

            // 100s, 100.000s, ... place, tell bead it is a Location Bead
            if (x_place % 3 == 0 && bead_value == 1)
            {
                bead->SetLocation();
            }

            bead_value++;

            mEarthBeads.push_back(bead);
            mBeads.push_back(bead);
        }
    }

    // heavenly beads
    for (int x : x_values)
    {
        int y = 100;
        std::shared_ptr<Bead> bead = std::make_shared<HeavenlyBead>(this);
        bead->SetLocation(x, y);

        // heavenly bar at 220, so bead ranges from 100 (upper) to 220 (lower)
        // drawing at 220 puts the top-left in line with the bar, move back up [height]
        bead->SetUpperLower(100, y + 120 - bead->GetHeight());
        bead->SetValue(5);

        mHeavenlyBeads.push_back(bead);
        mBeads.push_back(bead);
    }
}

/**
 * Draw the abacus frame and column lines
 * calls OnDraw function for each bead in mBeads
 * @param dc The device context to draw on
 */
void Abacus::OnDraw(wxDC *dc)
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
    dc->DrawText(L"integer value: ", 100, 600);

    for (const auto& bead : mBeads)
    {
        bead->Draw(dc);
    }

}

/**
 * Test an x,y click location to see if we clicked a bead
 * @param x X location in pixels
 * @param y Y location in pixels
 * @return Pointer to bead we clicked, else nullptr
 */
std::shared_ptr<Bead> Abacus::HitTest(int x, int y)
{
    for (const auto& bead : mBeads)
    {
        if (bead->HitTest(x, y))
        {
            return bead;
        }
    }

    return nullptr;
}
