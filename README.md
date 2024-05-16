# abacus
Program for an interactable abacus - Now playable!! Download the `abacus.exe` file to give it a test drive (you might get a warning from Windows - if you click 'More info' you should be able to run it)

![Image of the abacus program. There are two brown horizontal bars forming the frame.
There are ten columns, each with four beads on the bottom and one on top. Most of the beads are white. Three beads in the lower section are red.
A black bar separates the top from the bottom. There is a yellow rectangle at the top left.
The words 'integer value' appear below the abacus, followed by a number corresponding to the positions of the beads.
Below that is a checked box labeled 'Show integer display.'
Below that is a checked box labeled 'Show guide.' There are numbers along the edge of the frame indicating bead values.
The background is light grey.](AbacusProgramImage.png)

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

- Abacus behavior
  - If beads are toward the horizontal "heavenly bar," they are considered activated. Each bead along the bottom section is called an "earth bead," and is worth 1 when moved *up* to the bar. Each bead along the top is a "heavenly bead," and is worth 5 when moved *down* to the bar.
  - When beads are moved appropriately, the LITE value display at the bottom will update to match them.
  - Red beads are marked to delineate 100's places.
  - The yellow button on the top left can be clicked to reset the abacus.
    - Doing so will reset all beads to inactivated, and reset the LITE value display to zeros.
- Bead behavior
  - Clicking a bead once will flip it from inactivated to activated, or vice versa. If there are other beads between the clicked bead and its destination, they will be moved and (in)activated as well.
  - Clicking and dragging a bead will "push" any beads that are "in the way."
    - Releasing a bead more than halfway along the column from where it began will snap it (and any pushed beads) to the opposite status.
    - Releasing a bead less than halfway along its column from where it began will snap it (and any pushed beads) back to where they started, with their status unchanged.
    - Changing direction mid-drag will "snap" the pushed beads away from the clicked bead, and they will no longer be considered "pushed."
- Display behavior
  - The checkbox below the LITE value display can be clicked to select whether the LITE value is shown.
    - If checked, the LITE value display will appear as usual.
    - If unchecked, there will be no LITE value display, but the checkbox will remain.
    - The LITE value display persists when unseen. If the beads are moved when the LITE value display is hidden, and then the box is checked, the LITE value display will reappear with the correct number for the current state of the abacus.
    - This box defaults to being checked.
  - The checkbox beneath that can be clicked to select whether the optional guide is shown.
    - If checked, numbers will appear along the right edge to demonstrate the positions for a 1, 2, 3, 4, or 5x value. Numbers will appear along the bottom to denote the 1s, 10s, 100s, 100.000s, and 100.000.000s place.
    - If unchecked, these numbers will disappear.
    - This box defaults to being checked.
- Button behaviors
  - The 'save' button saves the current state of the beads on the abacus
  - The 'freeze' button stops the LITE display value from updating. The display is still visible, but does not change with the movement of beads. When clicked a second time, the LITE value display will update to match the current state of the abacus.
  - The 'go back' button changes the abacus to match the most recently 'save'd previous state
  - The 'go forth' button changes the abacus to match the most recent next state (the state that we left behind when clicking 'go back')



#### future

- [Here](https://trello.com/b/ed6DzdBR/aboncus) is a Trello board tracking components, including completed ones
- Also included in this repository is "ORIGINAL README.md," which contains my initial thoughts and intentions from before I began the program
- red light
  - None, we are functional!
- yellow light
  - None, we are functional!
- green light
  - int vs float option
    - Would change the display from integer LITE values to decimals and back
    - Functionality would be the same, but the manner of building the LITE display would differ slightly
    - green light<sup>2</sup>
      - Option to select where the decimal goes on the display
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


