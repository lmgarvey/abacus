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

public:
    Abacus();

    void OnDraw(wxDC *dc);
    static void OnDrawFrame(wxDC *dc);

    std::shared_ptr<Bead> HitTest(int x, int y);

};


#endif //ABACUS_ABACUS_H
