//
// Created by Bartosz Olewinski on 09/02/2022.
//

#ifndef RAYCASTER_MAPHANDLER_H
#define RAYCASTER_MAPHANDLER_H


#include <vector>

class MapHandler {
private:
    static const int MAP_HEIGHT = 26;
    static const int MAP_WIDTH = 26;


public:
    char map[MAP_HEIGHT][MAP_WIDTH];

    std::vector<std::vector<char>> getMap();

    void loadMap();

};


#endif //RAYCASTER_MAPHANDLER_H
