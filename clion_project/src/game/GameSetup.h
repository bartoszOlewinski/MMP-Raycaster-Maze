//
// Created by Bartosz Olewinski on 09/03/2022.
//

#ifndef RAYCASTER_GAMESETUP_H
#define RAYCASTER_GAMESETUP_H


#include "Map.h"
#include "Actor.h"

class GameSetup {

public:
    void setUpAttriubutes(Map* mapObject, Actor* player, Actor* agent);

    void resetAttributes();

    void pickAndLoadMap();

private:
    Map* map;
    Actor* player;
    Actor* agent;
};


#endif //RAYCASTER_GAMESETUP_H
