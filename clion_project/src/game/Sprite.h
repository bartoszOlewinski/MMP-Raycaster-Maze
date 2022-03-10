//
// Created by Bartosz Olewinski on 19/02/2022.
//

#ifndef RAYCASTER_SPRITE_H
#define RAYCASTER_SPRITE_H


class Sprite {
public:
    //explicit Sprite(double posX, double posY);
    //COPIED FROM TUTORIAL BY LODEV
    void sortSprites(int *order, double *dist, unsigned int amount);


    double posX;
    double posY;
    char textureChar;
    //int texture;
    int score;
};


#endif //RAYCASTER_SPRITE_H
