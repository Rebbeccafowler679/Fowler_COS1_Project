#pragma once

class Safehouse; // forward declaration — we only need the name here

// Models one night's zombie horde.
// Lives on the stack: created during day resolution, gone right after.
// (See prototype.md, Design Decisions.)
class Zombie
{
public:
	explicit Zombie(int day); // horde size scales with the day number

	int GetHordeSize() const;

	// Resolves the night's attack against the safehouse:
	// defenders repel zombies (costs ammo), the rest deal damage.
	void Attack(Safehouse& safehouse) const;

private:
	int mHordeSize;
};