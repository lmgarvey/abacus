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

    /// how far we've moved the mouse for dragging vs clicking
    int mDelta = 10;

    /// original position from which to grab delta
    int mClickedY;

    /// previous mouse position, for tracking if we're moving a bead toward or away from bar
    int mPreviousMouseY;

    /// the bead we are currently dragging
    std::shared_ptr<Bead> mGrabbedBead;

    void OnPaint(wxPaintEvent& event);

public:
    void Initialize(wxFrame* parent);

    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);

    void UpdateLITEValueDragged();
    void UpdateLITEValueClicked();

    int HandleActivation();
    int HandleDeactivation();



};


#endif //ABACUS_ABACUSVIEW_H
