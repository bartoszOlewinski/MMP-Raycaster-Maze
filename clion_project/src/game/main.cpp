#include <iostream>

#include <SFML/Graphics.hpp>
#include <thread>
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

int main() {

    const std::string WINDOW_TITLE = "Raycaster Maze prototype";

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default);
    window.clear(sf::Color::Black);

    window.setVerticalSyncEnabled(true);

    //create a raycaster and initialize window
    Raycaster raycaster(&window);


    Actor player{};
    Actor agent{};

    setUpActor(&player);
    //setUpActor(&agent);


    //main loop
    raycaster.runGame(&player, &agent);

    return 0;
}