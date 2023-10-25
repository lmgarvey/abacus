/**
 * @file AbacusView.h
 * @author L.M. Garvey
 *
 * View class for the Abacus
 *
 * created october 2023
 * updated october 2023
 */

#ifndef ABACUS_ABACUSVIEW_H
#define ABACUS_ABACUSVIEW_H

#include "Abacus.h"

/**
 * View class for the abacus
 */
class AbacusView : public wxWindow {
private:
    /// an object that describes our abacus
    Abacus mAbacus;

    void OnPaint(wxPaintEvent& event);

public:
    void Initialize(wxFrame* parent);

};


#endif //ABACUS_ABACUSVIEW_H
