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

const float ITEM_HIT_BOX = 0.5f;

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

    std::string stringText;
    sf::Text debugText;

    sf::Font font;



    sf::Text infoText;
    std::string scoreString;
    std::string timerString;


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
    sf::Texture bagTexture;
    sf::Texture keyTexture;



    //just for testing purposes
    Map mapObject;
    unsigned char mapInUse[Map::MAP_SIZE][Map::MAP_SIZE];
    std::vector<Sprite> loadedSpriteList;


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

    void update(Actor *actor);

    static void sortSprites(int* order, double* dist, unsigned int amount);

};


#endif //MMPPROTOTYPE_RAYCASTER_H
