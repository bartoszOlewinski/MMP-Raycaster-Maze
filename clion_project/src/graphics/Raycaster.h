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
#include "Menu.h"
#include "../game/GameSetup.h"
#include "../game/Controller.h"


#define RESOLUTION_720P
//#define RESOLUTION_900P

#ifdef RESOLUTION_720P
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const int RENDER_WIDTH = 480;
const int RENDER_HEIGHT = 360;
#endif

#ifdef RESOLUTION_900P
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;

const int RENDER_WIDTH = 640;
const int RENDER_HEIGHT = 480;
#endif



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

    Map mapObject;

    GameSetup gameSetup;

    Menu menuObject;

    Controller controllerObject;

    //DebugConsole debugConsole = DebugConsole(nullptr);



    std::string gameVersion = "0.3.2.2";



    enum Mode{
        MENU_MODE,
        PLAY_MODE,
        LEVEL_SUMMARY
    };


    Mode mode;

    Menu::AgentOption agentOption;


    sf::Color greyColor;

    std::string stringText;
    sf::Text debugText;


    sf::Font font;

    std::string eqDefaultString = "Equipment:\n";


    double frameTime;

    sf::Clock fpsClock;
    sf::Time fpsStartTime;
    sf::Time oldTime;


    sf::Time startPopUp;
    bool playerNewItem = false;
    bool agentNewItem = false;




    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    double rotSpeed = TimePerFrame.asSeconds() * 3.0;
    double moveSpeed = TimePerFrame.asSeconds() * 4.0;





    static const int textureSheetSize = 896;
    static const int singleTextureSize = 128;


    sf::Texture textureWallSheet;
    sf::Texture bagTexture;
    sf::Texture goldKeyTexture;
    sf::Texture silverKeyTexture;



    /**
     * handles window entity
     */
    void renderWindow();

    /**
     * Renders image using raycasting,
     * depending on whether it is AI or not
     * the image is rendered in different places
     */
    void raycastingRenderer(Actor * actor, sf::RenderStates texState, sf::RenderStates bagState,
                            sf::RenderStates goldKeyState, sf::RenderStates silverKeyState);



    void playerControls();

    void update(Actor *actor);

};


#endif //MMPPROTOTYPE_RAYCASTER_H
