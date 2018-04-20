#include <string>

using namespace std;

class Move {
	public:
	string name;
	int damage;
	int cooldown;
	int currentCooldown;
	bool isReady;
	bool moveUsed;
	Move(string movename, int dmgVal, int cdVal) {
		name = movename;
		damage = dmgVal;
		cooldown = cdVal;
		currentCooldown = 0;
		isReady = true;
		moveUsed = false;
	}
	void update() {
		if (!isReady && currentCooldown > 0) {
			currentCooldown--;
		}
		if (moveUsed) {
			isReady = false;
			currentCooldown = cooldown;
		}
		if (currentCooldown == 0) {
			isReady = true;
		}
	}


}