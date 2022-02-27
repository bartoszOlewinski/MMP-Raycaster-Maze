//
// Created by barto on 21/02/2022.
//

#include "Map.h"

//#define MAP testMap
#define MAP testMap01


void Map::loadMapDetails() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {


#if MAP == testMap
            mapArray[i][j] = testMap[i][j];
#endif

#if MAP == testMap01
            mapArray[i][j] = map01[i][j];
#endif



            // + 0.5f to move the positions into center of the cell they occupy
            if (mapArray[i][j] == '#') {
                Map::startingPosX = (float)i + 0.5f;
                Map::startingPosY = (float)j + 0.5f;

            } else if (mapArray[i][j] == '!') {
                Map::numOfSprites++;

                Sprite tempSprite{};
                tempSprite.posX = (float)i + 0.5f;
                tempSprite.posY = (float)j + 0.5f;
                tempSprite.textureChar = '!';

                spriteList.push_back(tempSprite);
            }
            // FURTHER ELSE IF FOR OTHER TYPES OF ITEMS

        }
    }
}
