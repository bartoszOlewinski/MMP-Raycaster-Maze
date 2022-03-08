//
// Created by Bartosz Olewinski on 21/02/2022.
//

#ifndef RAYCASTER_MAP_H
#define RAYCASTER_MAP_H

#include <cstdio>
#include <unordered_map>
#include <vector>
#include "Sprite.h"


class Map {
private:


public:
    static const int MAP_SIZE = 20;

    unsigned char mapArray[MAP_SIZE][MAP_SIZE];

    unsigned char testMap[MAP_SIZE][MAP_SIZE] = {
            '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1',
            '1','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','1',
            '1','.','1','1','.','2','2','.','3','3','.','4','4','.','.','.','.','.','.','1',
            '1','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','1',
            '1','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','1',
            '1','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','1',
            '6','.','.','.','.','.','.','.','.','.','.','.','.','2','.','2','.','2','.','1',
            '1','.','.','.','.','.','.','.','.','.','.','.','.','5','.','5','.','5','.','1',
            '1','.','!','!','!','.','.','.','.','.','.','.','.','2','.','2','.','2','.','1',
            '1','.','!','!','!','.','.','.','.','.','.','.','.','.','.','.','.','.','.','1',
            '1','.','.','.','.','.','.','#','.','.','.','.','.','3','.','3','.','3','.','1',
            '1','.','.','.','$','.','.','.','.','.','.','.','.','7','.','7','.','7','.','1',
            '1','.','.','.','$','.','.','.','.','.','.','.','.','3','.','3','.','3','.','1',
            '1','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','1',
            '1','.','.','.','&','.','.','.','.','.','.','.','.','.','.','.','.','.','.','1',
            '1','.','.','.','&','.','.','.','.','.','.','.','.','.','.','.','.','.','.','1',
            '1','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','1',
            '1','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','1',
            '1','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','1',
            '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1',
    };

    unsigned char map01[MAP_SIZE][MAP_SIZE] = {
            '3','6','3','3','4','3','3','3','3','3','3','3','3','3','3','3','1','3','3','3',
            '3','.','3','.','!','.','3','.','.','.','.','.','.','!','.','.','2','!','.','3',
            '3','!','3','.','.','.','4','.','.','.','.','.','1','1','1','.','2','.','.','3',
            '3','.','5','.','.','.','.','.','.','.','.','.','.','.','.','.','2','.','.','3',
            '3','3','3','.','.','.','4','.','.','.','.','.','.','.','.','.','.','.','.','4',
            '.','.','3','.','!','.','3','!','.','.','.','.','.','.','.','.','2','2','.','3',
            '.','.','3','3','4','3','3','3','2','.','.','.','.','.','.','.','2','!','.','3',
            '.','.','.','.','.','.','2','2','2','.','.','2','.','!','!','.','2','.','.','3',
            '.','.','.','.','2','2','2','.','.','.','.','2','.','.','.','.','2','.','.','3',
            '.','.','.','.','2','2','.','.','.','.','.','.','.','.','.','.','2','4','4','1',
            '.','.','.','3','.','.','.','.','.','.','.','.','.','.','2','2','2','.','.','.',
            '.','3','3','3','.','.','.','.','.','.','.','.','.','.','.','.','1','.','.','.',
            '3','.','.','.','.','.','.','3','3','3','.','.','.','.','.','.','1','.','.','.',
            '3','.','.','.','.','.','.','.','3','3','3','.','.','.','.','.','1','.','.','.',
            '3','.','.','.','.','!','.','.','.','.','3','.','.','.','.','.','1','.','.','.',
            '3','.','.','.','3','.','3','.','.','.','3','.','.','.','1','.','1','.','.','.',
            '3','.','.','3','.','.','.','3','.','.','3','.','.','$','1','.','1','.','.','.',
            '3','.','.','3','.','.','.','3','.','.','3','.','.','1','1','.','1','.','.','.',
            '3','!','!','3','.','#','.','3','!','!','3','.','.','.','.','!','1','.','.','.',
            '1','4','4','1','3','4','3','1','4','4','1','1','1','1','1','1','1','.','.','.',
    };

    unsigned char map02[MAP_SIZE][MAP_SIZE] = {
            '2','2','2','2','.','.','.','.','.','.','.','.','.','.','.','2','2','2','2','2',
            '2','!','!','1','2','.','3','3','.','.','.','.','.','.','2','.','.','.','.','6',
            '2','.','1','.','2','3','.','.','3','3','.','.','.','2','.','.','2','2','2','3',
            '2','.','.','.','2','3','.','.','.','3','.','.','.','2','.','2','3','3','4','3',
            '2','1','1','.','2','3','.','.','.','3','4','2','2','2','.','2','3','!','.','3',
            '2','.','.','.','.','2','3','.','3','3','.','.','5','.','.','2','3','3','.','3',
            '2','.','.','.','!','2','3','.','3','3','.','3','.','.','.','2','3','.','.','3',
            '2','.','.','.','!','2','3','.','.','.','.','3','3','2','2','3','.','.','.','3',
            '2','.','.','2','2','2','3','.','.','.','.','3','3','3','3','.','.','.','.','3',
            '2','.','.','.','!','.','3','.','.','.','.','4','.','.','.','.','.','!','.','3',
            '.','2','.','3','4','3','3','.','.','.','3','3','.','.','.','.','.','.','.','3',
            '3','2','.','3','.','3','3','.','.','.','3','3','.','.','3','.','.','.','.','3',
            '3','.','.','3','.','3','3','.','3','4','3','3','3','.','3','.','.','.','3','.',
            '4','.','.','.','.','.','.','.','.','.','3','!','.','.','!','3','.','3','4','.',
            '4','.','!','.','.','.','.','.','.','.','3','$','.','.','3','3','.','.','.','3',
            '3','.','.','.','.','.','.','.','.','.','!','3','.','1','1','1','3','.','.','3',
            '3','3','3','3','.','3','3','.','3','.','.','!','1','.','.','.','1','1','.','1',
            '.','3','!','.','.','3','.','.','3','.','.','1','.','.','#','.','.','.','.','1',
            '.','3','!','.','.','3','!','.','4','.','.','.','.','.','1','.','.','.','.','1',
            '.','3','3','3','3','3','3','3','.','1','1','1','1','1','.','1','1','1','1','1',
    };

    int numOfSprites = 0;
    int maxPoints;
    double startingPosX{};
    double startingPosY{};

    //std::unordered_map<char, std::tuple<int, int>> spriteLocationMap;

    std::vector<Sprite> spriteList;

    void loadMapDetails(int mapNumber);


};


#endif //RAYCASTER_MAP_H
