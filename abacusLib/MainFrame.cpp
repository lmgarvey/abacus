/**
 * @file MainFrame.cpp
 * @author L.M. Garvey
 *
 * The top-level (main) frame of the application
 *
 * created october 2023
 * updated october 2023
 */

#include "pch.h"

#include "AbacusView.h"
#include "MainFrame.h"


/**
 * Initialize the MainFrame window
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"abacus",
           wxDefaultPosition, wxSize( 1250,800 ));

    // create a sizer to lay  out child windows vertically above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // create the view class object as a child of MainFrame
    auto abacusView = new AbacusView();
    abacusView->Initialize(this);

    // add it to the sizer
    sizer->Add(abacusView, 1, wxEXPAND | wxALL);

    // set the sizer for this frame
    SetSizer(sizer);

    // lay out (place) the child windows
    Layout();
}
