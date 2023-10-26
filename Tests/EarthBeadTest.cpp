/**
 * @file EarthBeadTest.cpp
 * @author L.M. Garvey
 *
 * Test file for testing the beads
 *
 * created october 2023
 * updated october 2023
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <EarthBead.h>
#include <Abacus.h>

TEST(EarthBeadTest, Construct)
{
    Abacus abacus;
    EarthBead bead(&abacus);
}
