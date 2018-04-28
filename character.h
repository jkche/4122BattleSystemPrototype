#include "move.h"
#include "character.h"

class Character {
public:
	int x;
	int y;
	int health;
	int maxhealth;
	int mana;
	int maxmana;
	Move[] defenseMoves;
	Move[] offenseMoves;
	Character();
}