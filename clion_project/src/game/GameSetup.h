//
// Created by Bartosz Olewinski on 09/03/2022.
//

#ifndef RAYCASTER_GAMESETUP_H
#define RAYCASTER_GAMESETUP_H


#include "Map.h"
#include "Actor.h"

/**
 * Class that handles some of setting up the game,
 * such as initial attributes, resetting attributes,
 * and loading maps
 */
class GameSetup {

public:
    /**
    * Sets up Map, Player and Agent objects for this class' private variables
    * @param mapObject map object
    * @param player player object
    * @param agent agent object
    */
    void setUpAttributes(Map* mapObject, Actor* player, Actor* agent);

    /**
    * Resets player's and agent's attributes
    */
    void resetAttributes();

    /**
    * Given an int number, loads a map and sets up its attributes
    * @param mapId int representing the map to load
    */
    void pickAndLoadMap(int mapId);

private:
    Map* map;
    Actor* player;
    Actor* agent;
};


#endif //RAYCASTER_GAMESETUP_H
