#include "Survivor.h"

Survivor::Survivor(const std::string& name, int health)
	: mName(name), mHealth(health), mTask(Task::Rest)
{
}

const std::string& Survivor::GetName() const { return mName; }
int Survivor::GetHealth() const { return mHealth; }
bool Survivor::IsAlive() const { return mHealth > 0; }
Task Survivor::GetTask() const { return mTask; }

void Survivor::SetTask(Task task) { mTask = task; }

void Survivor::TakeDamage(int amount)
{
	mHealth -= amount;
	if (mHealth < 0) { mHealth = 0; }	// never below 0
}

void Survivor::Heal(int amount)
{
	mHealth += amount;	// no max health cap
}