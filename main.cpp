//#define _GLIBCXX_USE_CXX11_ABI 0
#include <SFML/Graphics.hpp>
#include <cmath>

#define CHAR_SELECT_RADIUS 75
#define CIRCLE_MENU_RADIUS 100
#define CHAR_DESELECT_RADIUS 170
#define HP_BAR_OFFSET 10
#define HP_BAR_HEIGHT 15
#define MP_BAR_OFFSET 5
#define MP_BAR_HEIGHT 10

//#include "MoveMenu.h"
//#include <typeinfo>
//#include <string>
//#include <vector>

#include "character.h"
#include "FillBar.h"


float distanceFormula(float, float, float, float);
float distanceFormula2(float, float, float, float);
int isHoveringAlly(sf::Vector2i);
int isHoveringAlly2(int, sf::Vector2i);
int isHoveringEnemy(sf::Vector2i);
int isHoveringEnemy2(int, sf::Vector2i);
int isHoveringMove(MoveMenu &, sf::Vector2i);
void drawPiMenu(sf::CircleShape &, sf::Vector2f);

/*
0 - Ally 1
1 - Player
2 - Ally 2
*/
const int ally1Xpos = 320;
const int enemy1Xpos = 1480;
const int Xoffset = 70;
const int Ystart = 100;
const int Ygap = 250;

sf::Color HPFillColor(255,0,0,255);
sf::Color HPBackColor(100,0,0,255);
sf::Color MPFillColor(0,0,255,255);
sf::Color MPBackColor(0,0,100,255);

std::vector<Character> allyteam;
std::vector<Character> enemyteam;

std::vector<FillBar> HPBars;
std::vector<FillBar> MPBars;

sf::CircleShape playerHighlight;
sf::RectangleShape turnIndicator;

//sf::Font moveFont;
//moveFont.loadFromFile("arial.ttf");

int turn;
float deltaTime = 0.0f;
float frameSpeed = 7500.0f;
bool battlePaused = true;


int main() {
    sf::Clock clock;
    deltaTime = clock.restart().asSeconds();
//battle frame vars
    float attackTimer = 6.0f;
    float frameCounter = 0.0f;
	sf::RenderWindow window(sf::VideoMode(1920,1080), "Lonely Blade", sf::Style::Close | sf::Style::Resize);

    //Disable key repeat for mouse clicks
    window.setKeyRepeatEnabled(false);


    sf::Texture sword1;
    sword1.loadFromFile("sword.png");
    sf::Texture sword2;
    sword2.loadFromFile("sword2.png");


    std::vector<Move> ally1DefMoves;
    //Move 1
    ally1DefMoves.clear();
    //std::cout << ally1DefMoves.size() << std::endl;
    ally1DefMoves.push_back(Move("Shout", 10, 2, "Buff", "Cast"));
    ally1DefMoves.push_back(Move("Heal", 10, 5, "Heal", "Cast"));
    for (int i = 0; i < 8; ++i) {
    	ally1DefMoves.push_back(Move());
    }
    //std::cout << ally1DefMoves.size() << std::endl;
    std::vector<Move> ally1OffMoves;
    ally1OffMoves.clear();
    ally1OffMoves.push_back(Move("Slash", 10, 1, "Attack", "Swing", &sword1, &sword2));
    ally1OffMoves.push_back(Move("Boomerang Blade", 50, 4, "Attack", "Cast"));
    for (int i = 0; i < 8; ++i) {
    	ally1OffMoves.push_back(Move());
    }


    //DUMMY TEXTURE FOR TESTING
    sf::Texture textureTest;
    textureTest.loadFromFile("player.png");

    //DUMMY CHAR FOR ALLY/ENEMY INIT
    Character dummyChar(true,&textureTest);

    //set party number for specific member turn check--useful for member and target select
    allyteam.push_back(Character(ally1Xpos, Ystart, 100, 100, ally1DefMoves, ally1OffMoves, &textureTest, sf::Vector2u(3,4), 0.3f, 100.0f, &dummyChar));
    allyteam.back().setPartyNumber(allyteam.size()-1);
    allyteam.push_back(Character(ally1Xpos + Xoffset, Ystart + Ygap, 100, 100, ally1DefMoves, ally1OffMoves, &textureTest, sf::Vector2u(3,4), 0.3f, 100.0f, &dummyChar));
    allyteam.back().setPartyNumber(allyteam.size()-1);
    allyteam.push_back(Character(ally1Xpos, Ystart + 2 * Ygap, 100, 100, ally1DefMoves, ally1OffMoves, &textureTest, sf::Vector2u(3,4), 0.3f, 100.0f, &dummyChar));
    allyteam.back().setPartyNumber(allyteam.size()-1);
    
    std::vector<MoveMenu> defMenus;
    std::vector<MoveMenu> offMenus;

    turn = 0;
    int allySelect = -1;
    int enemySelect = -1;
    int moveSelect = -1;

    for (int i = 0; i < allyteam.size(); ++i) {
		HPBars.push_back(FillBar(allyteam[i].x, allyteam[i].y + allyteam[i].height + HP_BAR_OFFSET, 100, HP_BAR_HEIGHT, HPFillColor, HPBackColor, 0));
		MPBars.push_back(FillBar(allyteam[i].x, allyteam[i].y + allyteam[i].height + HP_BAR_OFFSET + HP_BAR_HEIGHT + MP_BAR_OFFSET, 100, MP_BAR_HEIGHT, MPFillColor, MPBackColor, 0));
		defMenus.push_back(MoveMenu(-1000.0f, -1000.0f, CIRCLE_MENU_RADIUS, allyteam[i].defenseMoves));
		offMenus.push_back(MoveMenu(-1000.0f, -1000.0f, CIRCLE_MENU_RADIUS, allyteam[i].offenseMoves));
	}
	

    std::vector<Move> enemy1DefMoves;
    std::vector<Move> enemy1OffMoves;
    enemyteam.push_back(Character(enemy1Xpos, Ystart, 100, 100, enemy1DefMoves, enemy1OffMoves, &textureTest, sf::Vector2u(3,4), 0.3f, 100.0f, &dummyChar));
    enemyteam.back().setPartyNumber(enemyteam.size()-1);
    enemyteam.push_back(Character(enemy1Xpos - Xoffset, Ystart + Ygap, 100, 100, enemy1DefMoves, enemy1OffMoves, &textureTest, sf::Vector2u(3,4), 0.3f, 100.0f, &dummyChar));
    enemyteam.back().setPartyNumber(enemyteam.size()-1);
    enemyteam.push_back(Character(enemy1Xpos, Ystart + 2 * Ygap, 100, 100, enemy1DefMoves, enemy1OffMoves, &textureTest, sf::Vector2u(3,4), 0.3f, 100.0f, &dummyChar));
    enemyteam.back().setPartyNumber(enemyteam.size()-1);

    for (int i = 0; i < enemyteam.size(); ++i) {
		HPBars.push_back(FillBar(enemyteam[i].x, enemyteam[i].y + enemyteam[i].height + HP_BAR_OFFSET, 100, HP_BAR_HEIGHT, HPFillColor, HPBackColor, 0));
		MPBars.push_back(FillBar(enemyteam[i].x, enemyteam[i].y + enemyteam[i].height + HP_BAR_OFFSET + HP_BAR_HEIGHT + MP_BAR_OFFSET, 100, MP_BAR_HEIGHT, MPFillColor, MPBackColor, 0));
	}

    playerHighlight.setRadius(35.0f);
    playerHighlight.setPosition(-100.0f, -100.0f);
    playerHighlight.setFillColor(sf::Color::Transparent);
    playerHighlight.setOutlineColor(sf::Color::Yellow);
    playerHighlight.setOutlineThickness(2.0f);

    turnIndicator.setFillColor(sf::Color::Green);
    turnIndicator.setSize(sf::Vector2f(10.0f, 10.0f));

    while (allyteam[turn].alive == false) {
    	turn++;
    }

    while(window.isOpen())
    {
    	//cout << (hpbar.foreground).getSize() << endl;
        sf::Event evnt;
        while(window.pollEvent(evnt)){
            switch(evnt.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:

                    //NEW TURN DETERMINATION START
                    if(battlePaused && turn < 6) {   //move being selected
                        if (turn < 3) {   //ally making move
                            for(int i = 0; i < allyteam.size(); ++i){
                                allyteam[i].isSelect = false;
                            }
                            allyteam[turn].isSelect = true;
                            if(enemySelect > -1 && moveSelect > -1){    //target enemy; use offensive moves
                                allyteam[turn].setTarget(&enemyteam[enemySelect],moveSelect,ally1OffMoves);
                                battlePaused = false;
                                printf("\nBattle unpaused; player attacking\n");
                            }else if(allySelect > -1 && moveSelect > -1){   //target ally; use defensive moves
                                allyteam[turn].setTarget(&allyteam[allySelect],moveSelect,ally1DefMoves);
                                battlePaused = false;
                                printf("\nBattle unpaused; player defending\n");
                            }
                        }
                        else{               //enemy making move
                            for(int i = 0; i < enemyteam.size(); ++i){
                                enemyteam[i].isSelect = false;
                            }
                            enemyteam[turn].isSelect = true;
                            if(enemySelect > -1 && moveSelect > -1){    //target enemy; use defensive moves
                                enemyteam[turn].setTarget(&enemyteam[enemySelect],moveSelect,enemy1DefMoves);
                                battlePaused = false;
                                printf("\nBattle unpaused; enemy attacking\n");
                            }else if(allySelect > -1 && moveSelect > -1){   //target ally; use offensive moves
                                enemyteam[turn].setTarget(&allyteam[allySelect],moveSelect,enemy1OffMoves);
                                battlePaused = false;
                                printf("\nBattle unpaused; enemy defending\n");
                            }

                        }

                    }
                    //NEW TURN DETERMINATION END
//
//                    //OLD TURN DETERMINATION START
//                    if (battlePaused && turn < 3) {
//                        if(allySelect > -1) {                 //ally selection paths
//                            if (allyteam[allySelect].isSelect && moveSelect > -1 && enemySelect > -1) {
//                                if (!enemyteam[enemySelect].isSelect) {   //ally has chosen move, targets enemy
//                                    allyteam[allySelect].setTarget(&enemyteam[enemySelect]);
//                                    printf("\nAlly selected target\n");
//                                }
//                            } else if (!allyteam[allySelect].isSelect && enemySelect <= -1) {   //ally selected
//                                allyteam[allySelect].isSelect = true;
//                                printf("\nAlly selected\n");
//                            }
//                        }else if(enemySelect > -1) {                 //enemy selection paths
//                            if (enemyteam[enemySelect].isSelect && moveSelect > -1 && allySelect > -1) {     //enemy has chosen move, targets ally
//                                if (!allyteam[allySelect].isSelect)   //enemy targets ally
//                                    enemyteam[enemySelect].setTarget(&allyteam[allySelect]);
//                            } else if (!enemyteam[enemySelect].isSelect && allySelect <= -1) {   //enemy selected
//                                enemyteam[enemySelect].isSelect = true;
//                            }
//                        }
//                        if (allySelect > -1 || enemySelect > -1) {
//                            if (moveSelect > -1) {
//                                battlePaused = false;
//                            }
//                        }
//                    }
//                    //OLD TURN DETERMINATION END


                    break;
            }
        }
        if (battlePaused) {
            if (turn < 3) {
                turnIndicator.setPosition(allyteam[turn].x + allyteam[turn].width / 2 - 5, allyteam[turn].y - 20);
            } else {
                turnIndicator.setPosition(enemyteam[turn - 3].x + enemyteam[turn - 3].width / 2 - 5,
                                          enemyteam[turn - 3].y - 20);
            }


            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (allySelect > -1) {
                allySelect = isHoveringAlly2(allySelect, mousePos);
            }
            if (enemySelect > -1) {
                enemySelect = isHoveringEnemy2(enemySelect, mousePos);
            }
            if (allySelect == -1 && enemySelect == -1) {
                allySelect = isHoveringAlly(mousePos);
                enemySelect = isHoveringEnemy(mousePos);
            }
            moveSelect = -1;
            float circleCenterX = -1000.0f;
            float circleCenterY = -1000.0f;
            if (allySelect > -1) {
                circleCenterX = allyteam[allySelect].x + allyteam[allySelect].width / 2 - playerHighlight.getRadius();
                circleCenterY = allyteam[allySelect].y + allyteam[allySelect].height / 2 - playerHighlight.getRadius();
                defMenus[turn].setMenuPosition(sf::Vector2f(circleCenterX, circleCenterY));
                offMenus[turn].setMenuPosition(sf::Vector2f(-1000.0f, -1000.0f));
                moveSelect = isHoveringMove(defMenus[turn], mousePos);
            } else if (enemySelect > -1) {
                circleCenterX =
                        enemyteam[enemySelect].x + enemyteam[enemySelect].width / 2 - playerHighlight.getRadius();
                circleCenterY =
                        enemyteam[enemySelect].y + enemyteam[enemySelect].height / 2 - playerHighlight.getRadius();
                offMenus[turn].setMenuPosition(sf::Vector2f(circleCenterX, circleCenterY));
                defMenus[turn].setMenuPosition(sf::Vector2f(-1000.0f, -1000.0f));
                moveSelect = isHoveringMove(offMenus[turn], mousePos);
            } else {
                defMenus[turn].setMenuPosition(sf::Vector2f(-1000.0f, -1000.0f));
                offMenus[turn].setMenuPosition(sf::Vector2f(-1000.0f, -1000.0f));
            }
            playerHighlight.setPosition(circleCenterX, circleCenterY);
        }
        window.clear();
        if(!battlePaused){
            defMenus[turn].setMenuPosition(sf::Vector2f(-1000.0f, -1000.0f));
            offMenus[turn].setMenuPosition(sf::Vector2f(-1000.0f, -1000.0f));

            playerHighlight.setPosition(-1000.0f, -1000.0f);
        }
        for (int i = 0; i < allyteam.size(); ++i) {
            if (allyteam[i].alive) {
//    	        	window.draw(allyteam[i].drawing);
                allyteam[i].movementUpdate(deltaTime*frameSpeed,attackTimer, &frameCounter, &battlePaused);
                allyteam[i].draw(window);
                HPBars[i].amount = allyteam[i].health/allyteam[i].maxhealth;
                HPBars[i].update();
                window.draw(HPBars[i].background);
                window.draw(HPBars[i].foreground);
                MPBars[i].amount = allyteam[i].mana/allyteam[i].maxmana;
                MPBars[i].update();
                window.draw(MPBars[i].background);
                window.draw(MPBars[i].foreground);
            }
        }
        for (int i = 0; i < enemyteam.size(); ++i) {
            if (enemyteam[i].alive) {
//	        	window.draw(enemyteam[i].drawing);
                enemyteam[i].movementUpdate(deltaTime*frameSpeed,attackTimer, &frameCounter, &battlePaused);
                enemyteam[i].draw(window);
                HPBars[i + allyteam.size()].amount = enemyteam[i].health/enemyteam[i].maxhealth;
                HPBars[i + allyteam.size()].update();
                window.draw(HPBars[i + allyteam.size()].background);
                window.draw(HPBars[i + allyteam.size()].foreground);
                MPBars[i + allyteam.size()].amount = enemyteam[i].mana/enemyteam[i].maxmana;
                MPBars[i + allyteam.size()].update();
                window.draw(MPBars[i + allyteam.size()].background);
                window.draw(MPBars[i + allyteam.size()].foreground);
            }
        }
        for (int i = 0; i < 8; ++i) {
            window.draw(offMenus[turn].piMenu[i].getAppearance());
            window.draw(defMenus[turn].piMenu[i].getAppearance());
        }
        window.draw(turnIndicator);
        window.draw(playerHighlight);
        window.display();
//        } else {
//
//        }
    }

    return 0;
}

//calculate distance for circle and hovering calculations
float distanceFormula(float x1, float x2, float y1, float y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

float distanceFormula2(float x1, float x2, float y1, float y2){
    return (pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

float vecDistanceFormula2(sf::Vector2f p1, sf::Vector2f p2) {
	return distanceFormula2(p1.x, p2.x, p1.y, p2.y);
}

int isHoveringAlly(sf::Vector2i mousePos) {
	sf::Vector2f mousePosF(mousePos.x, mousePos.y);
	for (int i = 0; i < allyteam.size(); ++i) {
		if (allyteam[i].alive) {
			sf::Vector2f allyPosF(allyteam[i].x + allyteam[i].width/2, allyteam[i].y + allyteam[i].height/2);
			if (vecDistanceFormula2(mousePosF, allyPosF) < CHAR_SELECT_RADIUS * CHAR_SELECT_RADIUS) {
				return i;
			}
		}
		
	}
	return -1;
}

int isHoveringAlly2(int allySelected, sf::Vector2i mousePos) {
	sf::Vector2f mousePosF(mousePos.x, mousePos.y);
	sf::Vector2f allyPosF(allyteam[allySelected].x + allyteam[allySelected].width/2, allyteam[allySelected].y + allyteam[allySelected].height/2);
	if (vecDistanceFormula2(mousePosF, allyPosF) < CHAR_DESELECT_RADIUS * CHAR_DESELECT_RADIUS) {
		return allySelected;
	}
	return -1;
}

int isHoveringEnemy(sf::Vector2i mousePos) {
	sf::Vector2f mousePosF(mousePos.x, mousePos.y);
	for (int i = 0; i < enemyteam.size(); ++i) {
		if (enemyteam[i].alive) {
			sf::Vector2f enemyPosF(enemyteam[i].x + enemyteam[i].width/2, enemyteam[i].y + enemyteam[i].height/2);
			if (vecDistanceFormula2(mousePosF, enemyPosF) < CHAR_SELECT_RADIUS * CHAR_SELECT_RADIUS) {
				return i;
			}
		}
	}
	return -1;
}

int isHoveringEnemy2(int enemySelected, sf::Vector2i mousePos) {
	sf::Vector2f mousePosF(mousePos.x, mousePos.y);
	sf::Vector2f enemyPosF(enemyteam[enemySelected].x + enemyteam[enemySelected].width/2, enemyteam[enemySelected].y + enemyteam[enemySelected].height/2);
	if (vecDistanceFormula2(mousePosF, enemyPosF) < CHAR_DESELECT_RADIUS * CHAR_DESELECT_RADIUS) {
		return enemySelected;
	}
	return -1;
}

int isHoveringMove(MoveMenu &menu, sf::Vector2i mousePos) {
	int returnVal = -1;
	sf::Vector2f mousePosF(mousePos.x, mousePos.y);
	for (int i = 0; i < 8; ++i) {
		menu.piMenu[i].unhighlight();
		if (menu.piMenu[i].active == true && vecDistanceFormula2(mousePosF, menu.piMenu[i].getCenter()) < menu.piMenu[i].radius * menu.piMenu[i].radius) {
			menu.piMenu[i].highlight();
			returnVal = i;
		}
	}
	return returnVal;
}

void drawPiMenu(sf::CircleShape & enemyCircle, sf::Vector2f enemyPos){
    enemyCircle.setPosition(enemyPos.x - enemyCircle.getRadius(), enemyPos.y - enemyCircle.getRadius());
}