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

- Every 3rd day (3, 6, 9...) a 2 survivor joins the safehouse, with a welcome message.
- Roster capped at 11 so task assignment stays manageable.
- Learned: static local variables remember their value between function calls - used to cycle through the newcomer name pool  Rae, Kai, Juno, Ash, Noa, Lex, Sky, Rue

## Design decisions

- Arrival pacing: every 3 days chosen over 2 or 4. With +2/night horde growth, every 2 days lets the roster outgrow the threat, every 5 days is a death spiral. Every 3 keeps the player almost keeping up.
- Barricade building and repair are ONE menu option, not two - a barricade is an HP pool, so building and repairing are the same action (spend materials, HP goes up). Splitting them would be a fake choice.
- Balance rule: if late game is unwinnable, adjust the rescue valve (arrival pacing), not the threat (horde size).

## Bugs / fixes

- nothing new yet this week

## New feature: barricade system
- Materials finally have a use: new main menu option "Build barricade" spends 2 materials for +2 barricade HP.
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
- Tested: day 1 = 2-3 zombies, climbing by 2 each night as designed.

## New feature: survivor arrivals   
- Tested: Rae arrived on day 3, Kai on day 6, and they can be assigned tasks immediately.
  
## Balance playthrough
- Ran a full 10-day playthrough. Finding: single arrivals every 3 days could not keep pace with the +2/night horde scaling; mid-game losses felt unavoidable rather than caused by bad decisions. This run motivated the tuning changes below.

## Healing capped at max health - instructor feedback fix
- Survivor::Heal had no upper limit, so resting could stack HP past 100 forever and the horde scaling stopped mattering. Added mMaxHealth (set from starting health in the constructor) and clamped Heal at it.

## Input validation replaced - instructor feedback fix
- Replaced cin.clear()/cin.ignore() in Helper::GetMenuChoice with the getline + stoi + try/catch pattern from the Day 3 and Day 5 lectures. Catches invalid_argument and out_of_range specifically, and uses the processedCharacters check so partial input like "12abc" is rejected. Tested with: potato, 12abc, a 20-digit number, 0, 6, and valid input.

## New arrivals join in pairs
- Arrivals changed from 1 to 2 survivors every 3 days. The roster-cap check moved inside the loop so a nearly-full roster takes only the survivors it has room for.

## Roster cap raised 6 -> 11, name pool expanded
- Pairs filled the old cap of 6 by day 6, which silently shut the arrival system off (day 6 added only 1, day 9 added none). Cap is now 11 and the name pool grew from 6 to 8 names so nobody repeats.

## Barricade economy tuning
- Build cost reduced 3 -> 2 materials, and the safehouse now starts with 10 materials. Deliberately generous: after the playthrough showed the game was too punishing, I overcorrected on purpose and will let the next 10-day run judge it. Kill switch agreed in advance: if that run has zero deaths AND an unbroken barricade, starting materials go to 0 - one knob per playtest.