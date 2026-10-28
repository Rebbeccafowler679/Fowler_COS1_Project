#include "Game.h"
#include "Helper.h"
#include <iostream>
#include <cstdlib>


void Game::Run()
{
	// Starting roster — Milestone 1 keeps it fixed.
	mSafehouse.AddSurvivor("Maya");
	mSafehouse.AddSurvivor("Dre");
	mSafehouse.AddSurvivor("Sam");

	bool running = true;
	while (running)
	{
		std::cout << "\n===== ZOMBIE SURVIVAL - Day " << mDay << " =====\n";
		std::cout << "1. View status\n";
		std::cout << "2. Assign tasks\n";
		std::cout << "3. Next day\n";
		std::cout << "4. Quit\n";

		unsigned int choice = Helper::GetMenuChoice(1, 4);

		switch (choice)
		{
		case 1: ViewStatus(); break;
		case 2: AssignTasks(); break;
		case 3: NextDay(); break;
		case 4: running = false; break;
		}
	}

	std::cout << "You survived " << mDay << " day(s). Thanks for playing!\n";
}

void Game::ViewStatus() const
{
	mSafehouse.PrintStatus();
}

void Game::AssignTasks()
{
	// Set every survivor's task for the coming day.
	for (Survivor& s : mSafehouse.GetSurvivors())
	{
		if (!s.IsAlive()) { continue; }

		std::cout << "\nAssign " << s.GetName() << ":\n";
		std::cout << "1. Scavenge  2. Defend  3. Rest\n";
		unsigned int pick = Helper::GetMenuChoice(1, 3);
		s.SetTask(static_cast<Task>(pick - 1));	// enum order matches menu order
	}
}

void Game::NextDay()
{
	ResolveScavenging();

	// The group eats: 1 food per living survivor.
	int mouths = 0;
	for (Survivor& s : mSafehouse.GetSurvivors())
	{
		if (s.IsAlive()) { mouths++; }
	}

	if (mSafehouse.GetFood() >= mouths)
	{
		mSafehouse.AddFood(-mouths);
		std::cout << "The group ate " << mouths << " food.\n";
	}
	else
	{
		// Not enough food: everyone still alive loses health.
		mSafehouse.AddFood(-mSafehouse.GetFood());	// eat what's left
		std::cout << "Not enough food! The group goes hungry.\n";
		for (Survivor& s : mSafehouse.GetSurvivors())
		{
			if (s.IsAlive()) { s.TakeDamage(10); }
		}
	}

	// Rest heals.
	for (Survivor& s : mSafehouse.GetSurvivors())
	{
		if (s.IsAlive() && s.GetTask() == Task::Rest)
		{
			s.Heal(5);
		}
	}

	++mDay;
}

void Game::ResolveScavenging()
{
	for (Survivor& s : mSafehouse.GetSurvivors())
	{
		if (!s.IsAlive()) { continue; }

		if (s.GetTask() == Task::Scavenge)
		{
			int found = rand() % 4 + 1;	// 1-4 food per scavenger
			mSafehouse.AddFood(found);
			std::cout << s.GetName() << " scavenged " << found << " food.\n";
		}
		// Defend does nothing yet — zombie attacks arrive in Week 2.
	}
}