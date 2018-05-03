#include "character.h"
Character::Character(bool dead, sf::Texture *texture):
    animation(texture, sf::Vector2u(0,0),0.0f) {
    alive = selected = faceRight = faceTop = moving = isSelect = isSelected = false;
    health = maxhealth = mana = maxmana = attackTimer = speed = 0.0f;
    x = y = row = 0;

}

Character::Character(int posx, int posy, float hp, float mp, std::vector<Move> dMoves, std::vector<Move> oMoves, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
animation(texture, imageCount, switchTime)
{
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
	// drawing.setFillColor(sf::Color::Cyan);



	//additional variable settings from Player.cpp
    this->speed = speed;
    row = 0;
    faceRight = true;
    // drawing.setSize(sf::Vector2f(100.0f,100.0f));
    // drawing.setPosition(100.0f,100.0f);
     drawing.setTexture(texture);
//    drawing.setOrigin(50.0f, 50.0f);
//    nameOfSpriteSheet = name;

    //init battle targeting vars
    isSelect = false;
    isSelected = false;
}

//void Character::initTexture(sf::Texture* texture){
//	drawing.setTexture(texture);
//	animation.initSize(texture);
//}

//For movement on a map; may not need
void Character::update(float deltaTime, sf::Vector2f enemyPos, sf::Vector2f origPos, bool isAttack){
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

    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
    //     velocity.y = -sqrt(2.0f*981.0f*200);
    // }
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

    //animation and movement
    animation.update(row, deltaTime, faceRight, faceTop, moving);
    drawing.setTextureRect(animation.uvRect);
    drawing.move(velocity*deltaTime);
}

//For movement and animation in battle
void Character::updateAttack(float deltaTime, sf::Vector2f enemyPos, bool isAttack, float attackTimer, float moveTime){   //total animation time ~ 25 deltaTimes
    bool moving;	//indicates if char is moving across battle screen (to or from an enemy)
    float xVel = (enemyPos.x - origPos.x)/(moveTime); //moving forward and back takes moveTime seconds
    if(enemyPos.x -100 > getPosition().x && isAttack) {	//Char is moving to target
        moving = true;
        float slope = (enemyPos.y - getPosition().y) / (enemyPos.x - getPosition().x);
        velocity.x = xVel;
        velocity.y = slope * velocity.x;
    }else if(isAttack){ //char attack animation; stays in front of enemy
        moving = false;
        velocity.x = 0.0f;
        velocity.y = 0.0f;
    }else if(getPosition().x > origPos.x){	//char is finished attacking; moving back to original position
        moving = true;
        float slope = (enemyPos.y - getPosition().y) / (enemyPos.x - getPosition().x);
        velocity.x = -xVel;
        velocity.y = slope * velocity.x;
    }else{	//reset char to original position
        moving = false;
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        drawing.setPosition(origPos);
    }

    //animation and movement
    animation.updateAttack(deltaTime, isAttack, moving, attackTimer/2 - moveTime);
    drawing.setTextureRect(animation.uvRect);
    drawing.move(velocity*deltaTime);
}

//Draw char to window
void Character::draw(sf::RenderWindow& window){
    window.draw(drawing);
}


sf::Vector2f Character::getPosition(){
    return drawing.getPosition();
}


sf::Vector2f Character::getSize(){
    return drawing.getSize();
}


//Use on-click
void Character::setOrigPos(sf::Vector2f coords){
    origPos = coords;
}


sf::Vector2f Character::getOrigPos() {
    return origPos;
}

//Pushes animation sprites onto animation vector; see Animation.h
void Character::initAttack() {  //TO DO: Update to fill with move-specific animations
    animation.attackAnimationFill();
}

void Character::setPartyNumber(int num) {
    partyNum = num;
}

void Character::movementUpdate(float deltaTime, float attackTimer, float* frameCounter){    //TO DO: Update to check for move selected; change animation based on move
    if(isSelect && target->isSelected) { //attack initiated
        isSelect = false;
        target->isSelected = false;
        printf("\nAttack initiated\n");
        isAttacking = true;
    }
    if(*frameCounter < attackTimer && isAttacking){
        *frameCounter += deltaTime;
        updateAttack(deltaTime, target->getPosition(), *frameCounter < attackTimer / 2, attackTimer, 1);
    }else if(isAttacking){
        *frameCounter -= attackTimer;
        isAttacking = false;
    }else {
        update(deltaTime, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), false);
    }
}

int Character::getPartyNum() {
    return partyNum;
}

void Character::setTarget(Character *target) {  //POSSIBLE TO DO: Update to handle move-specific animations
    this->target = target;
    target->isSelected = true;
    initAttack();
}