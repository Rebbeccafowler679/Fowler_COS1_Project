#include "Zombie.h"
#include "Safehouse.h"
#include <iostream>
#include <vector>
#include <cstdlib>


Zombie::Zombie(int day)
{
	// Base 1-3 zombies, plus scaling: +1 more every 2 days survived.
	mHordeSize = 1 + (day / 2) + (rand() % 3);
}

int Zombie::GetHordeSize() const
{
	return mHordeSize;
}

void Zombie::Attack(Safehouse& safehouse) const
{
	std::cout << "\nA horde of " << mHordeSize << " zombie(s) attacks the safehouse!\n";

	// Count living defenders
	int defenders = 0;
	for (Survivor& s : safehouse.GetSurvivors())
	{
		if (s.IsAlive() && s.GetTask() == Task::Defend) { defenders++; }
	}

	// Each definder repels up to 2 zombies: every repel costs 1 ammo.
	int defenseCapacity = defenders * 2;
	int repelled = mHordeSize;
	if (repelled > defenseCapacity) { repelled = defenseCapacity; }
	if (repelled > safehouse.GetAmmo()) { repelled = safehouse.GetAmmo(); }

	safehouse.AddFood(-repelled); // spend the ammo

	if (defenders > 0)
	{
		std::cout << defenders << " defender(s) repelled " << repelled
			<< " zombie(s), using " << repelled << " ammo.\n";
	}
	else
	{
		std::cout << "No one was defending!\n";
	}

	int breakThrough = mHordeSize - repelled;
	if (breakThrough <= 0)
	{
		std::cout << "The safehouse held. No one was hurt.\n";
		return;
	}

	std::cout << breakThrough << " zombie(s) broke through!\n";

	// Gather the living so we can pick random victims.
	std::vector<Survivor*> living;
	for (Survivor& s : safehouse.GetSurvivors())
	{
		if (s.IsAlive()) { living.push_back(&s); }
	}

	// Each breakthrough zombie deals 5 damage to a random living survivor.
	for (int i = 0; i < breakThrough && !living.empty(); i++)
	{
		int pick = rand() % living.size();
		living[pick]->TakeDamage(5);
		std::cout << living[pick]->GetName() << " was attacked! (-5 HP)\n";
		if (!living[pick]->IsAlive())
		{
			std::cout << living[pick]->GetName() << " has died!\n";
			living.erase(living.begin() + pick); // dead can't be picked again
		}
	}
}