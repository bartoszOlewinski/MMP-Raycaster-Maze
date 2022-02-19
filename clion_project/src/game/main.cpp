#include <iostream>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../graphics/Raycaster.h"


void setUpActor(Actor* actor) {
    //set up actors parameters

    actor->positionX = 3.0f;
    actor->positionY = 2.5;

    actor->directionX = 1.0f;
    actor->directionY = 0.0f;

    actor->planeY = 0.66f;
    actor->planeX = 0.0f;
}


#define DEBUG_MODE
//#define RELEASE_MODE


#define MUSIC_MODE




int main() {

    std::string WINDOW_TITLE = "Raycaster Maze";

    const std::string VERSION = "0.1.3.1";


#ifdef DEBUG_MODE
    WINDOW_TITLE += " - prototype_textured_" + VERSION;
#endif



    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default);
    window.clear(sf::Color::Black);

    window.setVerticalSyncEnabled(true);

    //create a raycaster and initialize window
    Raycaster raycaster(&window);


    Actor player{};
    Actor agent{};

    setUpActor(&player);
    //setUpActor(&agent);

#ifdef MUSIC_MODE
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../resources/sounds/into_sandys_city.flac"))
        std::cout<<"music not loaded"<<std::endl;

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    sound.setVolume(20.f);
    sound.setLoop(true);
#endif



    //main loop
    raycaster.runGame(&player, &agent);

    return 0;
}