//
// Created by barto on 21/02/2022.
//

#include "Map.h"

#define MAP testMap


void Map::loadMapDetails() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {


#if MAP == testMap
            mapArray[i][j] = testMap[i][j];
#endif



            if (mapArray[i][j] == '#') {
                Map::startingPosX = i;
                Map::startingPosY = j;

            } else if (mapArray[i][j] == '!') {
                Map::numOfSprites++;

                Sprite tempSprite{};
                tempSprite.posX = i;
                tempSprite.posY = j;
                tempSprite.textureChar = '!';

                spriteList.push_back(tempSprite);
            }
            // FURTHER ELSE IF FOR OTHER TYPES OF ITEMS

        }
    }
}
