/**
 * @file HeavenlyBeadTest.cpp
 * @author L.M. Garvey
 *
 * Test file for testing the beads
 *
 * created october 2023
 * updated october 2023
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <HeavenlyBead.h>
#include <Abacus.h>

TEST(HeavenlyBeadTest, Construct)
{
    Abacus abacus;
    HeavenlyBead bead(&abacus);
}
