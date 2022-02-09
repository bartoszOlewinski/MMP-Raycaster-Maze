//
// Created by Bartosz Olewinski on 09/02/2022.
//

#ifndef MMPPROTOTYPE_RAYCASTER_H
#define MMPPROTOTYPE_RAYCASTER_H


#include <SFML/Window.hpp>
#include "../game/MapHandler.h"
#include "../game/Actor.h"


const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;

const int RENDER_WIDTH = 640;
const int RENDER_HEIGHT = 480;

class Raycaster {
public:
    sf::RenderWindow* windowPtr;
    explicit Raycaster(sf::RenderWindow* sfWindow) {
        windowPtr = sfWindow;
    }

    /**
     * Runs rest of the functions
     */
    void runGame(Actor* actor);



private:
    Actor* player;
    double rotSpeed;
    double moveSpeed;


    int testMap[14][14] = {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,1,1,1,0,0,0,0,0,0,0,0,0,0,
            0,1,0,0,2,0,0,0,0,0,0,0,0,0,
            0,1,0,0,2,0,0,0,0,0,0,0,0,0,
            0,1,0,0,2,2,3,3,0,0,0,0,0,0,
            0,1,0,0,0,0,0,3,0,0,0,0,0,0,
            0,1,0,0,1,4,0,3,0,0,0,0,0,0,
            0,1,0,0,1,4,0,4,0,0,0,0,0,0,
            0,1,0,0,5,4,0,4,0,0,0,0,0,0,
            0,0,5,5,5,4,4,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };





    /**
     * handles window entity
     */
    void handleWindow();

    /**
     * Renders image using raycasting,
     * depending on whether it is AI or not
     * the image is rendered in different places
     * @param screenPosX position on X axis for start point
     * @param screenPosY position on Y axis for start point
     */
    void raycastingRenderer(int screenPosX, int screenPosY);

    /**
     * draws information column
     */
    void drawInfoColumn();

    void drawScreenAI();

    void drawScreenPlayer();

    void playerControls();
};


#endif //MMPPROTOTYPE_RAYCASTER_H
