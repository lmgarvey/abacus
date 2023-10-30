/**
 * @file AbacusApp.cpp
 * @author L.M. Garvey
 *
 * Main application class file for AbacusApp
 *
 * created october 2023
 * updated october 2023
 */

#include "pch.h"

#include "AbacusApp.h"
#include <MainFrame.h>

/**
 * Initialize the application
 * @return
 */
bool AbacusApp::OnInit()
{
    if (!wxApp::OnInit())
    {
        return false;
    }

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}

