# abacus
Program for an interactable abacus

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
  - Optional LITE display
    - A toggleable switch to show or hide the LITE value display
  - Reset button
    - A button that, when clicked, sets the display and LITE value back to zero
  - Tests for the LITE display updating correctly
    - Due to what I believe was integer overflow, the LITE value wrapped around to negative numbers when a display value greater than $2^{31}$ was on the abacus. As such, I built the display value by considering each column as a single 1-digit integer, and concatenating the string versions of them together into the final LITE value. I would like to add testing for this, because it is currently only my visual confirmation that the behavior was correct
    - Alternatively, it would also be nice to find a data type that can hold values above $2^{33}$, instead of doing the string construction runaround. An unsigned int is not enough, because that only allows the display to go up to $4.29$ billion, and not the $10$ billion $- 1$ that it should support
- green light
  - int vs float option
    - Would change the display from integer LITE values to decimals and back
    - Functionality would be the same, but the manner of building the LITE display would differ slightly
    - green light$^2$
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
      - red$^2$ light, but a 'hard' mode would be a nice touch
        - Modes are addition, subtraction, multiplication, division, addition *with negative numbers included*, possibly other ways to make it more interesting
        - This would also apply to the regular math mode


this readme contains future plans and thoughts, and is not currently a comprehensive description of the abacus' functionality.


[80126739] = the literal integer number, ignoring heaven vs earth beads, "LITE"

[

(1,3)	# 1,000,000’s place

(0,0)

(0,1)

(0,2)

(1,1)	# 1000's place

(1,2)

(0,3)

(1,4)	# 1's place

]
= the same number, with each column represented as (number of heaven beads, number of earth beads)*, "HEAV". For personal use in english and pseudocode. The actual implementation will likely differ.

 ![visual abacus](https://github.com/lmgarvey/abacus/assets/94126547/5fa5d08f-00ba-4c8e-b4e2-bb8bf382e0a5)

= how it would visually display. Image taken at ![this](https://www.mathematik.uni-marburg.de/~thormae/lectures/ti1/code/abacus/soroban.html) website.


---

RED LIGHT FEATURES

- click a bead to move it up or down (opposite of current position)
  - at minimum needs to work clicking one at a time, not necessarily four at once
-	always display the current LITE value at the bottom, updates to match current HEAV display
-	RESET button to clear HEAV and LITE to zeroes

YELLOW LIGHT FEATURES

- Move multiple beads at once
  -	make (0,4) long way: click 1, then 2, then 3, then 4
  -	make (0,4) short way: click 4 will move 4, as well as the 1 2 and 3 above it at the same time
  -	so could also click 3 (moves 1 and 2 with it), then click 4 by itself

GREEN LIGHT FEATURES

- location beads, where top-most earth bead is a different color in the 1's and the 1000's column, so it's easy to see at a glance and track the digit places
-	would be nice to add decimals, maybe have an option to view an IntegerAbacus vs a FloatAbacus, can select either from the menu so you don't Have to practice decimals if you don't want to
-	FREEZE option
  -	Clicking FREEZE will “lock in” the LITE value at the bottom, and it won’t change when you move the beads around at all. Clicking UNFREEZE will update the LITE value to match the changed HEAV display
    -	Good for not getting confused doing addition
-	SAVE and RETURN options
  -	Saves HEAV state
    -	Probably also LITE value, but not visually saved or displayed
  -	You can then mess around with the HEAV display as much as you want, both HEAV and LITE will update as usual
  -	Clicking RETURN jumps you back to the last SAVEd state
    -	Both HEAV and LITE
    -	If no state was previously saved, RETURN should default to zeroes
  -	On clicking RETURN, the state you had immediately before clicking return is now saved
    -	Input [12345]
    -	SAVE
    -	Mess around
    -	Get to [34934]
    -	RETURN
      -	Even though SAVE is not explicitly called, [34934] is saved as the most recent
    -	Display updates to [12345]
    -	RETURN
    -	Display updates to [34934]
    -	Mess around
    -	Get to [09898]
    -	RETURN
    -	Display updates to [34934]
    -	RETURN
    -	Display updates to [09898]
    -	RETURN
    -	Display updates to [34934]
  -	RETURN vs GO BACK
    -	RETURN feels confusing, I think “GO BACK” and “GO FORWARD” might be better
-	HISTORY
  -	Every time you click SAVE, it saves that HEAV/LITE combo in a history
  -	Clicking the HISTORY option shows you previously saved numbers
    -	Maybe up to 10 most recent
    -	View only shows the LITE value
  -	Selecting one of the LITE values from the HISTORY updates the main display to have the selected HEAV/LITE combo
    -	Probably need to SAVE the combo you had right before selecting that one
    -	Selecting a combo bumps it to the top of the HISTORY
      -	Most recent combo is highest
      -	Could work well with the SAVE/RETURN options, where you’re just grabbing the most recent combo every time
-	Game mode
  -	Can have counting, addition, subtraction, multiplication, and division modes
    -	“activity-driven” modes
  -	And then a regular sandbox mode where you can do whatever you want
    -	This is where HISTORY, SAVE, RETURN, FREEZE would be used
    -	Probably won’t touch those in the activity-driven modes
  -	Counting
    -	Displays a fixed LITE value, and your goal is to make the HEAV display match that value
      -	Possibly in a fixed amount of time, but timers would be like a double-red light
    -	Once your HEAV is correct, display a “yeehaw you did it!”, give it a second, then display a new LITE value to try to match



