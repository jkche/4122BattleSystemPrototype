#include "move.h"
#include "character.h"

class Character {
public:
	
	Character(int posx, int posy, int hp, int mp, Move[] dMoves, Move[] oMoves) {
		x = posx;
		y = posy;
		health = hp;
		maxhealth = hp;
		mana = mp;
		maxmana = mp;
		defenseMoves = dMoves;
		offenseMoves = oMoves;
	}


}