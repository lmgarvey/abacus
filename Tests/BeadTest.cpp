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
#include <EarthBead.h>
#include <HeavenlyBead.h>

/// Mock class for testing the class bead
class BeadMock : public Bead
{
public:
    explicit BeadMock(Abacus *abacus) : Bead(abacus) {}

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

TEST(BeadTest, HitTest)
{
    // create a bead to test
    // earth and heavenly beads both use Bead::HitTest, just use an earthbead
    Abacus abacus;
    EarthBead bead(&abacus);

    // give it a location (top left)
    bead.SetLocation(100, 275);

    // center is at (left + radius_x, top + radius_y)
    // center should definitely be true
    ASSERT_TRUE(bead.HitTest(100 + bead.GetWidth()/2, 275 + bead.GetHeight()/2));

    // edges should be true
    ASSERT_TRUE(bead.HitTest(100 + bead.GetWidth()/2, 275));    // top middle
    ASSERT_TRUE(bead.HitTest(100 + bead.GetWidth()/2, 275 + bead.GetHeight()));    // bottom middle
    ASSERT_TRUE(bead.HitTest(100, 275 + bead.GetHeight()/2));     // left middle
    ASSERT_TRUE(bead.HitTest(100 + bead.GetWidth(), 275 + bead.GetHeight()/2));    // right edge

    // corners should be false
    ASSERT_FALSE(bead.HitTest(100, 275));    // top left
    ASSERT_FALSE(bead.HitTest(100 + bead.GetWidth(), 275));   // top right
    ASSERT_FALSE(bead.HitTest(100, 275 + bead.GetHeight()));    // bottom left
    ASSERT_FALSE(bead.HitTest(100 + bead.GetWidth(), 275 + bead.GetHeight()));   // bottom right

    // way outside the bead
    ASSERT_FALSE(bead.HitTest(50, 275));    // directly left
    ASSERT_FALSE(bead.HitTest(0, 0));       // origin
    ASSERT_FALSE(bead.HitTest(600, 200));   // to the right
}