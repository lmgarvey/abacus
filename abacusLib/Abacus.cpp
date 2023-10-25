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

/**
 * Draw the abacus
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

    // beads, TK will likely move once interactive
    wxBrush whiteBrush(*wxWHITE_BRUSH);
    dc->SetBrush(whiteBrush);

    // 1s column
    dc->DrawEllipse(875, 450, 60, 50);
    dc->DrawEllipse(875, 400, 60, 50);
    dc->DrawEllipse(875, 350, 60, 50);
    dc->DrawEllipse(875, 300, 60, 50);
    dc->DrawEllipse(875, 100, 60, 50);   // heavenly bead

    // 10s column
    dc->DrawEllipse(775, 450, 60, 50);
    dc->DrawEllipse(775, 400, 60, 50);
    dc->DrawEllipse(775, 350, 60, 50);
    dc->DrawEllipse(775, 300, 60, 50);
    dc->DrawEllipse(775, 100, 60, 50);   // heavenly bead

    // 100s column
    dc->DrawEllipse(675, 450, 60, 50);
    dc->DrawEllipse(675, 400, 60, 50);
    dc->DrawEllipse(675, 350, 60, 50);
    dc->DrawEllipse(675, 300, 60, 50);
    dc->DrawEllipse(675, 100, 60, 50);   // heavenly bead
}
