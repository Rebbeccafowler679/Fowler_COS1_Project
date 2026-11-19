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

	std::cout << "Survive 20 days. Rescue arrives at dawn on day 21.\n";

	bool running = true;
	while (running && !mGameOver)
	{
		std::cout << "\n===== ZOMBIE SURVIVAL - Day " << mDay << " of 20 =====\n";
		std::cout << "1. View status\n";
		std::cout << "2. Assign tasks\n";
		std::cout << "3. Next day\n";
		std::cout << "4. Build barricade (2 materials = +2 barricade HP)\n";
		std::cout << "5. Quit\n";

		// Helper re-asks until the player enters a number in range
		unsigned int choice = Helper::GetMenuChoice(1, 5);
		switch (choice)
		{
		case 1: ViewStatus(); break;
		case 2: AssignTasks(); break;
		case 3: NextDay(); break;
		case 4: BuildBarricade(); break;
		case 5: running = false; break;
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
		std::cout << "1. Scavenge (find 1-4 food and 1-2 materials,\n";
		std::cout << "            30% chance of 1-2 ammo)\n";
		std::cout << "2. Defend (repel up to 2 zombies each, 1 ammo per kill;\n";
		std::cout << "            fights hand-to-hand and takes 3 HP if no ammo)\n";
		std::cout << "3. Rest (heal 5 HP)\n";

		unsigned int pick = Helper::GetMenuChoice(1, 3);
		// menu is 1-3 but the Task enum is 0-2, so shift down by one
		s.SetTask(static_cast<Task>(pick - 1));
	}
}

// Runs one full day by calling each phase in order.
// Refactored in Week 3: each phase is its own function, so this
// reads like a summary of the day instead of a wall of code.
void Game::NextDay()
{
	ResolveScavenging();
	ResolveEating();
	ResolveAttack();

	CheckGameOver();
	if (mGameOver) { return; } // skip healing and summary on the final day

	ResolveResting();
	PrintDaySummary();

	++mDay;
	CheckWinCondition();       // dawn of day 21 ends the game
	if (mGameOver) { return; } // no arrivals after the rescue
	CheckNewArrival();         // check for new survivors as the new day begins
}

// Every living survivor on Scavenge duty finds 1-4 food and
// 1-2 materials, with a 30% chance of also finding 1-2 ammo.
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

			// materials are guaranteed, just like food
			int mats = rand() % 2 + 1; // 1 to 2 materials
			mSafehouse.AddMaterials(mats);
			std::cout << s.GetName() << " also salvaged " << mats << " materials!\n";

			if (rand() % 100 < 30)
			{
				int ammo = rand() % 2 + 1; // 1 to 2 ammo
				mSafehouse.AddAmmo(ammo);
				std::cout << s.GetName() << " also found " << ammo << " ammo!\n";
			}
		}
	}
}

// Each living survivor eats 1 food. If there is not enough,
// food hits zero and hunger deals 10 damage to everyone alive.
void Game::ResolveEating()
{
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
		mSafehouse.AddFood(-mSafehouse.GetFood());
		std::cout << "Not enough food! The group goes hungry.\n";
		for (Survivor& s : mSafehouse.GetSurvivors())
		{
			if (s.IsAlive()) { s.TakeDamage(10); }
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

// Win rule: survive to the dawn of day 21 and rescue arrives.
// Uses the same mGameOver flag as losing - the flag just means
// "the game ends now," and the screen says which ending you got.
void Game::CheckWinCondition()
{
	const int WIN_DAY = 20;
	if (mDay <= WIN_DAY) { return; } // not rescued yet

	mGameOver = true;
	std::cout << "\n===== RESCUED! =====\n";
	std::cout << "At dawn on day 21, you hear engines on the highway.\n";
	std::cout << mSafehouse.GetAliveCount() << " survivor(s) made it out alive.\n";
	std::cout << "The safehouse held. You won.\n";
}

// Survivors assigned to Rest recover 5 HP.
void Game::ResolveResting()
{
	for (Survivor& s : mSafehouse.GetSurvivors())
	{
		if (s.IsAlive() && s.GetTask() == Task::Rest)
		{
			s.Heal(5);
		}
	}
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
		<< "  Materials: " << mSafehouse.GetMaterials()
		<< "  Barricade HP: " << mSafehouse.GetBarricade() << "\n";
	for (const Survivor& s : mSafehouse.GetSurvivors())
	{
		std::cout << "  " << s.GetName() << " | HP: " << s.GetHealth()
			<< (s.IsAlive() ? "" : " (DEAD)") << "\n";
	}
	std::cout << "----------------------------\n";
}

// Day 3, 6, 9... a pair of survivors finds the safehouse, up to the
// roster cap of 11. If only one bed is left, only one joins.
void Game::CheckNewArrival()
{
	if (mDay % 3 != 0) { return; }

	const int ROSTER_CAP = 11;
	const int NEW_ARRIVALS = 2;

	// Static locals remember where we are in the name pool between
	// calls, so names do not repeat until the pool cycles.
	static const char* names[] = { "Rae", "Kai", "Juno", "Ash", "Noa", "Lex", "Sky", "Rue" };
	const int NAME_COUNT = 8;
	static int nextName = 0;

	for (int i = 0; i < NEW_ARRIVALS; i++)
	{
		if (mSafehouse.GetSurvivors().size() >= ROSTER_CAP)
		{
			return; // roster full - no room for anyone else tonight
		}

		std::string name = names[nextName % NAME_COUNT];
		nextName++;

		mSafehouse.AddSurvivor(name);
		std::cout << "\n*** " << name << " has joined the safehouse! ***\n";
	}
}

// Menu option 4: spend 2 materials to add 2 barricade HP.
// Fails gracefully if the player cannot afford it.
void Game::BuildBarricade()
{
	const int COST = 2;
	const int HP_GAIN = 2;

	if (mSafehouse.GetMaterials() < COST)
	{
		std::cout << "Not enough materials! Need " << COST
			<< ", you have " << mSafehouse.GetMaterials() << ".\n";
		return;
	}

	mSafehouse.AddMaterials(-COST);
	mSafehouse.AddBarricade(HP_GAIN);
	std::cout << "Barricade reinforced! +" << HP_GAIN << " barricade HP (now "
		<< mSafehouse.GetBarricade() << ").\n";
}