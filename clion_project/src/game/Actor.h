//
// Created by Bartosz Olewinski on 09/02/2022.
//

#ifndef RAYCASTER_ACTOR_H
#define RAYCASTER_ACTOR_H


#include <SFML/System/Time.hpp>
#include <string>
#include <vector>

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
};


#endif //RAYCASTER_ACTOR_H
