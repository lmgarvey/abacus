# Git Commit Messages

Since I work locally in CLion, committing and pushing changes with messages can only be done with titles, and no description section.
This is visually messy to me when looking at my commit history, since it's difficult to see at a glance what a certain commit did - you have to expand the title just to see the full thing.

This document is intended to supplement those messages. It will include backdated commits from before its existence, and will list out future commits as well, in an effort to clarify changes as they happened.
It will be in order of most recent first, as is standard in the regular commit history.

For all commits after 9 November, the main bullet will match the title on git's commit message.


- Added LITE value testing
  - 9 November 2023
  - Added testing for moving beads and updating the LITE display value correctly
  - Again required use of the AbacusMock class for testing
    - Took only the relevant value calculation from Abacus::OnDraw to avoid needing an instantiation of a View and drawing
    - The actual logic of the calculation itself is unchanged in the mock class
  - Modified the corresponding yellow light section in README.md
- Updated Abacus testing
  - 9 November 2023
  - HitTest testing broke as a result of adding the checkboxes
    - Moved this testing into an AbacusMock class to account for it
  - Added testing for hitting the reset button
  - Bead testing was also broken as a result of removing the EarthBead and HeavenlyBead classes, removed those errors
- Improved LITE value display
  - 9 November 2023
  - Modified the LITE value display calculation to use int64_t to build the entire number *as a number*, rather than as a backwards string one column at a time
    - Updated the corresponding yellow light section in README.md
    - I would still like to add testing for this, but we are functional!
  - Cleaned up the functionality section of the README.md
- Added GitCommitMessages file
  - 9 November 2023
  - Also updated the program image in README.md to include the optional guide display
- Added optional guide
  - 7 November 2023
  - There is now a checkbox that can toggle a guide to indicate the value of each activated bead, and the place value of select columns
  - Modified the corresponding yellow light section in README.md
  - Cleaned up the hit testing to split the work between clicking beads versus non-bead item (reset button and checkboxes)
- Added program image
  - 7 November 2023
  - Added an image of the program running to README.md, with some of the beads activated and the integer value checkbox toggled
- Added LITE value display toggle
  - 7 November 2023
  - There is now a checkbox that can toggle whether the integer LITE value is displayed at the bottom
  - Modified the 'display' section of the README.md, and the corresponding yellow light section
  - Cleaned up some doxygen warnings
- Added reset button
  - 7 November 2023
  - There is now a yellow button on the top left. When clicked, all beads are set to inactivated, and the LITE value display is set to zero
- Modified README.md
  - 6 November 2023
  - Overhauled the README.md to reflect the current state of the program:
    - Vocabulary that is assumed knowledge for the program and repo
    - Current functionality of the working program
    - Future plans for the program, split into the traffic light system
  - Moved the original README.md into its own file, 'ORIGINAL README.md'
    - For a paper trail of how the initial plan for the program looked
- Fixed LITE value display
  - 4 November 2023
  - Display is now built one column integer at a time and added to a string to avoid integer overflow on last column
    - Completely removed previous calculation for this in AbacusView, now work happens in Abacus::OnDraw
    - AbacusView is now only responsible for setting activation status and location of beads, not the total value
  - Split mBeads into mEarthBeads and mHeavenlyBeads for ease of LITE value calculation
  - Refactored over-busy functions into helper functions for cleanliness
  - Added the doxygen file
- Fixed dragging beads
  - 2 November 2023
  - Dragging a bead now also moves its neighbors properly
  - Broke LITE value display, there is now integer overflow
    - This may have been an issue before that I had simply not noticed yet
- Clicking a bead moves its neighbors
  - 31 October 2023
  - Clicking a single bead also moves the beads between it and its destination
  - LITE value is updated accordingly
  - Deleted redundant EarthBead and HeavenlyBead files
  - Dragging a bead is not yet functional
- Heavenly beads are now counted correctly
  - 31 October 2023
  - They are now counted when they are activated (toward the bar), instead of when at their highest vertical position
    - Maximum vertical position is activation for earth beads, not heavenly
- Added LITE value display
  - 31 October 2023
  - There is now a number display below the abacus representing the LITE value of the state of the beads
  - It is not currently correct, as each bead's value is added together - the 2 and 3 bead both being activated displays as 5 instead of the appropriate 3
- Modified clicking and dragging
  - 30 October 2023
  - Beads no longer move outside their set region
    - Earth beads can only go as low as {the lower frame or the neighboring lower bead}, and as high as {the heavenly bar or the neighboring upper bead}
    - Heavenly beads can only go as low as the heavenly bar, and as high as the upper frame
  - On a single click, the bead's position flips
  - On dragging and releasing, the bead snaps either up or down - whichever is closer
  - This only works for individual beads - the clicked bead still overlaps with neighbors, as neighbors do not yet move with it
- Added clicking and dragging
  - Beads can be clicked and dragged around without leaving their respective column
  - No vertical limits on bead location yet
- Added bead hit tests
  - 25 October 2023
  - There is now functionality to tell when a bead has been clicked
  - Added derived EarthBead and HeavenlyBead classes, and their corresponding test files
- Draws frame and static beads
  - 25 October 2023
  - Simple frame of straight lines appears
  - Three columns of five beads each appears, but is not interactable yet
- Initial files
  - 18 October 2023
  - Added initial files that set up an application to open a blank white window with the title 'abacus'