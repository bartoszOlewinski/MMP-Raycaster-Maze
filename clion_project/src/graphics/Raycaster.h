//
// Created by Bartosz Olewinski on 09/02/2022.
//

#ifndef MMPPROTOTYPE_RAYCASTER_H
#define MMPPROTOTYPE_RAYCASTER_H


#include <SFML/Window.hpp>
#include <unordered_map>
#include "../game/Actor.h"
#include "../game/DebugConsole.cpp"
#include "../game/Map.h"


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
    Map map;


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


    static const int textureSheetSize = 896;
    static const int singleTextureSize = 128;

    sf::Texture textureWallSheet;


    enum class Textures {
        GreyDefault,
        RedCircle,
        BlueCross,
        MoneyBag,
    };

    //unordered map for textures and its symbols on map
    const std::unordered_map<int, Textures> textureMap {
            {'1', Textures::GreyDefault},
            {'2', Textures::RedCircle},
            {'3', Textures::BlueCross},
            {'!', Textures::MoneyBag}
    };


    //just for testing purposes
    unsigned char mapInUse[14][14];



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

    void getSpriteLocations();

};


#endif //MMPPROTOTYPE_RAYCASTER_H
