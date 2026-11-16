# Milestone 3 - Zombie Survival Sim

## Features Added

- **New survivor arrivals every 3 days.** On day 3, 6, 9, and so on, a
  new survivor (Rae, Kai, or Juno) joins the safehouse, up to a cap of
  6 survivors. This gives the player a growing workforce to assign but
  also more mouths to feed, so it adds pressure instead of just help.
- **Horde scaling: +2 zombies per night.** The horde size is now
  (day * 2) plus a small random amount, instead of a flat value. The
  threat now grows over time so the late game is harder than day 1.
- **Barricade system.** Survivors can scavenge materials, and the
  player can spend 3 materials from the menu to add 2 barricade HP.
  During the night attack, zombies that get past the defenders hit the
  barricade first (1 zombie per 1 barricade HP) before any survivor
  takes damage.
- **Guaranteed materials from scavenging.** Scavenging now always
  returns 1-2 materials along with 1-4 food, so the barricade system
  is always usable and never starves on bad luck.

## Updates to System Design

- Added a new resource, **materials**, to the Safehouse class, tracked
  alongside food and ammo.
- Added **barricade HP** as a Safehouse stat. It works as a damage
  buffer between the horde and the survivors: zombies that break
  through the defense phase drain barricade HP one-for-one, and only
  the leftovers can hurt survivors.
- The survivor **name pool** (Rae, Kai, Juno) lives inside the
  CheckNewArrival function using static local variables, so the game
  remembers which name is next without adding new member variables
  to the Game class.

## Refactoring Improvements

- **Broke NextDay() into smaller phase functions.** NextDay used to
  be one long function that handled scavenging, eating, the zombie
  attack, resting, and the day summary all inline. I split it into
  ResolveScavenging, ResolveEating, ResolveAttack, ResolveResting,
  and PrintDaySummary, so NextDay now reads as a short list of phases
  in order. Each phase function has one clear job, and the order of
  the day is visible at a glance instead of buried in one long block.
- **Extracted CheckNewArrival** for the same reason: the arrival logic
  (day check, roster cap, name pick) is its own function called once
  after the day counter increments, instead of living inside NextDay.
- **Improved menu and prompt text** so the menu shows the new build
  option and the scavenge prompt tells the player exactly what
  scavenging returns (1-4 food, 1-2 materials, 30% chance of 1-2 ammo).

## What I Changed and Why

- I made materials a guaranteed drop because the barricade is a core
  defensive option, and a 25% random chance meant the player could
  play several days unable to interact with it at all. The tuning
  knob for balance is the barricade cost (3 materials for 2 HP),
  not the drop rate.
- I capped arrivals at 6 survivors because each survivor adds 5 food
  demand per day; without a cap the food economy would collapse and
  the game would become unloseable-but-unwinnable busywork.
- I kept "build barricade" and "repair barricade" as one menu option
  because they are the same action mechanically: both spend materials
  to add HP to the same pool.
- The horde scaling (+2 per night) and the arrival pacing (every 3
  days) were tuned against each other: the horde grows slightly
  faster than the roster, so the game stays tense but survivable if
  the player manages tasks and barricades well.