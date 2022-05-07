//
// Created by Bartosz Olewinski on 19/02/2022.
//

#include <cstdio>
#include <vector>
#include <algorithm>

#include "Sprite.h"



void Sprite::sortSprites(int *order, double *dist, unsigned int amount) {
    std::vector<std::pair<double, int>> sprites(amount);
    for(int i = 0; i < amount; i++) {
        sprites[i].first = dist[i];
        sprites[i].second = order[i];
    }
    std::sort(sprites.begin(), sprites.end());
    // restore in reverse order to go from farthest to nearest
    for(int i = 0; i < amount; i++) {
        dist[i] = sprites[amount - i - 1].first;
        order[i] = sprites[amount - i - 1].second;
    }
}


void Sprite::sortSprites2(std::vector<int>* order, std::vector<double>* dist, unsigned int amount) {
    std::vector<std::pair<double, int>> sprites(amount);
    for(int i = 0; i < amount; i++) {
        sprites[i].first = dist->at(i);
        sprites[i].second = order->at(i);
    }
    std::sort(sprites.begin(), sprites.end());
    // restore in reverse order to go from farthest to nearest
    for(int i = 0; i < amount; i++) {
        dist->at(i) = sprites[amount - i - 1].first;
        order->at(i) = sprites[amount - i - 1].second;
    }
}