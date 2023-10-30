/**
 * @file EarthBead.h
 * @author L.M. Garvey
 *
 * Class for earth beads (lower 4)
 *
 * created october 2023
 * updated october 2023
 */

#ifndef ABACUS_EARTHBEAD_H
#define ABACUS_EARTHBEAD_H

#include "Bead.h"

/**
 * Class for earth beads
 */
class EarthBead : public Bead
{
private:

public:
    /// default constructor (disabled)
    EarthBead() = delete;

    /// copy constructor (disabled)
    EarthBead(const EarthBead &) = delete;

    /// assignment operator (disabled)
    void operator=(const EarthBead &) = delete;

    explicit EarthBead(Abacus *abacus);

};


#endif //ABACUS_EARTHBEAD_H
