/**
 * @file HeavenlyBead.h
 * @author L.M. Garvey
 *
 * Class for heavenly beads (topmost row)
 *
 * created october 2023
 * updated october 2023
 */

#ifndef ABACUS_HEAVENLYBEAD_H
#define ABACUS_HEAVENLYBEAD_H

#include "Bead.h"

/**
 * Class for heavenly beads
 */
class HeavenlyBead : public Bead
{
private:

public:
    /// default constructor (disabled)
    HeavenlyBead() = delete;

    /// copy constructor (disabled)
    HeavenlyBead(const HeavenlyBead &) = delete;

    /// assignment operator (disabled)
    void operator=(const HeavenlyBead &) = delete;

    explicit HeavenlyBead(Abacus *abacus);

};


#endif //ABACUS_HEAVENLYBEAD_H
