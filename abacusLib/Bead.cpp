/**
 * @file Bead.cpp
 * @author L.M. Garvey
 *
 * Class for beads on the abacus
 *
 * created october 2023
 * updated october 2023
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
    wxBrush whiteBrush(*wxWHITE_BRUSH);
    dc->SetBrush(whiteBrush);
    dc->DrawEllipse(GetX(), GetY(), GetWidth(), GetHeight());
}

/**
 * Test to see if we hit this object with a mouse
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit, else false
 */
bool Bead::HitTest(int x, int y)
{
    double radius_x = GetWidth() / 2.0;
    double radius_y = GetHeight() / 2.0;

    double left = GetX();
    double top = GetY();
    double h = left + radius_x;
    double k = top + radius_y;

//    double h = GetX();   // x-coord center of ellipse
//    double k = GetY();   // y-coord center of ellipse

    double x_test = pow((x-h), 2) / pow((radius_x), 2);
    double y_test = pow((y-k), 2) / pow((radius_y), 2);

    double test_value = x_test + y_test;

    if (test_value <= 1)
        return true;
    return false;

}
