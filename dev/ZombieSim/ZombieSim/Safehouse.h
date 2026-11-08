#pragma once
#include "Survivor.h"
#include <vector>
#include <string>

// Safehouse
// The home base. Owns the shared resources (food, ammo, materials)
// and the survivor roster. Game asks it questions ("how many are
// alive?") and tells it when resources change; the Zombie class
// gets access to it during the nightly attack.
class Safehouse
{
public:
	void AddSurvivor(const std::string& name);   // add a survivor to the roster
	std::vector<Survivor>& GetSurvivors();       // roster by reference so Game can assign tasks
	int GetAliveCount() const;                   // how many survivors are still alive

	int GetFood() const;          // current food stock
	void AddFood(int amount);     // positive = gain, negative = spend

	int GetAmmo() const;          // current ammo stock
	void AddAmmo(int amount);     // spent by defenders, found by scavengers

	int GetMaterials() const;     // saved for future features (repairs, upgrades)
	void AddMaterials(int amount);

	void PrintStatus() const;     // the full status screen (menu option 1)

private:
	int mFood = 10;                      // starting food
	int mAmmo = 5;                       // starting ammo
	int mMaterials = 0;                  // starting materials
	std::vector<Survivor> mSurvivors;    // everyone living (and dead) in the safehouse
};