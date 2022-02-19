//
// Created by Bartosz Olewinski on 09/02/2022.
//

#ifndef MMPPROTOTYPE_RAYCASTER_H
#define MMPPROTOTYPE_RAYCASTER_H


#include <SFML/Window.hpp>
#include <unordered_map>
#include "../game/MapHandler.h"
#include "../game/Actor.h"
#include "../game/DebugConsole.cpp"


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
    void runGame(Actor *actor, Actor *actorAI);



private:
    Actor* agent{};
    Actor* player{};

    DebugConsole debugConsole = DebugConsole(nullptr);


    sf::Color greyColor;

    sf::Text text;
    sf::Font font;
    std::string stringText;


    double frameTime;

    sf::Clock fpsClock;
    sf::Time time;
    sf::Time oldTime;

    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    double rotSpeed = TimePerFrame.asSeconds() * 3.0;
    double moveSpeed = TimePerFrame.asSeconds() * 4.0;


    int textureSheetSize = 768;
    int singleTextureSize = 128;

    sf::Texture texture;


    enum class Textures {
        GreyDefault,
        RedCircle,
        BlueCross,
    };

    //unordered map for textures and its symbols on map
    const std::unordered_map<int, Textures> textureMap {
            {1, Textures::GreyDefault},
            {2, Textures::RedCircle},
            {3, Textures::BlueCross},
    };


    //just for testing purposes
    int testMap[14][14] = {
            0,0,0,0,0,2,1,1,2,0,0,0,0,0,
            0,1,4,1,0,2,0,0,0,2,0,0,0,0,
            0,5,0,0,2,2,0,0,0,1,0,0,0,0,
            0,4,0,0,0,0,0,1,0,3,2,2,0,0,
            0,3,0,0,2,2,3,3,0,0,0,0,3,2,
            0,5,0,0,0,0,0,0,0,0,0,0,0,2,
            0,5,0,0,0,0,0,0,0,0,2,0,0,1,
            0,1,0,0,1,3,0,0,0,0,3,0,0,1,
            0,1,0,0,2,3,0,0,0,0,1,0,0,1,
            0,0,3,3,1,2,0,0,0,0,0,0,0,1,
            0,0,0,0,0,2,0,0,0,0,0,0,2,0,
            0,0,0,0,0,1,0,0,0,0,0,2,0,0,
            0,0,0,0,0,2,0,0,0,2,2,3,0,0,
            0,0,0,0,0,2,3,3,1,1,0,0,0,0,
    };



    void setupWindow();


    /**
     * handles window entity
     */
    void renderWindow();

    /**
     * Renders image using raycasting,
     * depending on whether it is AI or not
     * the image is rendered in different places
     */
    void raycastingRenderer(Actor * actor);

    /**
     * draws information column
     */
    void drawInfoColumn();

    void drawScreenAI();

    void drawScreenPlayer();

    void playerControls();

};


#endif //MMPPROTOTYPE_RAYCASTER_H
