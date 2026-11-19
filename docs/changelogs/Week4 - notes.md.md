# Week 4 Notes

## Week focus

- Theme this week: endings and honesty. Give the game a win condition, then make every comment and doc tell the truth about what shipped. Feature freeze: no new mechanics.

## New feature: win condition

- Survive 20 days and rescue arrives at dawn on day 21.
- CheckWinCondition() runs at the end of NextDay(), before the arrival check, so no new survivors join after the rescue.
- Reuses the mGameOver flag on purpose: the flag means "the game ends now," and the ending message says which ending you got.
- Why 20 days: the horde grows by 2 every night, so day 20 sends 40-41 zombies. The ending lands right as any strategy starts to break, not after.

## Balance: full playthrough

- Ran a complete 20-day game: rescued at dawn of day 21 with 3 survivors left, 7 died on day 20, and the barricade hit zero several times.
- Kill switch check from Week 3: the run had deaths AND a broken barricade, so the switch did not fire. Starting materials stay at 10. Tuning stands.

## Balance: scripted strategy runs

- Verified the final build with scripted playtests a barricade-focused strategy rescued 8 of 11, a balanced strategy wiped on day 18, and a random strategy wiped on day 17. 
- My human win (3 left) sits below optimal scripted play. That is the target: winnable, not free.
- Finding: the barricade is the dominant strategy by a wide margin.

|   |   |   |   |   |   |   |   |
|---|---|---|---|---|---|---|---|
|Strategy|Outcome|Final day|Survivors|Deaths|Builds|Days barricade at 0|Hungry days|
|Turtle|RESCUED|20|8 rescued|3|104|13|0|
|Balanced|GAME OVER|18|0 (wiped)|10|18|14|1|
|ChaosGremlin|GAME OVER|17|0 (wiped)|11|35|13|5|

Kill-switch check (pre-committed): Turtle run had 3 deaths and barricade hit 0 on 13 of 20 days -> switch does NOT trigger. Starting materials stay at 10.

Baseline comparison (5-run set, same strategies):

- Turtle: won then (6 of 10 rescued, 97 builds); wins now (8 of 11 rescued, 104 builds). Same verdict.
- Balanced: wiped day 16 then, day 18 now. Same failure mode (under-built barricade).
- ChaosGremlin: wiped day 18 then, day 17 now. Same failure mode.

## Refactoring: comments and docs 

- Instructor feedback last week was doc drift, so I fixed it forward. Game.h's arrival comment said "roster cap 6" changed to 11 . The mGameOver comment said "flips when the last survivor dies" (the flag also means rescued now). CheckNewArrival's own comment said cap 10 while the code below it said 11.
- Roster cap reconciled to 11 everywhere: 3 starting survivors + an 8-name arrival pool = 11, so nobody in the pool gets locked out. Milestone3.md updated to match.
- Rule I am keeping: a comment that disagrees with its code is a bug.

## Usability: tell the player the goal

- The game never told the player what the win condition was. The opening now prints "Survive 20 days. Rescue arrives at dawn on day 21." and the day banner reads "Day X of 20".

## Bugs / fixes

- No new runtime bugs this week. This week's bugs were documentation bugs: stale comments that described code I no longer ship.
