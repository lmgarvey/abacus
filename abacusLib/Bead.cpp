/**
 * @file Bead.cpp
 * @author L.M. Garvey
 *
 * Class for beads on the abacus
 *
 * created october 2023
 * updated november 2023
 */

#include "pch.h"

#include "Bead.h"
#include "Abacus.h"

/**
 * Constructor
 * @param abacus The abacus this bead is a member of
 */
Bead::Bead(Abacus *abacus) : mAbacus(abacus)
{

}

/**
 * Destructor
 */
Bead::~Bead()
{

}

/**
 * Draw this earth bead
 * @param dc Device context to draw on
 */
void Bead::Draw(wxDC * dc)
{
    if (mRedBead)
    {
        dc->SetBrush(*wxRED_BRUSH);
    }
    else
    {
        dc->SetBrush(*wxWHITE_BRUSH);
    }

    if (GetY() <= mUpperY)
    {
        // too high on the screen
        mY = mUpperY;
    }
    else if (GetY() >= mLowerY)
    {
        // too low on the screen
        mY = mLowerY;
    }
    else
    {
        // we're good!
        mY = GetY();
    }
    wxPen blackPen(wxColour(0, 0, 0), 2);
    dc->SetPen(blackPen);
    dc->DrawEllipse(mX, mY, GetWidth(), GetHeight());

    // don't do dc->Clear(), we're still using the device context out in Abacus::OnDraw

}

/**
 * Test to see if we hit this object with a mouse
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit, else false
 */
bool Bead::HitTest(int x, int y) const
{
    double radius_x = GetWidth() / 2.0;
    double radius_y = GetHeight() / 2.0;

    double h = mX + radius_x;   // x-coord center of bead
    double k = mY + radius_y;   // y-coord center of bead

    // equation to check if point (x,y) is in the ellipse centered at (h,k)
    double x_test = pow((x-h), 2) / pow((radius_x), 2);
    double y_test = pow((y-k), 2) / pow((radius_y), 2);

    double test_value = x_test + y_test;

    if (test_value <= 1)
        return true;
    return false;

}
