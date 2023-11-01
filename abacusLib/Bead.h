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
private:
    /// the abacus this bead is contained in
    Abacus *mAbacus;

    // bead's location on the abacus
    int mX = 0;      ///< x location for top-left of bead
    int mY = 0;      ///< y location for top-left of bead

    // farthest bead can go toward or away from the bar
    int mTowardBar = 0;  ///< bead can't go any closer to the heavenly bar than this
    int mFromBar = 0;    ///< bead can't go any farther from the heavenly bar than this

    // farthest the bead can go on the screen in general (mUpperY < mLowerY)
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
    bool mRedBead = false;

    /// whether this is a heavenly bead
    bool mIsHeav = false;

    /// beads between this one and the bar
    std::vector<std::shared_ptr<Bead>> mTowardBarNeighbors;

    /// beads below this one, away from the bar
    std::vector<std::shared_ptr<Bead>> mFromBarNeighbors;

public:
    explicit Bead(Abacus *abacus);

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
    [[nodiscard]] int GetTowardBar() const { return mTowardBar; }     ///< @return closest bead can get to bar
    [[nodiscard]] int GetFromBar() const { return mFromBar; }     ///< @return farthest bead can get from bar

    /// Set @param toward and @param from to be vertical limits for this bead wrt the heavenly bar
    void SetTowardFrom(int toward, int from) { mTowardBar = toward; mFromBar = from; }

    /// Set @param upper and @param lower to be absolute vertical limits, ignoring heavenly bar
    void SetUpperLower(int upper, int lower) { mUpperY = upper; mLowerY = lower; }

    [[nodiscard]] int GetWidth() const { return mWidth; }       ///< @return bead's width
    [[nodiscard]] int GetHeight() const { return mHeight; }     ///< @return bead's height
    [[nodiscard]] bool GetActivated() const { return mActivated; }  ///<@return whether beat is activated
    void SetActivated(bool activate) { mActivated = activate; }  ///< set bead's activation status to @param activate

    /**
     * Set location of bead
     * @param x X location to set
     * @param y Y location to set
     */
    void SetLocation(int x, int y) { mX = x; mY = y; }

    void SetValue(int value) { mValue = value; }    ///< Set the value of this bead to @param value
    [[nodiscard]] int GetValue() const { return mValue; }         ///< @return the value of this bead

    void SetIsRed() { mRedBead = true; }    ///< Tell this bead it is a location bead

    /**
     * Tell this bead about another bead between it and the bar
     * @param bead Bead we're telling it about
     */
    void AddTowardNeighbor(const std::shared_ptr<Bead>& bead) { mTowardBarNeighbors.push_back(bead); }
    std::vector<std::shared_ptr<Bead>> GetTowardNeighbors() { return mTowardBarNeighbors; }     /// @return the neighbors between this bead and the bar

    /**
     * Tell this bead about another bead below it, away from the bar
     * @param bead Bead we're telling it about
     */
    void AddFromNeighbor(const std::shared_ptr<Bead>& bead) { mFromBarNeighbors.push_back(bead); }
    std::vector<std::shared_ptr<Bead>> GetFromNeighbors() { return mFromBarNeighbors; }     /// @return the neighbors between this bead and the bar

    void Draw(wxDC *dc);

    [[nodiscard]] bool HitTest(int x, int y) const;

};


#endif //ABACUS_BEAD_H
