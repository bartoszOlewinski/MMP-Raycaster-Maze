//
// Created by Bartosz Olewinski on 09/02/2022.
//

#include "MapHandler.h"
#include <fstream>
#include <sstream>

void MapHandler::loadMap() {

}

std::vector<std::vector<char>> MapHandler::getMap() {
    std::vector<std::vector<char>> tempMap;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            tempMap[i][j] = map[i][j];
        }
    }
    return tempMap;
}
