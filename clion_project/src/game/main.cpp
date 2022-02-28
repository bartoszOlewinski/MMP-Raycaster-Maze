#include <iostream>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <utility>

#include "../graphics/Raycaster.h"



#define DEBUG_MODE
//#define RELEASE_MODE


#define MUSIC_MODE




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

    const std::string VERSION = "0.1.5.3";


#ifdef DEBUG_MODE
    WINDOW_TITLE += " - " + VERSION;
#endif



    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default);
    window.clear(sf::Color::Black);

    window.setVerticalSyncEnabled(true);

    //create a raycaster and initialize window
    Raycaster raycaster(&window);


    Actor player{};
    Actor agent{};

    setUpActor(&player, "PLAYER");
    setUpActor(&agent, "AGENT");


#ifdef MUSIC_MODE
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../resources/sounds/tyrian_theme.flac"))
        std::cout<<"music not loaded"<<std::endl;

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    sound.setVolume(20.f);
    sound.setLoop(true);
#endif



    //MAIN LOOP INSIDE
    raycaster.runGame(&player, &agent);





    return 0;
}