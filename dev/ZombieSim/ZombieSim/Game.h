#pragma once
#include "Safehouse.h"

// Game
// Owns the whole program: the menu loop, the day cycle, and the win/lose state.
// It holds one Safehouse and talks to the Zombie class once per night.
class Game
{
public:
	void Run(); // starts the program and loops the main menu until quit or game over

private:
	void ViewStatus() const;   // prints the safehouse status screen (menu option 1)
	void AssignTasks();        // lets the player give each living survivor a task (menu option 2)
	void NextDay();            // runs one full day by calling each phase in order
	void ResolveScavenging();  // handles food/ammo gains for survivors on Scavenge duty
	void ResolveEating();      // survivors eat 1 food each; hunger deals damage if short
	void ResolveAttack();      // creates the nightly zombie horde and lets it attack
	void CheckGameOver();      // ends the game when no survivors are left alive
	void ResolveResting();     // survivors assigned to Rest heal 5 HP
	void PrintDaySummary();    // prints one recap block at the end of each day

	Safehouse mSafehouse;   // the safehouse: resources + the survivor roster
	int mDay = 1;           // current day number, used for display and horde scaling
	bool mGameOver = false; // flips to true when the last survivor dies
};