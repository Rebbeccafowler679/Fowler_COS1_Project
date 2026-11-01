#pragma once
#include <string>

// The three jobs a survivor can be assigned each day.
enum class Task { Scavenge, Defend, Rest };

class Survivor
{
public:
	Survivor(const std::string& name, int health = 100);

	const std::string& GetName() const;
	int GetHealth() const;
	bool IsAlive() const;
	Task GetTask() const;

	void SetTask(Task task);
	void TakeDamage(int amount);
	void Heal(int amount);

private:
	std::string mName;
	int mHealth;
	Task mTask;
};
