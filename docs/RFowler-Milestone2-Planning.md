> Use this worksheet to plan the next phase of your project **before you begin coding**
> Be clear, specific, and intentional—this will guide your development this week.

---
##  Project Overview

**Project Name:**
→ Zombie Survival Sim
  
**What does your program currently do? (1–3 sentences)**   
→ It is a console survival game where the player manages a safehouse of three survivors. Each day the player assigns tasks (Scavenge, Defend, Rest), scavenging brings in food and ammo, survivors eat, and then a zombie horde attacks at night. The horde grows as the days go up, defenders repel zombies using ammo, and breakthrough zombies injure or kill survivors.

---
##  Current Progress Check  
  
**What is working right now?**   
→ The main menu loop, task assignment, the day cycle (scavenge, eat, attack, rest), resource tracking for food and ammo, and the new Zombie class with the nightly attack resolution. Survivors can be injured, die, and heal on rest.
  
**What is NOT working or incomplete?**   
→ There is no game over condition, so the game keeps running even if all survivors die. There is also no end-of-day summary, so the results of a day print as scattered lines instead of one readable recap.
  
**What feels confusing or messy in your code?**   
→ The attack output and eating output are mixed together in one long scroll, which makes it hard to tell what happened on which day. NextDay() is also getting long as more steps get added to the day cycle.

---
## Feature Planning  
  
List the features you plan to add or improve this week.  
  
### Feature 1  
**Name:**   
→ Game over condition and end screen  
  
**What does this feature do?**   
→ After each nightly attack, the game checks if any survivors are still alive. If none are, it prints a game over screen showing how many days the player survived and exits the loop cleanly.  
  
**Why is this feature important?**   
→ Right now the game can never actually be lost, so there are no real stakes. A survival game needs an ending, and this also makes the difficulty scaling (bigger hordes each day) mean something. 
  
---
### Feature 2  
**Name:**   
→ Day summary screen  
  
**What does this feature do?**   
→ At the end of each day, print one clear recap block: what day it is, what was scavenged, how big the horde was, how many zombies were repelled, who was injured or died, and current food/ammo totals. 
  
**Why is this feature important?**   
→ This is my usability improvement. Right now the player has to scroll up and piece together what happened. One summary block makes the consequences of their choices visible at a glance.  
  
---
  
### Feature 3 (optional)  
**Name:**   
→ Clearer task assignment prompts  
  
**What does this feature do?**   
→ When assigning tasks, the prompt will explain what each option does and what it costs, like noting that Defend uses 1 ammo per repelled zombie and Rest heals 5 HP.  
  
**Why is this feature important?**   
→ New players should not have to guess the rules. Showing the cost of Defend up front helps the player make an informed choice instead of learning by losing survivors.  
  
---
## System Design Updates  
  
**Will you need to create any new classes? If so, which ones?**   
→ No new classes this week. The three classes (Game, Safehouse, Survivor) plus Zombie already cover the design. 
  
**Will you modify any existing classes? How?**   
→ Game gets the game over check (loop ends when no survivors are alive) and a PrintDaySummary method to group the recap output. Safehouse may get a small helper like GetAliveCount() so Game can ask one question instead of looping through survivors itself. 
  
**What data structures will you use (vectors, 2D vectors, etc.)?**   
→ The existing vector<Survivor> in Safehouse, plain int counters for resources, and enum class Task for assignments. The Zombie horde stays a stack object created fresh each night since it does not need to outlive the attack.  
  

## Program Flow  
  
**Describe how a user interacts with your program:**  
  
1. Program starts →  Main menu appears with options to assign tasks, view status, start the next day, or quit. 
2. User chooses →  Assigns each living survivor a task (Scavenge, Defend, Rest) using numbered menu choices. 
3. Program responds → Starting the next day runs scavenging, eating, the zombie attack, and rest healing, then prints the day summary.  
4. Loop/next step → Returns to the menu for the next day. If all survivors are dead, the game over screen prints with the final day count and the program ends.
  

## Usability Improvements  
  
How will you make your program easier to use this week?  
  
- Clearer prompts:   
→ Task prompts will say what each task does and costs (ammo for Defend, healing for Rest) so the player can plan instead of guess.
  
- Better error handling:   
→ Menu input already re-asks on out-of-range numbers through the Helper class; I will test it with bad inputs (letters, 0, huge numbers) to make sure nothing crashes.  
  
- Improved menu/navigation:   
→ The day summary screen groups each day's events into one labeled block, so the console reads as a series of days instead of one long unbroken scroll.  
  

## Potential Challenges  
  
**What do you think will be the hardest part this week?**   
→ Getting the game over check in the right place. It has to run after the attack but before the menu shows again, and I need to make sure dead survivors are handled correctly in the summary without the loop printing stale info.  
  
**What is your plan if you get stuck?**   
→  Rebuild first to separate real compiler errors from stale IntelliSense squiggles, read the Error List file and line, and isolate the problem in a small test before changing more code. That process worked for the E0020 typo bugs this week. 
  

  
## Level Up Goal  
  
**What skill are you focusing on improving this week?**   
→ Memory management discipline: knowing when an object should live on the stack versus the heap.  
  
**What will you do to improve it?**   
(e.g., tutorial, practice, debugging, office hours)   
→ Apply it in real decisions, like keeping the nightly Zombie horde on the stack because it only exists for one attack, and write down the reasoning in my design notes so the choice is deliberate instead of a habit. 
  

## Task Breakdown (GitHub Issues Planning)  
  
List the tasks you plan to create as GitHub Issues:  
- Add game over condition and end screen
- Add day summary screen (usability)
- Improve task assignment prompts with costs
- PR dev into main and submit Milestone 2
---
  
##  Final Check  
  
Before you start coding, ask yourself:  
  
[yes] Do I know what I’m building this week?   
[yes] Do I know where to start?   
[yes] Did I break my work into small tasks?   
  
If yes → start coding    
If no → refine your plan first   
  
##  Final Thought  
  
 Plan it now… or debug it later.