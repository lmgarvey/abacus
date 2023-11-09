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

class AbacusMock : public Abacus
{
public:
    /**
     * Mock hit test for beads, nearly identical to Abacus::HitTest
     *      Only skips seeing if we hit the checkboxes
     * @param x X location to check
     * @param y Y location to check
     * @return The clicked bead, else nullptr
     */
    std::shared_ptr<Bead> HitTestMock(int x, int y)
    {
        for (const auto& bead : mEarthBeads)
        {
            if (bead->HitTest(x, y)) { return bead; }
        }
        for (const auto& bead : mHeavenlyBeads)
        {
            if (bead->HitTest(x, y)) { return bead; }
        }

        return nullptr;
    }

    static bool HitResetMock(int x, int y)
    {
        if (x >= 60 && x <= 60 + 50 && y >= 65 && y <= 65 + 30) { return true; }
        return false;
    }
};

TEST(AbacusTest, Construct)
{
    Abacus abacus;
}

TEST(AbacusTest, HitTest)
{
    AbacusMock abacus;

    ASSERT_EQ(abacus.HitTestMock(0, 0), nullptr) <<
        L"Testing clicking at origin, no beads";

    // we know for sure beads are at these locations on launch (from Abacus::Abacus)
    // +(0..60) and +(0..50) moves us from the top left corner to the bottom right corner
    ASSERT_TRUE(abacus.HitTestMock(875 + 30, 450 + 25) != nullptr) <<
        L"Testing center of bead at 875,450 with integer value 4";
    ASSERT_TRUE(abacus.HitTestMock(675 + 30, 400 + 25) != nullptr) <<
        L"Testing right edge of bead at 675,400 with integer value 300";
    ASSERT_TRUE(abacus.HitTestMock(775 + 60, 100 + 25) != nullptr) <<
        L"Testing bottom edge of bead at 775,100 with integer value 50";

    // check we can hit the reset button
    ASSERT_TRUE(abacus.HitResetMock(60 + 25, 65)) <<
        L"Testing top middle of reset button";
    ASSERT_TRUE(abacus.HitResetMock(60, 65 + 30)) <<
        L"Testing bottom left corner of reset button";
    ASSERT_TRUE(abacus.HitResetMock(60 + 23, 65 + 17)) <<
        L"Testing somewhere in the middle of reset button";
    ASSERT_FALSE(abacus.HitResetMock(675 + 30, 400 + 25)) <<
        L"Testing clicking a bead when trying for the reset button";
    ASSERT_FALSE(abacus.HitResetMock(1023, 92)) <<
        L"Testing clicking somewhere random on the screen when trying for the reset button";
}

