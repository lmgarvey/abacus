/**
 * @file Bead.h
 * @author L.M. Garvey
 *
 * Class for beads on the abacus
 *
 * created october 2023
 * updated october 2023
 */

#ifndef ABACUS_BEAD_H
#define ABACUS_BEAD_H

class Abacus;

/**
 * Class for beads on the abacus
 */
class Bead {
protected:
    Bead(Abacus *abacus);

private:
    /// the abacus this bead is contained in
    Abacus *mAbacus;

    // bead's location on the abacus
    int mX = 0;      ///< x location for center of bead
    int mY = 0;      ///< y location for center of bead

public:
    virtual ~Bead();

    /// default constructor (disabled)
    Bead() = delete;

    /// copy constructor (disabled)
    Bead(const Bead &) = delete;

    /// assignment operator (disabled)
    void operator=(const Bead &) = delete;

    // getters and setters
    [[nodiscard]] int GetX() const { return mX; }  ///< @return X location in pixels
    [[nodiscard]] int GetY() const { return mY; }  ///< @return Y location in pixels

    /// set item location at @param x, @param y location
    void SetLocation(int x, int y) { mX = x; mY = y; }

};


#endif //ABACUS_BEAD_H
