# abacus
Program for an interactable abacus

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



