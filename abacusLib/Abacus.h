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
protected:
    std::vector<std::shared_ptr<Bead>> mEarthBeads;       ///< earth beads
    std::vector<std::shared_ptr<Bead>> mHeavenlyBeads;    ///< heavenly beads

    std::string mDisplayValue = "0";      ///< the LITE value to display below the abacus

private:
    void SetUpBeads();

    // for the reset button
    bool mReset = false;    ///< whether the reset button was clicked
    int mResetX = 60;       ///< x-coord of top left corner of reset button
    int mResetY = 65;       ///< y-coord of top left corner of reset button
    int mResetWidth = 50;   ///< width of reset button
    int mResetHeight = 30;  ///< height of reset button when not clicked

    wxCheckBox* mLITECheckBox;  ///< checkbox for whether to draw the LITE display
    wxCheckBox* mGuideCheckBox; ///< checkbox for whether to draw the guide

    // {booleans for all earth beads, booleans for all heavenly beads}
    std::vector<std::pair<std::vector<bool>, std::vector<bool>>> mPrevBeads;     ///< for saving the previous state of the abacus
    std::vector<std::pair<std::vector<bool>, std::vector<bool>>> mNextBeads;     ///< for saving the next state of the abacus

    bool mSaving = false;        ///< whether the 'save' button is being clicked
    bool mFreezing = false;      ///< whether the 'freeze' button has been clicked
    bool mGoBack = false;        ///< whether the 'go back' button is being clicked
    bool mGoForth = false;       ///< whether the 'go forth' button is being clicked


public:
    Abacus();

    void OnDraw(wxDC *dc);
    static void DrawFrame(wxDC *dc);
    void DrawLITEDisplay(wxDC *dc);
    void DrawResetButton(wxDC *dc) const;
    static void DrawGuide(wxDC *dc);
    void DrawGreenButtons(wxDC *dc) const;


    std::shared_ptr<Bead> HitTest(int x, int y);
    bool NonBeadHitTest(int x, int y);


    [[nodiscard]] bool GetReset() const { return mReset; }    ///< @return whether the reset button is clicked
    void ResetBeads();

    [[nodiscard]] bool GetSaving() const { return mSaving; }      ///< @return whether we are clicking the 'save' button
    void SaveState(bool prev);

    [[nodiscard]] bool GetGoingBack() const { return mGoBack; }  ///< @return whether we are clicking the 'go back' button

    [[nodiscard]] bool GetGoingForth() const { return mGoForth; }  ///< @return whether we are clicking the 'go forth' button

    void GoToState(bool prev);

    /// @param checkbox was constructed in the view, save it to the member variable
    void AssignLITECheckBox(wxCheckBox *checkbox) { mLITECheckBox = checkbox; }

    /// @param checkbox was constructed in the view, save it to the member variable
    void AssignGuideCheckBox(wxCheckBox *checkbox) { mGuideCheckBox = checkbox; }

};


#endif //ABACUS_ABACUS_H
