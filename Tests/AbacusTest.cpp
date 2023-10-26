/**
 * @file AbacusTest.cpp
 * @author L.M. Garvey
 *
 * Test file for testing the Abacus
 *
 * created october 2023
 * updated october 2023
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Abacus.h>

using namespace std;

TEST(AbacusTest, Construct)
{
    Abacus abacus;
}

TEST(AbacusTest, HitTest)
{
    Abacus abacus;

    ASSERT_EQ(abacus.HitTest(0, 0), nullptr) <<
        L"Testing clicking at origin, no beads";

    // we know for sure beads are at these locations on launch (from Abacus::Abacus)
    // +(0..60) and +(0..50) moves us from the top left corner to the bottom right corner
    ASSERT_TRUE(abacus.HitTest(875 + 30, 450 + 25) != nullptr) <<
        L"Testing center of bead at 875,450 with integer value 4";
    ASSERT_TRUE(abacus.HitTest(675 + 30, 400 + 25) != nullptr) <<
        L"Testing right edge of bead at 675,400 with integer value 300";
    ASSERT_TRUE(abacus.HitTest(775 + 60, 100 + 25) != nullptr) <<
        L"Testing bottom edge of bead at 775,100 with integer value 50";
}
