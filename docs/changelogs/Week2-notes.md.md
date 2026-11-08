
# Week 2 Progress Notes

## Sunday–Monday (Week 1 wrap / Week 2 start)
- Wrapped Week 1: README stand-up added, PR dev → main merged and closed, Milestone 1 submitted
- Created docs/prototype.md — full design blueprint (classes, data structures, program flow, user interaction)
- Read the Objects & Pointers refresher; confirmed the project mostly uses stack objects on purpose
- Read the Usability & Accessibility research page; picked 2 usability improvements for this week
  (clearer task-assignment prompts + a day summary screen)
- Created Week 2 GitHub Issues (zombie attacks, defend/ammo, day summary, game over, usability pass)
  and connected them to the Project board

## Zombie attack system
- Implemented the Zombie class: horde size scales with the day counter (1-3 base + 1 per 2 days)
- Attack resolution: each defender repels up to 2 zombies at 1 ammo per repel;
  breakthrough zombies deal 5 damage to random living survivors
- Design decision: horde lives on the stack (only exists during nightly resolution) —
  no manual new/delete needed. Documented in prototype.md
- Design decision: damage hits random living survivors, not just defenders, so Rest isn't a free heal
- Safehouse gained ammo/materials getters and setters to support the attack mechanics
- Tested: no defenders = full breakthrough damage; with defenders = ammo spent, horde repelled

- Implemented game over condition: GetAliveCount() in Safehouse, mGameOver flag in Game,
  end screen prints days survived; loop exits cleanly
  
  ## Game over condition and end screen

- Added `GetAliveCount()` to Safehouse so Game can ask one question instead of looping the roster itself.
- Added `CheckGameOver()` to Game, called right after the nightly attack in NextDay(). If no survivors are alive it flips an mGameOver flag, prints a GAME OVER screen with the final day count, and the menu loop exits cleanly.
- Design note: on the game over day, rest healing, the day summary, and the day counter are all skipped - the GAME OVER screen is the ending.
- Bug found: LNK2019 unresolved external `Survivor::GetTaskName()`. The header declared the function but Survivor.cpp had no body for it. Linker errors mean "promised but never delivered" - different from IntelliSense E-codes. Fixed by writing the definition with a switch over the Task enum.
- Verified by playing with no defenders assigned: horde broke through each night, survivors died one by one, game ended on its own with the correct day count.

## Day summary screen

- Added `PrintDaySummary()` to Game, called at the end of NextDay() after rest healing and before the day counter advances.
- Prints one labeled block: survivors alive out of total, food/ammo/materials totals, and each survivor's HP with a (DEAD) marker.
- Usability goal: the player no longer scrolls back through scattered lines to figure out what happened that day.
- Note: it is not a const method because GetSurvivors() is not const - a const summary function would not compile.

## Usability pass

- Task assignment prompts now say what each task does and costs (Defend = 1 ammo per kill, 3 HP hand-to-hand; Rest = +5 HP).
- Verified menu input handling with bad inputs (letters, 0, out-of-range numbers) - Helper::GetMenuChoice re-asks without crashing.

## Code comments

- Added explanatory comments to all class files: Game.h/.cpp, Safehouse.h/.cpp, Survivor.h/.cpp, Zombie.h/.cpp.
- Comments explain WHY decisions were made (stack horde, pointer target list, no health cap), not just what each line does.
  
## Bugs / fixes[
- [Zombie.cpp: typo "Survior" (missing second v) in the defender-counting loop caused
  [E0020 "identifier is undefined" — fixed spelling to Survivor

- [Zombie.cpp: declared "int defender" but used "defenders" elsewhere, causing two more
  [E0020s plus an E0065 "expected a ;" as fallout — made the names match

- [Lesson reinforced: E-codes are IntelliSense; after fixing, Rebuild before trusting the Error List]
-
- [- E0135 "class Survivor has no member GetTaskName" at Safehouse.cpp when   wiring up the status-screen task display. Cause: the multi-file change needed three edits
-
- [(Survivor.h declaration, Survivor.cpp implementation, Safehouse.cpp call site) and
  [the .h declaration never got saved, so the compiler found the call but not the method.
-
-  [Fix: added `std::string GetTaskName() const;` to the public section of   Survivor.h,
   [saved, Rebuild. Lesson: with changes that span files, check every file got its
   [edit before trusting the Error List — and E-codes are IntelliSense, so Rebuild
   [before believing them.] 