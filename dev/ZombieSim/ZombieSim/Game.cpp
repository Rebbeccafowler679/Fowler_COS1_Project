#include "Game.h"
#include "Zombie.h"
#include "Helper.h"
#include <iostream>
#include <cstdlib> // for rand()

// Starts the game: creates the survivors, then loops the main menu.
// The loop ends when the player quits OR when CheckGameOver() flips mGameOver.
void Game::Run()
{
	// starting roster of three survivors
	mSafehouse.AddSurvivor("Maya");
	mSafehouse.AddSurvivor("Dre");
	mSafehouse.AddSurvivor("Sam");

	bool running = true;
	while (running && !mGameOver)
	{
		std::cout << "\n===== ZOMBIE SURVIVAL - Day " << mDay << " =====\n";
		std::cout << "1. View status\n";
		std::cout << "2. Assign tasks\n";
		std::cout << "3. Next day\n";
		std::cout << "4. Quit\n";

		// Helper re-asks until the player enters a number in range
		unsigned int choice = Helper::GetMenuChoice(1, 4);
		switch (choice)
		{
		case 1: ViewStatus(); break;
		case 2: AssignTasks(); break;
		case 3: NextDay(); break;
		case 4: running = false; break;
		}
	}

	// only prints on a manual quit; a game over has its own ending message
	if (!mGameOver)
	{
		std::cout << "You walked away on day " << mDay << ". The safehouse is on its own.\n";
	}
}

// Menu option 1: hand off to the safehouse's own status printer.
void Game::ViewStatus() const
{
	mSafehouse.PrintStatus();
}

// Menu option 2: walk through each living survivor and assign a task.
// Prompts list what each task does and costs so the player can plan.
void Game::AssignTasks()
{
	for (Survivor& s : mSafehouse.GetSurvivors())
	{
		if (!s.IsAlive()) { continue; } // dead survivors get no tasks

		std::cout << "\nAssign " << s.GetName() << " (HP " << s.GetHealth() << "):\n";
		std::cout << "1. Scavenge (find 1-4 food, 30% chance of 1-2 ammo)\n";
		std::cout << "2. Defend (repel up to 2 zombies each, 1 ammo per kill;\n";
		std::cout << "            fights hand-to-hand and takes 3 HP if no ammo)\n";
		std::cout << "3. Rest (heal 5 HP)\n";

		unsigned int pick = Helper::GetMenuChoice(1, 3);
		// menu is 1-3 but the Task enum is 0-2, so shift down by one
		s.SetTask(static_cast<Task>(pick - 1));
	}
}

// Runs one full day in order:
// scavenge -> eat -> zombie attack -> game over check -> rest healing -> summary.
void Game::NextDay()
{
	ResolveScavenging();

	// count how many mouths need feeding
	int mouths = 0;
	for (Survivor& s : mSafehouse.GetSurvivors())
	{
		if (s.IsAlive()) { mouths++; }
	}

	if (mSafehouse.GetFood() >= mouths)
	{
		// enough food: everyone eats 1
		mSafehouse.AddFood(-mouths);
		std::cout << "The group ate " << mouths << " food.\n";
	}
	else
	{
		// not enough: food hits zero and hunger deals 10 damage to each survivor
		mSafehouse.AddFood(-mSafehouse.GetFood());
		std::cout << "Not enough food! The group goes hungry.\n";
		for (Survivor& s : mSafehouse.GetSurvivors())
		{
			if (s.IsAlive()) { s.TakeDamage(10); }
		}
	}

	ResolveAttack();

	// if the attack (or hunger) killed the last survivor, end here:
	// skip healing, skip the summary, and do not advance the day counter
	CheckGameOver();
	if (mGameOver) { return; }

	// survivors assigned to Rest recover 5 HP
	for (Survivor& s : mSafehouse.GetSurvivors())
	{
		if (s.IsAlive() && s.GetTask() == Task::Rest)
		{
			s.Heal(5);
		}
	}

	PrintDaySummary(); // recap everything that happened today

	++mDay;
}

// Every living survivor on Scavenge duty finds 1-4 food,
// with a 30% chance of also finding 1-2 ammo.
void Game::ResolveScavenging()
{
	for (Survivor& s : mSafehouse.GetSurvivors())
	{
		if (!s.IsAlive()) { continue; }
		if (s.GetTask() == Task::Scavenge)
		{
			int found = rand() % 4 + 1; // 1 to 4 food
			mSafehouse.AddFood(found);
			std::cout << s.GetName() << " scavenged " << found << " food.\n";

			if (rand() % 100 < 30)
			{
				int ammo = rand() % 2 + 1; // 1 to 2 ammo
				mSafehouse.AddAmmo(ammo);
				std::cout << s.GetName() << " also found " << ammo << " ammo!\n";
			}
		}
	}
}

// Build tonight's horde on the stack and let it attack the safehouse.
// The horde only exists for this one call, so it does not need the heap.
void Game::ResolveAttack()
{
	Zombie horde(mDay);
	horde.Attack(mSafehouse);
}

// Game over rule: if nobody is alive, flip the flag and print the end screen.
// Run()'s loop condition sees the flag and exits cleanly.
void Game::CheckGameOver()
{
	if (mSafehouse.GetAliveCount() > 0) { return; } // someone is still standing

	mGameOver = true;
	std::cout << "\n===== GAME OVER =====\n";
	std::cout << "The last survivor has fallen. The safehouse is lost.\n";
	std::cout << "You survived " << mDay << " day(s).\n";
}

// Prints one labeled recap block so the player can see the day's results
// at a glance instead of scrolling back through scattered lines.
void Game::PrintDaySummary()
{
	std::cout << "\n----- DAY " << mDay << " SUMMARY -----\n";
	std::cout << "Survivors alive: " << mSafehouse.GetAliveCount()
		<< " of " << mSafehouse.GetSurvivors().size() << "\n";
	std::cout << "Food: " << mSafehouse.GetFood()
		<< "  Ammo: " << mSafehouse.GetAmmo()
		<< "  Materials: " << mSafehouse.GetMaterials() << "\n";
	for (const Survivor& s : mSafehouse.GetSurvivors())
	{
		std::cout << "  " << s.GetName() << " | HP: " << s.GetHealth()
			<< (s.IsAlive() ? "" : " (DEAD)") << "\n";
	}
	std::cout << "----------------------------\n";
}