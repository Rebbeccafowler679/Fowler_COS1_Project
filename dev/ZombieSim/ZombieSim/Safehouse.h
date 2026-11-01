#pragma once
#pragma once
#include "Survivor.h"
#include <vector>
#include <string>

class Safehouse
{
public:
	void AddSurvivor(const std::string& name);

	std::vector<Survivor>& GetSurvivors();

	int GetFood() const;
	void AddFood(int amount);

	void PrintStatus() const;

private:
	int mFood = 10;
	int mAmmo = 5;
	int mMaterials = 0;
	std::vector<Survivor> mSurvivors;
};