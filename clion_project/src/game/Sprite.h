//
// Created by Bartosz Olewinski on 19/02/2022.
//

#ifndef RAYCASTER_SPRITE_H
#define RAYCASTER_SPRITE_H

/**
 * Contains information of any sprite object,
 * also sorts sprites from clostest to furthest
 * from actor
 */
class Sprite {
public:



    double posX;
    double posY;
    char textureChar;
    //int texture;
    int score;

    //explicit Sprite(double posX, double posY);


    /**
    * Function copied from Lodev's tutorial
     * @param order
    * @param dist
    * @param amount
    */
    void sortSprites(int *order, double *dist, unsigned int amount);

    /**
    * Lodev's sprite sorting function with vectors instead of arrays
    * @param order vector of order of sprites
    * @param dist vector of sprite distances
    * @param amount int containing total amount of sprites in a map
    */
    void sortSprites2(std::vector<int>* order, std::vector<double>* dist, unsigned int amount);
};


#endif //RAYCASTER_SPRITE_H
