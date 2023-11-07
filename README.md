# abacus
Program for an interactable abacus

![Image of the abacus program. There are two brown horizontal bars forming the frame. There are ten columns, each with four beads on the bottom and one on top, running between the bars. Most of the beads are white. Three beads in the lower section are red, each with two white beads between them. A black bar separates the top from the bottom. The beads range in positions from against either of the brown bars to touching the black bar. There is a yellow rectangle at the top left. The words 'integer value' appear below the abacus, followed by a number corresponding to the positions of the beads. Below that is a checked box that reads 'Show integer display.' The background is light grey.](https://github.com/lmgarvey/abacus/assets/94126547/dc9ef2ee-e18d-486f-8949-bc70d2234832)

#### vocab
- TK
  - For finding later. Could mean something is broken, in progress, or I just know I'll want to come back to it.
- LITE
  - LITEral integer value. The base-10 representation of the state of the abacus.
- HEAV
  - As in HEAVenly beads. The bead display representation of the state of the abacus.
- red light
  - Features or behavior that are required for a bare-minimum functional program. If all "red light" components are not complete, the program is not complete.
  - Suppose you are making a 2d platformer. Red light features would be accepting input from the player, moving the character left and right, and interacting with key items.
  - This could also include program-breaking bugs. For example, if an input of "up up down down left right left right B B B" from the player crashes the game, then that is a red light bug.
- yellow light
  - Features or behavior that are not strictly necessary for a functional program, but would vastly improve it. If all "yellow light" components are not complete, the program can still be operational, but at a lower quality.
  - Again, consider a 2d platformer. Yellow light features would be things like shovels and jumping. Without these, yes, the character can move left and right on the screen, and could theoretically go places. Adding the yellow light abilities to dig and jump would massively open up the world to the player.
- green light
  - Features or behavior that are not at all required for a functional, quality program. If all "green light" components are not complete, the program might just be missing "that special something" that makes it unique.
  - These can be thought of as stretch goals. If you have the time, go for it, but they are not a priority.


#### current functionality

- Display behavior
  - If beads are toward the horizontal "heavenly bar," they are considered activated. Each bead along the bottom section is called an "earth bead," and is worth 1 when moved *up* to the bar. Each bead along the top is a "heavenly bead," and is worth 5 when moved *down* to the bar.
  - When beads are moved appropriately, the LITE value display at the bottom will update to match them.
  - Red beads are marked to delineate 100's places.
  - The yellow button on the top left can be clicked to reset the abacus.
    - Doing so will reset all beads to inactivated, and reset the LITE value display to zeros.
  - The checkbox below the LITE value display can be clicked to select whether the LITE value is shown.
    - If checked, the LITE value display will appear as usual.
    - If unchecked, there will be no LITE value display, but the checkbox will remain.
    - The LITE value display persists when unseen. If the beads are moved when the LITE value display is hidden, and then the box is checked, the LITE value display will reappear with the correct number for the current state of the abacus.
- Bead behavior
  - Clicking a bead once will flip it from inactivated to activated, or vice versa. If there are other beads between the clicked bead and its destination, they will be moved and (in)activated as well.
  - Clicking and dragging a bead will "push" any beads that are "in the way."
    - Releasing a bead more than halfway along the column from where it began will snap it (and any pushed beads) to the opposite status.
    - Releasing a bead less than halfway along its column from where it began will snap it (and any pushed beads) back to where they started, with their status unchanged.
    - Changing direction mid-drag will "snap" the pushed beads away from the clicked bead, and they will no longer be considered "pushed."


#### future

- [Here](https://trello.com/b/ed6DzdBR/aboncus) is a Trello board tracking past and future plans
- Also included in this repository is "ORIGINAL README.md," which contains my initial thoughts and intentions from before I began the program
- red light
  - None, we are functional!
- yellow light
  - Optional guide
    - A toggleable switch to label heavenly beads as worth 5, earth beads as worth 1, and each column's place value
- Tests for the LITE display updating correctly
  - Due to what I believe was integer overflow, the LITE value wrapped around to negative numbers when a display value greater than $2^{31}$ was on the abacus. As such, I built the display value by considering each column as a single 1-digit integer, and concatenating the string versions of them together into the final LITE value. I would like to add testing for this, because it is currently only my visual confirmation that the behavior was correct
  - Alternatively, it would also be nice to find a data type that can hold values above $2^{33}$, instead of doing the string construction runaround. An unsigned int is not enough, because that only allows the display to go up to $4.29$ billion, and not the $10$ billion $- 1$ that it should support
- green light
  - int vs float option
    - Would change the display from integer LITE values to decimals and back
    - Functionality would be the same, but the manner of building the LITE display would differ slightly
    - green light<sup>2</sup>
      - Option to select where the decimal goes on the display
  - "Freeze" option
    - Would freeze the LITE value as it is. Moving any beads on the abacus would not change the LITE value. Once "freeze" is deselected, the LITE value would update to match the abacus as it is now, after any changes were made
  - "Save" and "Return" options
    - Similar to "freeze," "save" would store the current state of the abacus and its LITE value. Moving beads would then resume as normal, with the LITE value updating accordingly. Clicking "return" would save the *new* current state and LITE, and switch the display back to the state and LITE that were saved
    - TK probably want `vector<vector<Bead>> mHistory`, and each vector is one instance of `mBeads`
      - Or possible a map of 'vector<Bead>, LITE_as_string` so they can be kept together
  - "History" option
    - An extension of the "save" and "return" options, this would ideally be a dropdown of (up to 10?) previously "save"d LITE values, with the most recent at the top. Behavior:
      - Select some "save"d LITE value
        - It should NOT be removed from the history
      - The current display/LITE combo gets saved automatically as the new most-recent value in the history
      - Update the display/LITE combo to be the selected one from the history
    - A "remove" button to delete a certain combo from the history?
  - Game mode
    - "Sandbox" mode
      - The current functionality. Play around with the display, watch the LITE value update, do what you will as you will
    - "Match display" mode
      - Display a random LITE value. The user has to move beads around so the display matches that value
      - The LITE value will not update to match the display during this time, since the point is to get to the given LITE value, not make your own
    - "Math" mode
        - Sub-modes would be addition, subtraction, multiplication, division
      - Show two LITE numbers. Depending on the mode, user has to move beads to get the correct answer for the relevant operation
      - Probably have the LITE value update as the beads move, or the user can just toggle to hide it if it's distracting
        - Could have an option for the LITE value to show the correct answer, so it becomes a combination of math and matching display
    - "Speed math" mode
      - Where the regular math mode just shows two numbers at a time, this would do multiple, perhaps ten to fifteen. Behavior on addition:
        - Display numbers $7$ and $8$
        - Once user moves beads to equivalent of $15$, display number $21$
        - Suppose user moves beads to equivalent of $34$ (incorrect), nothing else changes. Do not say 'incorrect,' do not display a new number
        - Once user moves beads to equivalent of $36$, display number $29$
        - ...
        - When user clicks 'done' (or when the supposed ten to fifteen have been run through), display a celebratory message and tell them how many numbers they added (or subtracted, multiplied, or divided)
      - green light<sup>2</sup>, but a 'hard' mode would be a nice touch
        - Modes are addition, subtraction, multiplication, division, addition *with negative numbers included*, possibly other ways to make it more interesting
        - This would also apply to the regular math mode


