//
// Created by Bartosz Olewinski on 09/02/2022.
//

#ifndef RAYCASTER_ACTOR_H
#define RAYCASTER_ACTOR_H


class Actor {
public:
    double positionX;
    double positionY;

    double directionX;
    double directionY;

    double planeX;
    double planeY;

    int score;
    double time;

    bool hasWon = false;
};


#endif //RAYCASTER_ACTOR_H
