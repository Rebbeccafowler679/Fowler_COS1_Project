# 🚀 Welcome to Project & Portfolio!

This repository will be used to keep track of research and development conducted in this class. Follow the instructions below to get started.
cos
### Getting Started

**1.** Review the [About](./docs/01_about/README.md) README and all of the links it provides.

**2.** Review the documentation and [Getting Started](./docs/02_getting_started/README.md) steps in this repository's docs folder.

**3.** Attend the first Live Lecture to see a live setup demo. If you are unable to attend, make sure to watch the archive.

### Next Steps...

After completing the above steps, feel free to begin updating this readme where indicated below. Remember to update this document each week to receive proper credit for the weekly Milestone assignment.

<br>

> ❗️ &nbsp; Now that you have read to this point, go ahead and delete this sentence and everything above it.

<br>

# Project & Portfolio 1

### Rebbecca Fowler

Hello my name is [Rebbecca Fowler]. I am a student from [Full Sail University]. The purpose of this repository is to practice development using version control. This work will help me begin to build a portfolio of skills and accomplishment that can be shared in the future.

<br>

## 📢 &nbsp; Weekly Stand Up

Each week I will summarize my milestone activity and progress by writing a stand-up. A stand-up is meant to be a succinct update on how things are going. Use these prompts as a guide on what to write about:

⚙️ Overview: What did you work on this week.

WEEK 1 -- This week I set up my GitHub workflow (repo, dev branch, Project board, iterations) and built the foundation of my Zombie Survival Sim: the Survivor, Safehouse, and Game classes, an input-validated menu loop, and a working day cycle where scavengers find food, the group eats, and resting heals. Committed and pushed to dev.

WEEK 2 -- This week I built the Zombie class and wired nightly attacks into the day cycle. Hordes scale with the day count, defenders repel zombies using ammo, and breakthrough zombies injure or kill survivors. I also added a game over condition with an end screen, a day summary screen, and a usability pass on the menus. I completed my Milestone 2 planning worksheet before coding and kept my design notes and changelog current all week.

WEEK 3 --

WEEK 4 


--
<br>
🌵 Challenges - What problems did I have & how I'm addressing them.

WEEK 1 -- A missing closing brace in my helper header broke the entire build in a confusing way — eight errors that all traced back to one character. I fixed it by reading the actual error codes instead of guessing. I also hit a text encoding issue where a Unicode dash garbled my menu title, which taught me to stick to plain ASCII in string literals.

WEEK 2 -- Two hard moments this week. First, an LNK2019 linker error that turned out to be a missing function body - the header made a promise the cpp file never kept. Second, simple typos (Survior, defender vs defenders) that cascaded into scary-looking error lists. Both taught me the same lesson: read the actual error, find the file and line, and do not guess. I also learned to trust Rebuild over IntelliSense squiggles, since E-codes can linger after the real fix.

WEEK 3 --

WEEK 4 --
<br>
🏆 Accomplishments: What you learned or leveled up.

WEEK 1 -- I leveled up at error-driven debugging — tracing C1075 to its root cause instead of treating the seven fallout errors as separate problems. I also got comfortable moving Issues across the board as work actually finished rather than batch-closing at the deadline, and I learned to link commits to Issues with "Closes #" so the board stays honest automatically.

WEEK 2 -- I leveled up on memory management discipline. The nightly horde lives on the stack because it never outlives one attack, and the breakthrough phase uses a vector of pointers to living survivors as a target pool, so dead survivors leave the target list but stay in the real roster. Both were deliberate decisions I documented in my prototype notes. I also got faster at classifying errors: E-codes vs C-codes vs LNK-codes.

WEEK 3 --

WEEK 4 --
<br>
🔮 Next Steps: Priorities before next milestone.

WEEK 1 -- For Week 2 I'm planning zombie attacks against the safehouse, giving the Defend task a real purpose, and health consequences for survivors. I'll also start linking my commits to Issues as I work.

WEEK 2 --Before Week 3 I want to give materials a real use (like barricade repairs), add a maximum health cap so Rest cannot heal forever, and look at a difficulty curve beyond just bigger hordes. I also want to keep the commit-little-and-often habit going, since my history this week actually showed the project evolving.

WEEK 3 --

WEEK 4 --

<br>

### Week 1

This week I set up my GitHub workflow -repository, dev branch, Project board with iterations - and built the foundation of my Zombie Survival Sim, including the Survivor, Safehouse, and Game classes, an input-validated menu loop, and a working day cycle where scavengers find food, the group eats, and resting heals. My biggest challenge was a missing closing brace in my helper header that broke the build with eight confusing errors that all traced back to one character; I fixed it by reading the actual error text instead of guessing, and I also learned to stick to plain ASCII in strings after a Unicode dash garbled my menu title. I leveled up at error-driven debugging and at keeping my Project board honest by moving Issues to Done as work finished and linking commits to Issues with "Closes #". Next week I'm building the zombie attack system so the Defend task has a real purpose, adding health consequences for survivors, and keeping up the linked-commit habit as I work.

### Week 2

This week I built the Zombie class and wired nightly attacks into the day cycle: hordes scale with the day count, defenders repel zombies using ammo, and breakthrough zombies injure or kill survivors, plus I added a game over screen, a day summary screen, and a usability pass on the menus. My biggest challenges were an LNK2019 linker error caused by a function I declared but never wrote the body for, and simple typos that cascaded into scary error lists, both of which taught me to read the actual error, find the file and line, and trust Rebuild over IntelliSense squiggles. I leveled up on memory management discipline, keeping the nightly horde on the stack since it never outlives one attack, and using a vector of pointers to living survivors as the attack target pool so dead survivors leave the list but stay in the real roster. Before Week 3 I want to give materials a real use like barricade repairs, add a maximum health cap, and look at a difficulty curve beyond just bigger hordes.

### Week 3

Stay tuned, this stand up is coming soon...

### Week 4

My final stand up...
