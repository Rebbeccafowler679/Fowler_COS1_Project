#pragma once
#include "Safehouse.h"

class Game
{
public:
	void Run(); // owns the whole program loop

private:
	void ViewStatus() const;
	void AssignTasks();
	void NextDay();
	void ResolveScavenging();
	void ResolveAttack();
	void CheckGameOver(); // NEW: ends the game when everyone is dead

	Safehouse mSafehouse;
	int mDay = 1;
	bool mGameOver = false; // NEW
};