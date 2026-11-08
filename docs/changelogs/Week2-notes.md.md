
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