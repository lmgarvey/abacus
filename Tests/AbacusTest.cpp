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
    // getters
    [[nodiscard]] std::string GetDisplayValue() const { return mDisplayValue; }
    std::vector<std::shared_ptr<Bead>> GetEarthBeads() { return mEarthBeads; }
    std::vector<std::shared_ptr<Bead>> GetHeavenlyBeads() { return mHeavenlyBeads; }

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

    [[nodiscard]] int64_t CalculateTotal() const
    {
        int64_t out = 0;
        for (const auto &bead : mEarthBeads)
        {
            if (bead->GetActivated())  { out += bead->GetBaseValue() * (int64_t)pow(10, bead->GetColPos()); }
        }
        for (const auto &bead: mHeavenlyBeads)
        {
            if (bead->GetActivated())  { out += bead->GetBaseValue() * (int64_t)pow(10, bead->GetColPos()); }
        }

        return out;
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

TEST(AbacusTest, LITEValue)
{
    AbacusMock abacus;

    // initial value should be zero
    ASSERT_TRUE(abacus.GetDisplayValue() == "0") <<
        L"Testing an initial display should be zero";


    // move only earth beads
    auto earthBeads = abacus.GetEarthBeads();
    std::vector<int> toActivate = {2, 5, 12, 27, 1, 18, 38, 7};
    for (const auto i : toActivate)
    {
        earthBeads.at(i)->SetActivated(true);
        for (auto &neighbor : earthBeads.at(i)->GetTowardNeighbors())
        {
            // have to also activate their neighbors
            neighbor->SetActivated(true);
        }
    }
    int64_t total = 3004031043;     // calculated offline
    ASSERT_EQ(abacus.CalculateTotal(), total) <<
        L"Testing random earth beads only";


    // resetting should put everything back to zero
    abacus.ResetBeads();
    ASSERT_EQ(abacus.CalculateTotal(), 0) <<
        L"Resetting should put the total back to zero";


    // move only heavenly beads
    auto heavenlyBeads = abacus.GetHeavenlyBeads();
    toActivate = {0, 7, 3, 9};
    for (const auto i : toActivate)
    {
        heavenlyBeads.at(i)->SetActivated(true);
    }
    total = 5050005005;
    ASSERT_EQ(abacus.CalculateTotal(), total) <<
        L"Testing random heavenly beads only";


    // resetting should put everything back to zero
    abacus.ResetBeads();
    ASSERT_EQ(abacus.CalculateTotal(), 0) <<
        L"Resetting should put the total back to zero";


    // move some earth beads AND heavenly beads
    toActivate = {21, 18, 11, 0, 8, 33, 39, 27, 15, 30};
    for (const auto i : toActivate)
    {
        earthBeads.at(i)->SetActivated(true);
        for (auto &neighbor : earthBeads.at(i)->GetTowardNeighbors())
        {
            // have to also activate their neighbors
            neighbor->SetActivated(true);
        }
    }
    toActivate = {3, 1, 8, 5, 9};
    for (const auto i : toActivate)
    {
        heavenlyBeads.at(i)->SetActivated(true);
    }
    total = 9734739451;
    ASSERT_EQ(abacus.CalculateTotal(), total) <<
        "Testing both earth and heaven beads";


    // manually deactivate some beads without resetting the whole board
    // including some already-deactivated beads
    toActivate = {38, 13, 31, 24, 2, 36};
    for (const auto i : toActivate)
    {
        earthBeads.at(i)->SetActivated(false);
        for (auto &neighbor : earthBeads.at(i)->GetFromNeighbors())
        {
            neighbor->SetActivated(false);
        }
    }
    toActivate = {1, 9, 8};
    for (const auto i : toActivate)
    {
        heavenlyBeads.at(i)->SetActivated(false);
    }
    // activate some earth beads, just for fun
    toActivate = {7, 14, 22, 15};
    for (const auto i : toActivate)
    {
        earthBeads.at(i)->SetActivated(true);
        for (auto &neighbor : earthBeads.at(i)->GetTowardNeighbors())
        {
            neighbor->SetActivated(true);
        }
    }
    // and activate another heaven bead while we're at it
    heavenlyBeads.at(6)->SetActivated(true);
    heavenlyBeads.at(9)->SetActivated(true);
    total = 5235839441;
    ASSERT_EQ(abacus.CalculateTotal(), total) <<
        "Testing earth and heaven beads without resetting first";


    // resetting should put everything back to zero
    abacus.ResetBeads();
    ASSERT_EQ(abacus.CalculateTotal(), 0) <<
        L"Resetting should put the total back to zero";

}
