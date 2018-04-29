#include <string>

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
	Move(std::string, int, int);
	void update();
};