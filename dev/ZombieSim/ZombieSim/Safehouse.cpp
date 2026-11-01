#include "Safehouse.h"
#include <iostream>

void Safehouse::AddSurvivor(const std::string& name)
{
	mSurvivors.push_back(Survivor(name));
}

std::vector<Survivor>& Safehouse::GetSurvivors()
{
	return mSurvivors;
}

int Safehouse::GetFood() const { return mFood; }
void Safehouse::AddFood(int amount) { mFood += amount; }

void Safehouse::PrintStatus() const
{
	std::cout << "=== SAFEHOUSE STATUS ===\n";
	std::cout << "Food: " << mFood << "  Ammo: " << mAmmo
		<< "  Materials: " << mMaterials << "\n";
	std::cout << "Survivors:\n";
	for (const Survivor& s : mSurvivors)
	{
		std::cout << "  " << s.GetName() << " | HP: " << s.GetHealth()
			<< (s.IsAlive() ? "" : " (DEAD)") << "\n";
	}
}