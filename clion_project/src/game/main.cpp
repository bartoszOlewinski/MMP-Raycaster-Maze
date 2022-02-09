#include <iostream>

#include <SFML/Graphics.hpp>
#include "../graphics/Raycaster.h"


int main() {

    const int FRAME_LIMIT = 60;
    const std::string WINDOW_TITLE = "Raycaster prototype";

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close);
    window.setVerticalSyncEnabled(true);


    //create a raycaster and initialize window
    Raycaster raycaster(&window);

    //main loop
    while(window.isOpen()) {
        raycaster.runGame();
    }


    return 0;
}