#include "Survivor.h"

// Constructor: sets the name and health (defaults to 100 from the header).
// The starting health is remembered as mMaxHealth, so healing can
// never push a survivor above the HP they started with.
// New survivors start on Rest so an unassigned survivor never
// accidentally fights or scavenges.
Survivor::Survivor(const std::string& name, int health)
	: mName(name), mHealth(health), mMaxHealth(health), mTask(Task::Rest)
{
}

// Basic getters. GetName returns a reference to avoid copying the string.
const std::string& Survivor::GetName() const { return mName; }
int Survivor::GetHealth() const { return mHealth; }

// Alive means any health above zero. 0 HP = dead.
bool Survivor::IsAlive() const { return mHealth > 0; }
Task Survivor::GetTask() const { return mTask; }

// Assigns the daily task (Scavenge, Defend, or Rest).
void Survivor::SetTask(Task task) { mTask = task; }

// Subtracts damage and clamps health at 0 so it never goes negative.
// IsAlive() returning false is what marks the survivor as dead.
void Survivor::TakeDamage(int amount)
{
	mHealth -= amount;
	if (mHealth < 0) { mHealth = 0; }	// never below 0
}

// Rest healing. Clamps at mMaxHealth so survivors cannot heal
// past their starting health - this keeps the horde scaling
// meaningful over a long game.
void Survivor::Heal(int amount)
{
	mHealth += amount;
	if (mHealth > mMaxHealth) { mHealth = mMaxHealth; }	// never above max
}

// Converts the Task enum to readable text for status screens.
// (This is the function whose missing body caused the LNK2019
// linker error - the header promised it, now the body exists.)
std::string Survivor::GetTaskName() const
{
	switch (mTask)
	{
	case Task::Scavenge: return "Scavenge";
	case Task::Defend:   return "Defend";
	case Task::Rest:     return "Rest";
	}
	return "Unknown"; // fallback, should never happen with a valid Task
}