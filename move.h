#include <string>

using namespace std;

class Move {
public:
	string name;
	int damage;
	int cost;
	int cooldown;
	int currentCooldown;
	bool isReady;
	bool moveUsed;
	Move(string movename, int dmgVal, int cdVal);
	void update();
};