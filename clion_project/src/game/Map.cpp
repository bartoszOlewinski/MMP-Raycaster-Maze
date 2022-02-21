//
// Created by barto on 21/02/2022.
//

#include "Map.h"

void Map::loadMapDetails() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {

            if (mapArray[i][j] == '#') {
                Map::startingPosX = i;
                Map::startingPosY = j;

            } else if (mapArray[i][j] == '!') {
                Map::numOfSprites++;
                std::pair<char, std::tuple<int, int>> valuesToMap('!', std::make_tuple(i,j));

                spriteLocationMap.insert(valuesToMap);
            } // FURTHER ELSE IF FOR OTHER TYPES OF ITEMS
        }
    }
}
