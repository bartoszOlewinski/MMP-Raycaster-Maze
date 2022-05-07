//
// Created by Bartosz Olewinski on 09/02/2022.
//

#ifndef RAYCASTER_ACTOR_H
#define RAYCASTER_ACTOR_H


#include <SFML/System/Time.hpp>
#include <string>
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Map.h"


/**
 * Class that contains information about Player's or
 * Agent's objects such as:
 * positions, directions, scores, timers, equipment
 *
 * Also handles actor specific text displays
 *
 */
class Actor {
public:
    double positionX;
    double positionY;

    double directionX;
    double directionY;

    double planeX;
    double planeY;

    std::string name;

    int score;
    sf::Time time;

    std::vector<char> collectedKeys;

    bool hasFinished;


    int renderX;
    int renderY = 10;

    bool isCloseToDoor;
    int doorX;
    int doorY;

    sf::Text statsText;
    std::string timerString;
    std::string scoreString;

    sf::Text popupText;
    std::string popupString;

    sf::Text eqText;
    std::string eqString;

    std::vector<Sprite> loadedSpriteList;


    unsigned char mapInstance[Map::MAP_SIZE][Map::MAP_SIZE];


    /**
    * sets up timer and score display
    *
    * @param font font to be used by text object
    * @param posX position on the screen
    * @param posY position on the screen
    */
    void setupStatsText(sf::Font *font, int posX, int posY);

    /**
    * Sets up item pick up pop up text
    *
    * @param font font to be used by text object
    * @param posX position on the screen
    * @param posY position on the screen
    */
    void setupPopupText(sf::Font *font, int posX, int posY);

    /**
    * Sets up equipment display
    *
    * @param font font to be used by text object
    * @param posX position on the screen
    * @param posY position on the screen
    */
    void setupEqText(sf::Font *font, int posX, int posY);
};


#endif //RAYCASTER_ACTOR_H
