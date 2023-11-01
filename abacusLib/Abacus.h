/**
 * @file Abacus.h
 * @author L.M. Garvey
 *
 * Our main aquarium class
 *
 * created october 2023
 * updated october 2023
 */

#ifndef ABACUS_ABACUS_H
#define ABACUS_ABACUS_H

#include "Bead.h"

/**
 * Our main aquarium class
 */
class Abacus {
private:
    std::vector<std::shared_ptr<Bead>> mBeads;          ///< ALL beads

    /// the integer value to display for the abacus
    int mLITEValue = 0;

    void SetUpBeads();

public:
    Abacus();

    void OnDraw(wxDC *dc);

    std::shared_ptr<Bead> HitTest(int x, int y);

    /// Increments the LITE value by @param value
    void UpdateLITEValue(int value) { mLITEValue += value; }    /// update the LITE value with @param value

};


#endif //ABACUS_ABACUS_H
