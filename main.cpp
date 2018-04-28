#include <SFML/Graphics.hpp>
#include <cmath>
#include "move.h"
#include "character.h"

Character player;

float distanceFormula(float, float, float, float);
bool isHoveringEnemy(sf::RenderWindow &, sf::Vector2i, sf::Vector2f, float);
void drawPiMenu(sf::CircleShape &, sf::Vector2f);

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Battle System 0.0.1", sf::Style::Close);

	window.setKeyRepeatEnabled(false);
	player = new Character(0, 0, 100, 100, NULL, NULL);

	while (window.isOpen()) {
		window.clear();
		window.display();
	}

	return 0;
}

//calculate distance for circle and hovering calculations
float distanceFormula(float x1, float x2, float y1, float y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool isHoveringEnemy(sf::RenderWindow & win, sf::Vector2i mousePos, sf::Vector2f enemyPos, float radius){
    if(distanceFormula(mousePos.x, enemyPos.x, mousePos.y, enemyPos.y) < radius)
        return true;
    else
        return false;
}

void drawPiMenu(sf::CircleShape & enemyCircle, sf::Vector2f enemyPos){
    enemyCircle.setPosition(enemyPos.x - enemyCircle.getRadius(), enemyPos.y - enemyCircle.getRadius());
}