#pragma once
#include <string>

// The three jobs a survivor can be assigned each day.
// enum class keeps the values scoped (Task::Scavenge, not bare Scavenge)
// so they cannot collide with other names.
enum class Task { Scavenge, Defend, Rest };

// Survivor
// One person living in the safehouse. Tracks their name, health,
// and today's task. Knows how to take damage and heal, but knows
// nothing about zombies or resources - Game and Safehouse decide
// when those things happen.
class Survivor
{
public:
	// Creates a survivor with a name; health defaults to 100
	// if no value is passed in.
	Survivor(const std::string& name, int health = 100);

	const std::string& GetName() const;  // name as a reference (no copy)
	int GetHealth() const;               // current HP, 0 means dead
	bool IsAlive() const;                // true while HP is above 0
	Task GetTask() const;                // today's assigned task
	std::string GetTaskName() const;     // task as readable text for status screens

	void SetTask(Task task);       // assign today's task
	void TakeDamage(int amount);   // subtract HP, clamps at 0 (never negative)
	void Heal(int amount);         // add HP (no maximum cap yet)

private:
	std::string mName;  // survivor's display name
	int mHealth;        // hit points; 0 = dead
	Task mTask;         // current daily assignment
};