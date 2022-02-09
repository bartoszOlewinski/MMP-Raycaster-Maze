//
// Created by barto on 09/02/2022.
//

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>
#include "Raycaster.h"

//MAIN GAME FUNCTION
void Raycaster::runGame() {
    handleWindow();



}


void Raycaster::handleWindow() {
    sf::Event event{};

    //handling closing window
    while(windowPtr->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            windowPtr->close();
    }
    //erase previous frame
    windowPtr->clear(sf::Color::Black);

    //draw here
    raycastingRenderer();
    drawInfoColumn();


    //end of frame
    windowPtr->display();
}

void Raycaster::raycastingRenderer() {
    int screenPosX;
    int screenPosY;


}

void Raycaster::drawInfoColumn() {

}

void Raycaster::drawScreenAI() {

}

void Raycaster::drawScreenPlayer() {

}


