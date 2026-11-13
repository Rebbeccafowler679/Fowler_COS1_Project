#include "Safehouse.h"
#include <iostream>

// Adds a new survivor to the roster by name.
// push_back copies the new Survivor into the vector.
void Safehouse::AddSurvivor(const std::string& name)
{
	mSurvivors.push_back(Survivor(name));
}

// Returns the roster by reference so callers (like Game) can
// read AND modify the survivors inside, e.g. assigning tasks.
std::vector<Survivor>& Safehouse::GetSurvivors()
{
	return mSurvivors;
}

// Food getters/setters. AddFood takes positives AND negatives:
// scavenging adds, eating subtracts.
int Safehouse::GetFood() const { return mFood; }
void Safehouse::AddFood(int amount) { mFood += amount; }

// Ammo getters/setters. Defending spends it, scavenging can find it.
int Safehouse::GetAmmo() const { return mAmmo; }
void Safehouse::AddAmmo(int amount) { mAmmo += amount; }

// Materials getters/setters. Scavengers can salvage them,
// and they are spent building the barricade.
int Safehouse::GetMaterials() const { return mMaterials; }
void Safehouse::AddMaterials(int amount) { mMaterials += amount; }

// Barricade HP: built with materials, chewed through by breakthrough
// zombies. Clamps at zero so it can never go negative.
int Safehouse::GetBarricade() const { return mBarricade; }
void Safehouse::AddBarricade(int amount)
{
	mBarricade += amount;
	if (mBarricade < 0) { mBarricade = 0; } // never below zero
}

// Prints the full status screen: resource totals plus one line
// per survivor with HP, assigned task, and a (DEAD) marker.
void Safehouse::PrintStatus() const
{
	std::cout << "=== SAFEHOUSE STATUS ===\n";
	std::cout << "Food: " << mFood << "  Ammo: " << mAmmo
		<< "  Materials: " << mMaterials
		<< "  Barricade HP: " << mBarricade << "\n";
	std::cout << "Survivors:\n";
	for (const Survivor& s : mSurvivors)
	{
		std::cout << "  " << s.GetName() << " | HP: " << s.GetHealth()
			<< " | Task: " << s.GetTaskName()
			<< (s.IsAlive() ? "" : " (DEAD)") << "\n";
	}
}

// Counts only the living survivors.
// Game uses this for the game over check and the day summary.
int Safehouse::GetAliveCount() const
{
	int count = 0;
	for (const Survivor& s : mSurvivors)
	{
		if (s.IsAlive()) { count++; }
	}
	return count;
}