# Zombie Survival Sim — Prototype / Design Blueprint

## 1. Class Design

| Class         | Responsibility                                                                                               |
| ------------- | ------------------------------------------------------------------------------------------------------------ |
| **Survivor**  | One person: name, health, alive status, current task (Scavenge / Defend / Rest). Handles damage and healing. |
| **Safehouse** | The base: owns the shared resource counters (food, ammo, materials) and the survivor roster. Prints status.  |
| **Game**      | Owns the day counter, the menu loop, and day resolution. Connects all the other classes each turn.           |
| **Zombie**    | (Week 2) Models the nightly threat: horde size and attack strength, resolved against the defenders.          |

**How they interact:** Game owns one Safehouse; the Safehouse owns the Survivors; each night the Game creates/resolves a Zombie horde against the Safehouse. Survivors never talk to Zombies directly — the Safehouse mediates (defenders protect the whole building, not themselves).
## Design Decisions

**Zombie horde: stack object, not heap.** The horde only exists while
resolving one night's attack, so it will be created on the stack
(`Zombie horde(day);`) and cleaned up automatically. Using `new`/`delete`
here would add manual memory management with no benefit — the reading's
"don't overuse pointers" rule applies. Heap allocation stays reserved
for things that must outlive the scope that created them.

[// Option A: stack — simple, fine for one horde per night
Zombie horde(day);
horde.Attack(mSafehouse);

[// Option B: heap — needed if the horde must outlive the function
Zombie* horde = new Zombie(day);
horde->Attack(mSafehouse);
delete horde;   // forget this = memory leak
## 2. Data Structures

- `std::vector&lt;Survivor&gt;` inside Safehouse — the roster. Vector because the group can grow (finding survivors) and shrink (deaths).
- Plain `int` counters in Safehouse — food, ammo, materials. No container needed; they're single values.
- `int mDay` in Game — the day counter drives difficulty (horde size scales with it).
- `enum class Task { Scavenge, Defend, Rest }` — keeps task assignment type-safe instead of using magic numbers.

**What the program tracks:** current day, each survivor's name/health/alive/task, shared food/ammo/materials, and (Week 2) the night's horde size.

## 3. Program Flow

1. **Start:** seed the RNG once → create the Game → Game creates the Safehouse and the starting roster.
2. **Each day (the main loop):**
   - Show menu → user picks: View status / Assign tasks / Next day / Quit
   - Assign tasks sets each living survivor's job
   - Next day resolves in order: scavenging → group eats → zombie attack (Week 2) → rest healing → day counter +1
3. **End:** user quits from the menu, or (Week 2) all survivors die → game over screen shows days survived.

## 4. User Interaction

- Everything is menu-driven with number input, validated by `Helper::GetMenuChoice` (letters and out-of-range numbers re-prompt instead of crashing).
- Assign tasks: one prompt per survivor, 1–3.
- Input changes the next day's outcome: more scavengers = more food but fewer defenders at night; resting heals but produces nothing. That tradeoff is the core decision of the game.

## Scaling check (Week 2 and beyond)

- Zombie attacks slot into NextDay() as one more resolution step — no restructuring needed.
- Random events (Week 3) can reuse the same "resolve one step per day" pattern.
- Save/load (Week 4) writes out exactly the data listed in section 2 — which is why it was worth deciding the data structures now.










