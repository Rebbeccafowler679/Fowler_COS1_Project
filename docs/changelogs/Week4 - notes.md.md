# Week 4 Notes - Zombie Survival Sim

## Win condition added
The game could previously only be lost. Now surviving to the dawn of
day 21 triggers a rescue ending: CheckWinCondition() runs right after
the day counter increments, before CheckNewArrival(), so no survivor
joins after the rescue. It reuses the mGameOver flag - the flag just
means "the game ends now," and the screen says which ending you got.

## Documentation synced with final tuning values
Milestone docs described old values (1 arrival per 3 days, 3-material
barricade cost). Updated to match the shipped implementation: pair
arrivals, cost 2, 10 starting materials, roster cap 10, 8-name pool.
Flagged in instructor feedback - docs that disagree with code are
worse than no docs.

## Balance playthrough to day 20
Full run with the win condition active. Result: RESCUED at the dawn
of day 21 with 3 survivors left. Seven survivors died on day 20 -
the final horde (40+ zombies) nearly wiped the roster, and the
barricade hit zero multiple times during the run. Verdict: the
Week 3 tuning stands. Kill-switch check: did NOT trigger (deaths
occurred and the barricade broke), so starting materials stay at 10.
The game is winnable but not guaranteed, and the win was decided on
the final night - exactly the tension a survival game should have.

## Automated balance verification (100% machine-played)
Compiled the dev build and ran 5 automated playthroughs under fixed
strategies. Result: 1 win (barricade-focused, rescued 6 of 10),
4 losses (days 10-18). Strategies that under-invested in the
barricade all died in the day 10-16 window; the two controls
(pure scavenge, pure defend) failed in distinct, predictable ways
(resource hoarding vs starvation). Conclusion: the game is winnable,
strategy choice matters, and the barricade is the dominant lever.


|`Strategy`|`Outcome`|`Days survived`|`Rescued`|`First death`|`Barricade builds`|
|---|---|---|---|---|---|
|`Hoarder`|`wiped`|`13`|`0`|`day 8`|`0`|
|`Militia`|`wiped`|`10`|`0`|`day 8`|`0`|
|`Turtle`|`rescued`|`20`|`6`|`day 20`|`97`|
|`Balanced`|`wiped`|`16`|`0`|`day 16`|`16`|
|`ChaosGremlin`|`wiped`|`18`|`0`|`day 14`|`41`|
