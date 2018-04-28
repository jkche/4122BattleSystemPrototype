#include "move.h"
#include <vector>

class Character {
public:
	int x;
	int y;
	int health;
	int maxhealth;
	int mana;
	int maxmana;
	vector<Move> defenseMoves;
	vector<Move> offenseMoves;
	Character();
};