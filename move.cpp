#include "move.h"

Move::Move() {
	exists = false;
}
Move::Move(sf::Text movename, int type, int amount, int cd) {
	//name = movename;
	exists = false;
}
// Unused
Move::Move(std::string movename, int dmgVal, int cdVal) {
	//name = movename;
	//damage = dmgVal;
	//cooldown = cdVal;
	//currentCooldown = 0;
	//isReady = true;
	//moveUsed = false;
	exists = false;
}
void Move::update() {
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
