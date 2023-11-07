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

public:
    Abacus();

    void OnDraw(wxDC *dc);
    static void OnDrawFrame(wxDC *dc);
    void OnDrawLITEDisplay(wxDC *dc);

    std::shared_ptr<Bead> HitTest(int x, int y);

    [[nodiscard]] bool GetReset() const { return mReset; }
    void ClearReset() { mReset = false; }
    void ResetBeads();

};


#endif //ABACUS_ABACUS_H
