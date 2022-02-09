#include <iostream>

#include <SFML/Graphics.hpp>
#include "../graphics/Raycaster.h"


int main() {

    const int FRAME_LIMIT = 60;
    const std::string WINDOW_TITLE = "Raycaster prototype";

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close);
    window.setFramerateLimit(FRAME_LIMIT);


    //create a raycaster and initialize window
    Raycaster raycaster(&window);
    Actor player{};
    player.positionX = 3.0f;
    player.positionY = 2.0f;

    player.directionX = 1.0f;
    player.directionY = 0.0f;

    player.planeY = 0.66;
    player.planeX = 0;

    //main loop
    while(window.isOpen()) {
        raycaster.runGame(&player);
    }


    return 0;
}