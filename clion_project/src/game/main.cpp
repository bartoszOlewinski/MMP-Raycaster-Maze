#include <iostream>

#include <SFML/Graphics.hpp>
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

    const int FRAME_LIMIT = 60;
    const std::string WINDOW_TITLE = "Raycaster Maze prototype";

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close);
    window.setFramerateLimit(FRAME_LIMIT);

    //create a raycaster and initialize window
    Raycaster raycaster(&window);


    Actor player{};
    Actor agent{};

    setUpActor(&player);

    //main loop
    while(window.isOpen()) {
        raycaster.runGame(&player, &agent);
    }


    return 0;
}