/**
 * @file AbacusView.h
 * @author L.M. Garvey
 *
 * View class for the Abacus
 *
 * created october 2023
 * updated november 2023
 */

#ifndef ABACUS_ABACUSVIEW_H
#define ABACUS_ABACUSVIEW_H

#include <wx/checkbox.h>

#include "Abacus.h"

/**
 * View class for the abacus
 */
class AbacusView : public wxWindow {
private:
    /// an object that describes our abacus
    Abacus mAbacus;

    /// how far we've moved the mouse for dragging vs clicking
    int mDelta = 5;

    /// original position from which to grab delta
    int mClickedY;

    /// previous mouse position, for tracking if we're moving a bead toward or away from bar
    int mPreviousMouseY;

    /// the bead we are currently dragging
    std::shared_ptr<Bead> mGrabbedBead;

    wxCheckBox mLITECheckBox;       ///< the check box for whether to draw the LITE display
    wxCheckBox mGuideCheckBox;      ///< the check box for whether to show the use guide

    void OnPaint(wxPaintEvent& event);

public:
    void Initialize(wxFrame* parent);

    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);

    void HandleSingleClick(wxMouseEvent &event);
    void HandleDragging(wxMouseEvent &event);
    void HandleReleasing(wxMouseEvent &event);

};


#endif //ABACUS_ABACUSVIEW_H
