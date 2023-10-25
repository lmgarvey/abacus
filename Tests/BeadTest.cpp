/**
 * @file BeadTest.cpp
 * @author L.M. Garvey
 *
 * Test file for testing the beads
 *
 * created october 2023
 * updated october 2023
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Bead.h>
#include <Abacus.h>

/// Mock class for testing the class bead
class BeadMock : public Bead
{
public:
    BeadMock(Abacus *abacus) : Bead(abacus) {}
};

TEST(BeadTest, Construct)
{
    Abacus abacus;
    BeadMock bead(&abacus);
}

TEST(BeadTest, GettersSetters)
{
    Abacus abacus;
    BeadMock bead(&abacus);

    // initial values
    ASSERT_EQ(0, bead.GetX());
    ASSERT_EQ(0, bead.GetY());

    // different values
    bead.SetLocation(735, 682);
    ASSERT_EQ(735, bead.GetX());
    ASSERT_EQ(682, bead.GetY());

    // new bead initial values
    BeadMock bead2(&abacus);
    ASSERT_EQ(0, bead2.GetX());
    ASSERT_EQ(0, bead2.GetY());

    // new bead different values
    bead2.SetLocation(500, 11);
    ASSERT_EQ(500, bead2.GetX());
    ASSERT_EQ(11, bead2.GetY());

    // original bead unchanged
    ASSERT_EQ(735, bead.GetX());
    ASSERT_EQ(682, bead.GetY());
}