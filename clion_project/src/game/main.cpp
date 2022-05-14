#include <iostream>
#include <thread>

#include <SFML/Graphics.hpp>

#include "../graphics/Raycaster.h"




#define DEBUG_MODE
//#define RELEASE_MODE


//#define MUSIC_MODE



//setting up important attributes
void setUpActor(Actor* actor, std::string name) {
    //set up actors parameters
    actor->directionX = -1.0f;
    actor->directionY = 0.0f;

    actor->planeY = 0.66f;
    actor->planeX = 0.0f;

    actor->score = 0;

    actor->time = sf::Time::Zero;

    actor->hasFinished = false;

    actor->name = std::move(name);
}


int main() {

    std::string WINDOW_TITLE = "Raycaster Maze";

    std::string VERSION = "1.0";


//debug only by name, should be used as default way of window set up, if your display is above 1080p, either change preprocessor
//commands in Raycaster.h to render in 900p or try RELEASE_MODE while ensuring 16:9 screen ratio of the display
#ifdef DEBUG_MODE
    WINDOW_TITLE += " - " + VERSION;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default);
#endif

    //fullscreen works correctly only if screen it is displayed on is using 16:9 aspect ratio, and is >= 720p
#ifdef RELEASE_MODE
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Fullscreen);
#endif


    //set up icons for the window
    sf::Image icon;
    icon.loadFromFile("../resources/textures/icon.png");
    window.setIcon(100, 100, icon.getPixelsPtr());



    //clear the window
    window.clear(sf::Color::Black);

    //not necessary, default value true
    //window.setMouseCursorVisible(true);

    //supposedly helps in limiting framerate, most likely not working
    window.setVerticalSyncEnabled(true);


    //create a raycaster and initialize window
    Raycaster raycaster(&window);




    //actor set up
    Actor player{};
    player.renderX = 10;

    Actor agent{};
    agent.renderX = RENDER_WIDTH + 10 + 300;

    setUpActor(&player, "Player");
    setUpActor(&agent, "Agent");




    //change music file to whatever is placed in the 'sounds' directory
#ifdef MUSIC_MODE
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../resources/sounds/tyrian_theme.flac"))
        std::cout<<"music not loaded"<<std::endl;

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    sound.setVolume(10.f);
    sound.setLoop(true);
#endif


    //run game
    //MAIN LOOP INSIDE=====================================================

    raycaster.runGame(&player, &agent);

    //=====================================================================





    return 0;
}