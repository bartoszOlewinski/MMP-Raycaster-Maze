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

    std::string VERSION = "0.2.6";



#ifdef DEBUG_MODE
    WINDOW_TITLE += " - " + VERSION;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default);
#endif

#ifdef RELEASE_MODE
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Fullscreen);
#endif

    sf::Image icon;
    icon.loadFromFile("../resources/textures/icon.png");

    window.setIcon(100, 100, icon.getPixelsPtr());





    window.clear(sf::Color::Black);

    window.setMouseCursorVisible(false);

    window.setVerticalSyncEnabled(true);

    //create a raycaster and initialize window
    Raycaster raycaster(&window);


    Actor player{};
    player.renderX = 10;

    Actor agent{};
    agent.renderX = RENDER_WIDTH + 10 + 300;

    setUpActor(&player, "Player");
    setUpActor(&agent, "Agent");


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