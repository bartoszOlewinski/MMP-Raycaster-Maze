//
// Created by Bartosz Olewinski on 09/02/2022.
//

#ifndef MMPPROTOTYPE_RAYCASTER_H
#define MMPPROTOTYPE_RAYCASTER_H


#include <thread>
#include <unordered_map>

#include <SFML/Window.hpp>

#include "Menu.h"
#include "../game/Map.h"
#include "../game/Actor.h"
#include "../game/GameSetup.h"
#include "../game/Controller.h"
#include "../torch/PythonRunner.h"


/*
 * better use 720p,
 *
 * without dedicated GPU raycasting is horrible performance-wise,
 * GTX 1050, 960 and AMD equivalents should be completely fine with 900p
 * running it above 120fps,
 *
 */
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



/**
 * Most important class, central to the game,
 * handles window set up, raycasting renderer,
 * logic updates.
 *
 * Contains main game loop and high level menu handling.
 */
class Raycaster {
public:
    sf::RenderWindow* windowPtr;
    explicit Raycaster(sf::RenderWindow* sfWindow) {
        windowPtr = sfWindow;
    }

    /**
    * public function to be called when game is started
    * @param actor player object
    * @param actorAI agent object
    */
    void runGame(Actor *actor, Actor *actorAI);



private:
    Actor* agent{};

    Actor* player{};

    Map mapObject;

    GameSetup gameSetup;

    Menu menuObject;

    Controller controllerObject;

    //python essentials
    PythonRunner pyRunner;
    bool pyEnvRunning;
    const int PYTHON_RESET_CODE = -99;


    //string for a debug print in-game
    std::string gameVersion = "1.0";


    //modes used when in menu loop
    enum Mode{
        MENU_MODE,
        PLAY_MODE,
        LEVEL_SUMMARY
    };

    Mode mode;

    Menu::AgentOption agentOption;
    Menu::LevelOption levelOption;




    sf::Color greyColor;
    sf::Text debugText;

    sf::Font font;

    std::string eqDefaultString = "Equipment:\n";

    //for handling update timers
    sf::Clock fpsClock;
    sf::Time fpsStartTime;
    sf::Time oldTime;


    sf::Time startPopUp;
    bool playerNewItem = false;
    bool agentNewItem = false;



    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);




    //texture variables
    static const int textureSheetSize = 896;
    static const int singleTextureSize = 128;


    sf::Texture textureWallSheet;
    sf::Texture bagTexture;
    sf::Texture goldKeyTexture;
    sf::Texture silverKeyTexture;




    //thread for python runner
    std::thread aiThread;


    /**
    * Runs PythonRunner's function for Python's AI
    */
    void aiThreadHandler();

    /**
    * Handles main game loop, menu loop, calls renderer
    */
    void renderWindow();

    /**
    * Rendering raycasting magic function
    * @param actor player's or agent's perspective
    * @param texState wall texture sheet state file
    * @param bagState money bag texture state file
    * @param goldKeyState gold key texture state file
    * @param silverKeyState silver key texture state file
    */
    void raycastingRenderer(Actor * actor, sf::RenderStates texState, sf::RenderStates bagState,
                            sf::RenderStates goldKeyState, sf::RenderStates silverKeyState);

    /**
    * Handles logic update, item hit detection
    * @param actor object
    */
    void update(Actor *actor);


};


#endif //MMPPROTOTYPE_RAYCASTER_H
