//
// Created by justi_000 on 4/28/2018.
//

#include <cmath>
#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    row = 0;
    faceRight = true;

    body.setSize(sf::Vector2f(100.0f,100.0f));
    body.setPosition(100.0f,100.0f);
    body.setTexture(texture);
    //Uncomment below for testing center
    body.setOrigin(50.0f, 50.0f);
}

void Player::update(float deltaTime, sf::Vector2f enemyPos, sf::Vector2f origPos, bool isAttack){
//    sf::Vector2f movement(0.0f, 0.0f);

    velocity.x = 0.0f;
    velocity.y = 0.0f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocity.x -= speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocity.x += speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        velocity.y -= speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        velocity.y += speed;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        velocity.y = -sqrt(2.0f*981.0f*200);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
//        float slope =
    }



    if(velocity.x == 0.0f){
        row = 0;
        moving = false;
    }
    else{
        moving = true;
        row = 2;
        if(velocity.x > 0.0f)
            faceRight = true;
        else
            faceRight = false;
    }
    animation.update(row, deltaTime, faceRight, faceTop, moving);
    body.setTextureRect(animation.uvRect);
    body.move(velocity*deltaTime);
}

void Player::updateAttack(float deltaTime, sf::Vector2f enemyPos, bool isAttack, float attackTimer, float moveTime){   //total animation time ~ 25 deltaTimes
    bool moving;
    float xVel = (enemyPos.x - origPos.x)/(moveTime); //moving forward and back takes x seconds
    if(enemyPos.x -100 > getPosition().x && isAttack) {
        moving = true;
        float slope = (enemyPos.y - getPosition().y) / (enemyPos.x - getPosition().x);
        velocity.x = xVel;
        velocity.y = slope * velocity.x;
    }else if(isAttack){ //Animation takes 5 deltaTimes
        moving = false;
        velocity.x = 0.0f;
        velocity.y = 0.0f;
    }else if(!isAttack && getPosition().x > origPos.x){
        moving = true;
        float slope = (enemyPos.y - getPosition().y) / (enemyPos.x - getPosition().x);
        velocity.x = -xVel;
        velocity.y = slope * velocity.x;
    }else if(!isAttack && getPosition().x <= origPos.x){
        moving = false;
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        body.setPosition(origPos);
    }
    animation.updateAttack(deltaTime, isAttack, moving, attackTimer/2 - moveTime);
    body.setTextureRect(animation.uvRect);
    body.move(velocity*deltaTime);
}

void Player::draw(sf::RenderWindow& window){
    window.draw(body);
}

sf::Vector2f Player::getPosition(){
    return body.getPosition();
}

sf::Vector2f Player::getSize(){
    return body.getSize();
}
//Use on-click
void Player::setOrigPos(sf::Vector2f coords){
    origPos = coords;
}

sf::Vector2f Player::getOrigPos() {
    return origPos;
}

void Player::initAttack() {
    animation.attackAnimationFill();
}

//2:57