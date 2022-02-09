//
// Created by barto on 09/02/2022.
//

#ifndef MMPPROTOTYPE_RAYCASTER_H
#define MMPPROTOTYPE_RAYCASTER_H


#include <SFML/Window.hpp>


const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;

const int RENDER_WIDTH = 640;
const int RENDER_HEIGHT = 480;

const std::string WINDOW_TITLE = "Raycaster prototype";

class Raycaster {
public:
    sf::RenderWindow* windowPtr;
    explicit Raycaster(sf::RenderWindow* sfWindow) {
        windowPtr = sfWindow;
    }

    /**
     * Runs rest of the functions
     */
    void runGame();



private:
    /**
     * handles window entity
     */
    void handleWindow();

    /**
     * Renders image using raycasting,
     * depending on whether it is AI or not
     * the image is rendered in different places
     */
    void raycastingRenderer();

    /**
     * draws information column
     */
    void drawInfoColumn();

    void drawScreenAI();

    void drawScreenPlayer();
};


#endif //MMPPROTOTYPE_RAYCASTER_H
