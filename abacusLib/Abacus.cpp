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
    const std::vector<int> x_values = {875, 775, 675};
    const std::vector<int> y_values = {450, 400, 350, 300};

    // earth beads
    for (int i = 0; i < 3; i++)
    {
        int x = x_values.at(i);
        for (int j = 0; j < 4; j++)
        {
            std::shared_ptr<Bead> bead = std::make_shared<EarthBead>(this);
            int y = y_values.at(j);
            bead->SetLocation(x, y);
            mEarthBeads.push_back(bead);
            mBeads.push_back(bead);
        }
    }

    // heavenly beads
    for (int i = 0; i < 3; i++)
    {
        int x = x_values.at(i);
        int y = 100;
        std::shared_ptr<Bead> bead = std::make_shared<HeavenlyBead>(this);
        bead->SetLocation(x, y);
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
    dc->DrawLine(50, 100, 950, 100);     // top bar
    dc->DrawLine(50, 500, 950, 500);     // bottom bar

    wxPen blackPen(wxColour(0, 0, 0), 7);
    dc->SetPen(blackPen);
    dc->DrawLine(50, 220, 950, 220);     // heavenly bar

    // columns
    wxPen thinBlackPen(wxColour(0, 0, 0), 2);
    dc->SetPen(thinBlackPen);
    dc->DrawLine(905, 100, 905, 500);    // 1s
    dc->DrawLine(805, 100, 805, 500);    // 10s
    dc->DrawLine(705, 100, 705, 500);    // 100s

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
