#include "Zombie.h"
#include "Safehouse.h"
#include <iostream>
#include <vector>
#include <cstdlib> // for rand()

// Constructor: horde size grows with the day number.
Zombie::Zombie(int day)
{
	// Week 3: horde grows by 2 every night (day 1 = 2-3 zombies),
	// with a small random term so nights are not perfectly predictable
	mHordeSize = (day * 2) + (rand() % 2);
}

int Zombie::GetHordeSize() const
{
	return mHordeSize;
}

// The nightly attack, resolved in four phases:
//   1. Gun defense - defenders shoot zombies, 1 ammo per kill
//   2. Hand-to-hand - defenders block leftovers with their bodies
//   3. Barricade - built-up barricade HP absorbs breakthrough zombies
//   4. Breakthrough - anything unstopped hurts random survivors
void Zombie::Attack(Safehouse& safehouse) const
{
	std::cout << "\nA horde of " << mHordeSize << " zombie(s) attacks the safehouse!\n";

	// Count living defenders - only survivors assigned to Defend
	// who are still alive can fight tonight.
	int defenders = 0;
	for (Survivor& s : safehouse.GetSurvivors())
	{
		if (s.IsAlive() && s.GetTask() == Task::Defend) { defenders++; }
	}

	// Phase 1: gun defense. Each defender repels up to 2 zombies, 1 ammo each.
	// repelled is capped twice: by defender capacity AND by ammo in stock.
	int gunCapacity = defenders * 2;
	int repelled = mHordeSize;
	if (repelled > gunCapacity) { repelled = gunCapacity; }
	if (repelled > safehouse.GetAmmo()) { repelled = safehouse.GetAmmo(); }

	safehouse.AddAmmo(-repelled); // spend one bullet per zombie shot

	if (repelled > 0)
	{
		std::cout << defenders << " defender(s) shot down " << repelled
			<< " zombie(s), using " << repelled << " ammo.\n";
	}

	// Phase 2: hand-to-hand. Whatever the guns could not cover, defenders
	// block with their bodies: 1 zombie each, but they take 3 damage each.
	int remaining = mHordeSize - repelled;
	if (remaining > 0 && defenders > 0)
	{
		int melee = remaining;
		if (melee > defenders) { melee = defenders; } // one zombie per defender

		// walk the roster and assign one melee fight per defender
		int hitsLeft = melee;
		for (Survivor& s : safehouse.GetSurvivors())
		{
			if (hitsLeft <= 0) { break; }
			if (s.IsAlive() && s.GetTask() == Task::Defend)
			{
				s.TakeDamage(3);
				hitsLeft--;
				std::cout << s.GetName() << " fought a zombie hand-to-hand! (-3 HP)\n";
			}
		}

		repelled += melee;
		remaining -= melee;
	}

	// Fully stopped: nobody gets hurt beyond the melee bruises.
	if (repelled == mHordeSize)
	{
		std::cout << "The safehouse held. No one got inside.\n";
		return;
	}

	if (defenders == 0)
	{
		std::cout << "No one was defending!\n";
	}
	std::cout << remaining << " zombie(s) broke through!\n";

	// Phase 3: the barricade absorbs breakthrough zombies first.
	// Each barricade HP point blocks one zombie and is destroyed doing it.
	int barricade = safehouse.GetBarricade();
	if (barricade > 0 && remaining > 0)
	{
		int blocked = remaining;
		if (blocked > barricade) { blocked = barricade; }

		safehouse.AddBarricade(-blocked);
		remaining -= blocked;
		std::cout << "The barricade held back " << blocked
			<< " zombie(s) but took " << blocked << " damage.\n";

		if (remaining <= 0)
		{
			std::cout << "The barricade stopped everything. No one was hurt.\n";
			return; // nothing got past the barricade
		}
	}

	// Phase 4: breakthrough zombies each deal 5 damage to a random
	// living survivor. Build a list of POINTERS to the living so we
	// can remove the dead from the target pool without touching
	// the real roster inside Safehouse.
	std::vector<Survivor*> living;
	for (Survivor& s : safehouse.GetSurvivors())
	{
		if (s.IsAlive()) { living.push_back(&s); }
	}

	for (int i = 0; i < remaining && !living.empty(); i++)
	{
		int pick = rand() % living.size(); // random target each zombie
		living[pick]->TakeDamage(5);
		std::cout << living[pick]->GetName() << " was attacked! (-5 HP)\n";
		if (!living[pick]->IsAlive())
		{
			std::cout << living[pick]->GetName() << " has died!\n";
			// remove the dead from the target pool so later zombies
			// only attack survivors who are still alive
			living.erase(living.begin() + pick);
		}
	}
}