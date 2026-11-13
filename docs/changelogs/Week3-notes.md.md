# Week 3 Notes

## Week focus

- Theme this week: refactoring and stability. "It works sometimes" to "it works reliably."
- Planning first: created 7 new GitHub Issues covering refactoring, features, a design decision, usability, and testing. All connected to the Project board.

## Refactoring: NextDay() split

- NextDay() had grown into one long function handling scavenging, eating, the attack, game over check, rest healing, and the summary.
- Refactored: eating logic moved to ResolveEating(), rest healing moved to ResolveResting(). NextDay() now reads as a short list of the day's phases.
- Pure refactor: no behavior changed. Verified by playing several days and comparing output before and after.

## New feature: horde scaling 

- Changed the horde formula from 1 + day/2 + random(0-2) to (day * 2) + random(0-1).
- Day 1 now has 2-3 zombies, growing by 2 every night.
- Reason: pairs with survivor arrivals so pressure keeps rising as the roster grows.

## New feature: survivor arrivals 

- Every 3rd day (3, 6, 9...) a new survivor joins the safehouse, with a welcome message.
- Roster capped at 6 so task assignment stays manageable.
- Learned: static local variables remember their value between function calls - used to cycle through the newcomer name pool (Rae, Kai, Juno).

## Design decisions

- Arrival pacing: every 3 days chosen over 2 or 4. With +2/night horde growth, every 2 days lets the roster outgrow the threat, every 5 days is a death spiral. Every 3 keeps the player almost keeping up.
- Barricade building and repair are ONE menu option, not two - a barricade is an HP pool, so building and repairing are the same action (spend materials, HP goes up). Splitting them would be a fake choice.
- Balance rule: if late game is unwinnable, adjust the rescue valve (arrival pacing), not the threat (horde size).

## Bugs / fixes

- nothing new yet this week

## New feature: barricade system

- Materials finally have a use: new main menu option "Build barricade" spends 3 materials for +2 barricade HP.
- Barricade HP lives in Safehouse (GetBarricade/AddBarricade, clamped at zero).
- Attack is now four phases: gun defense, hand-to-hand, barricade absorbs breakthrough zombies 1 HP each, then survivors take damage.
- Status screen and day summary now show all four resources: food, ammo, materials, barricade HP.
- Build/repair stayed one menu option on purpose - a barricade is an HP pool, so both actions are the same verb.

## Change: materials are guaranteed from scavenging

- Scavengers now always find 1-2 materials along with 1-4 food; ammo stays a 30% chance.
- Tradeoff: the barricade becomes a reliable wall instead of a scarce resource. If the 10-day playtest feels too easy, the knob to turn is the barricade COST, not the drop rate.
- Prompts updated so the Scavenge option lists materials too.

## Usability: prompts and summary

- Task prompts now list everything scavenging can bring back (food, materials, ammo chance).
- Day summary shows barricade HP alongside the other resources.

## New feature: horde scaling

...existing text...
- Tested: day 1 = 2-3 zombies, climbing by 2 each night as designed.

## New feature: survivor arrivals

...existing text...
- Tested: Rae arrived on day 3, Kai on day 6, and they can be assigned tasks immediately.