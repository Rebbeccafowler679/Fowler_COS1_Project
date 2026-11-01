#pragma once
#include "Safehouse.h"

class Game
{
public:
	void Run();		// owns the whole program loop

private:
	void PrintMenu() const;
	void ViewStatus() const;
	void AssignTasks();
	void NextDay();
	void ResolveScavenging();

	Safehouse mSafehouse;
	int mDay = 1;
};
