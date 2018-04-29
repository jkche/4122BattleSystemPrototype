#include "move.h"
#include <vector>

class Character {
public:
	bool alive;
	int x;
	int y;
	static const float width = 100.0f;
	static const float height = 100.0f;
	float health;
	float maxhealth;
	float mana;
	float maxmana;

	sf::RectangleShape drawing;

	vector<Move> defenseMoves;
	vector<Move> offenseMoves;
	Character(bool dead) {
		alive = false;
	}
	Character(int posx, int posy, float hp, float mp, std::vector<Move> dMoves, std::vector<Move> oMoves) {
		alive = true;
		x = posx;
		y = posy;
		health = hp;
		maxhealth = hp;
		mana = mp;
		maxmana = mp;
		defenseMoves = dMoves;
		offenseMoves = oMoves;

		drawing.setPosition(x, y);
		drawing.setSize(sf::Vector2f(width, height));
		drawing.setFillColor(sf::Color::Cyan);
	}
};