//
// Created by Bartosz Olewinski on 09/03/2022.
//

#include "GameSetup.h"


void GameSetup::resetAttributes() {
    //reset actors
    player->time = sf::Time::Zero;
    agent->time = sf::Time::Zero;

    player->directionX = -1.0f;
    player->directionY = 0.0f;

    player->planeY = 0.66f;
    player->planeX = 0.0f;

    agent->directionX = -1.0f;
    agent->directionY = 0.0f;

    agent->planeX = 0.0f;
    agent->planeY = 0.66f;

    player->score = 0;
    agent->score = 0;

    player->hasFinished = false;
    agent->hasFinished = false;

    player->collectedKeys.clear();
    agent->collectedKeys.clear();


    player->loadedSpriteList.clear();
    agent->loadedSpriteList.clear();


}


void GameSetup::pickAndLoadMap(int mapId) {

    map->loadMapDetails(mapId);


    //clearing sprite lists for new contents
    player->loadedSpriteList.clear();
    agent->loadedSpriteList.clear();

    player->loadedSpriteList = map->spriteList;
    agent->loadedSpriteList = map->spriteList;

    //set up starting points
    player->positionX = map->startingPosX;
    player->positionY = map->startingPosY;

    agent->positionX = map->startingPosX;
    agent->positionY = map->startingPosY;


    //copy the mapObject to the raycaster
    for (int i = 0; i < Map::MAP_SIZE; i++) {
        for (int j = 0; j < Map::MAP_SIZE; j++) {

            player->mapInstance[i][j] = map->mapArray[i][j];
            agent->mapInstance[i][j] = map->mapArray[i][j];
        }
    }
}

void GameSetup::setUpAttributes(Map *mapObject, Actor *player, Actor *agent) {
    this->map = mapObject;
    this->player = player;
    this->agent = agent;
}
