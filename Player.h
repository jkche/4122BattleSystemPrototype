//
// Created by justi_000 on 4/28/2018.
//

#ifndef SFMLDEMO_PLAYER_H
#define SFMLDEMO_PLAYER_H


#include <SFML/Graphics.hpp>
#include "Animation.h"

class Player {
public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);

    void update(float deltaTime, sf::Vector2f enemyPos, sf::Vector2f origPos, bool isAttack);
    void draw(sf::RenderWindow& window);
    void updateAttack(float deltaTime, sf::Vector2f enemyPos, bool isAttack, float attackTimer, float moveTime);
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    void setOrigPos(sf::Vector2f coords);
    sf::Vector2f getOrigPos();
    void initAttack();

private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
    bool faceTop;
    bool moving;

    sf::Vector2f velocity;
    sf::Vector2f origPos;
};


#endif //SFMLDEMO_PLAYER_H
