/**
 * @file Abacus.h
 * @author L.M. Garvey
 *
 * Our main aquarium class
 *
 * created october 2023
 * updated november 2023
 */

#ifndef ABACUS_ABACUS_H
#define ABACUS_ABACUS_H

#include <utility>
#include <wx/checkbox.h>

#include "Bead.h"

/**
 * Our main aquarium class
 */
class Abacus {
private:
    std::vector<std::shared_ptr<Bead>> mEarthBeads;       ///< earth beads
    std::vector<std::shared_ptr<Bead>> mHeavenlyBeads;    ///< heavenly beads

    void SetUpBeads();

    // for the reset button
    bool mReset = false;    ///< whether the reset button was clicked
    int mResetX = 60;       ///< x-coord of top left corner of reset button
    int mResetY = 65;       ///< y-coord of top left corner of reset button
    int mResetWidth = 50;   ///< width of reset button
    int mResetHeight = 30;  ///< height of reset button when not clicked

    wxCheckBox* mLITECheckBox;  ///< checkbox for whether to draw the LITE display
    wxCheckBox* mGuideCheckBox; ///< checkbox for whether to draw the guide


public:
    Abacus();

    void OnDraw(wxDC *dc);
    static void DrawFrame(wxDC *dc);
    void DrawLITEDisplay(wxDC *dc) const;
    void DrawResetButton(wxDC *dc) const;
    static void DrawGuide(wxDC *dc);

    std::shared_ptr<Bead> HitTest(int x, int y);
    bool NonBeadHitTest(int x, int y);

    // for the reset button
    [[nodiscard]] bool GetReset() const { return mReset; }    ///< @return whether the reset button is clicked
    void ClearReset() { mReset = false; }   ///< un-click the reset button
    void ResetBeads();

    /// @param checkbox was constructed in the view, save it to the member variable
    void AssignLITECheckBox(wxCheckBox *checkbox) { mLITECheckBox = checkbox; }

    /// @param checkbox was constructed in the view, save it to the member variable
    void AssignGuideCheckBox(wxCheckBox *checkbox) { mGuideCheckBox = checkbox; }

};


#endif //ABACUS_ABACUS_H
