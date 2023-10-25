/**
 * @file Bead.cpp
 * @author L.M. Garvey
 *
 * Class for beads on the abacus
 *
 * created october 2023
 * updated october 2023
 */

#include "pch.h"

#include "Bead.h"
#include "Abacus.h"

/**
 * Constructor
 * @param abacus The abacus this bead is a member of
 */
Bead::Bead(Abacus *abacus) : mAbacus(abacus)
{

}

/**
 * Destructor
 */
Bead::~Bead()
{

}
