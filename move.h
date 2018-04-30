#include <string>
#include <SFML/Graphics.hpp>

class Move {
public:
	std::string name;
	int damage;
	int cost;
	int cooldown;
	int currentCooldown;
	bool isReady;
	bool moveUsed;
	bool exists;
	Move();
	Move(sf::Text, int, int, int);
	Move(std::string, int, int);
	void update();
};