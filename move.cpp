#include "move.h"

Move::Move(string movename, int dmgVal, int cdVal) {
	name = movename;
	damage = dmgVal;
	cooldown = cdVal;
	currentCooldown = 0;
	isReady = true;
	moveUsed = false;
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
