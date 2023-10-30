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
    explicit Bead(Abacus *abacus);

private:
    /// the abacus this bead is contained in
    Abacus *mAbacus;

protected:
    // bead's location on the abacus
    int mX = 0;      ///< x location for top-left of bead
    int mY = 0;      ///< y location for top-left of bead

    // farthest bead can go vertically (mUpperY < mLowerY)
    int mUpperY = 0;    ///< bead can't go any higher on screen than this
    int mLowerY = 0;    ///< bead can't go any lower on screen than this

    // bead's size
    const int mWidth = 60;      ///< width of every bead
    const int mHeight = 50;     ///< height of every bead

    /// bead is toward heavenly bar (counted) if true
    bool mActivated = false;

    /// how much this bead counts for
    int mValue = 0;

    /// whether this bead should be painted red
    bool mLocationBead = false;

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
    [[nodiscard]] int GetUpperY() const { return mUpperY; }     ///< @return highest position bead can go
    [[nodiscard]] int GetLowerY() const { return mLowerY; }     ///< @return lowest position bead can go

    /// Set @param upper and @param lower to be vertical limits for this bead
    void SetUpperLower(int upper, int lower) { mUpperY = upper; mLowerY = lower; }

    [[nodiscard]] int GetWidth() const { return mWidth; }       ///< @return bead's width
    [[nodiscard]] int GetHeight() const { return mHeight; }     ///< @ return bead's height
    [[nodiscard]] bool GetActivated() const { return mActivated; }  ///<@return whether beat is activated
    void FlipActivated() { mActivated = !mActivated; }  ///< flip whether this bead is activated

    /// set item location at @param x, @param y location
    void SetLocation(int x, int y) { mX = x; mY = y; }

    void SetValue(int value) { mValue = value; }    ///< Set the value of this bead to @param value
    int GetValue() const { return mValue; }         ///< @return the value of this bead

    void SetLocation() { mLocationBead = true; }    ///< Tell this bead it is a location bead

    void Draw(wxDC *dc);

    [[nodiscard]] bool HitTest(int x, int y) const;

};


#endif //ABACUS_BEAD_H
