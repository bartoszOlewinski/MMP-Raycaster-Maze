//
// Created by Bartosz Olewinski on 09/02/2022.
//

#ifndef RAYCASTER_ACTOR_H
#define RAYCASTER_ACTOR_H


#include <SFML/System/Time.hpp>
#include <string>
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include "Map.h"

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


    void setupStatsText(sf::Font *font, int posX, int posY);

    void setupPopupText(sf::Font *font, int posX, int posY);

    void setupEqText(sf::Font *font, int posX, int posY);
};


#endif //RAYCASTER_ACTOR_H
