//
// Created by Bartosz Olewinski on 09/03/2022.
//

#include <SFML/Window/Event.hpp>
#include <iostream>
#include <valarray>
#include "Controller.h"

void Controller::controls() {



}

void Controller::loadKeyMapping(Actor *actor) {
    if (actor->name == "Player") {
        playerKeyBindArray[0] = std::tuple<sf::Keyboard::Key, Controls>(sf::Keyboard::Up, UP);
        playerKeyBindArray[1] = std::tuple<sf::Keyboard::Key, Controls>(sf::Keyboard::Down, DOWN);
        playerKeyBindArray[2] = std::tuple<sf::Keyboard::Key, Controls>(sf::Keyboard::Left, TURN_LEFT);
        playerKeyBindArray[3] = std::tuple<sf::Keyboard::Key, Controls>(sf::Keyboard::Right, TURN_RIGHT);
        playerKeyBindArray[4] = std::tuple<sf::Keyboard::Key, Controls>(sf::Keyboard::Space, ACTION);

    } else {

    }
}


void Controller::actorControls(Actor *actor) {

    double oldDirX;
    double oldPlaneX;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

        if (actor->mapInstance[int(actor->positionX + actor->directionX * moveSpeed)][int(actor->positionY)] <= '.')
            actor->positionX += actor->directionX * moveSpeed;
        if (actor->mapInstance[int(actor->positionX)][int(actor->positionY + actor->directionY * moveSpeed)] <= '.')
            actor->positionY += actor->directionY * moveSpeed;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

        if (actor->mapInstance[int(actor->positionX - actor->directionX * moveSpeed)][int(actor->positionY)] <= '.')
            actor->positionX -= actor->directionX * moveSpeed;
        if (actor->mapInstance[int(actor->positionX)][int(actor->positionY - actor->directionY * moveSpeed)] <= '.')
            actor->positionY -= actor->directionY * moveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {

        oldDirX = actor->directionX;
        actor->directionX = actor->directionX * cos(rotSpeed) - actor->directionY * sin(rotSpeed);
        actor->directionY = oldDirX * sin(rotSpeed) + actor->directionY * cos(rotSpeed);

        oldPlaneX = actor->planeX;
        actor->planeX = actor->planeX * cos(rotSpeed) - actor->planeY * sin(rotSpeed);
        actor->planeY = oldPlaneX * sin(rotSpeed) + actor->planeY * cos(rotSpeed);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {

        oldDirX = actor->directionX;
        actor->directionX = actor->directionX * cos(-rotSpeed) - actor->directionY * sin(-rotSpeed);
        actor->directionY = oldDirX * sin(-rotSpeed) + actor->directionY * cos(-rotSpeed);

        oldPlaneX = actor->planeX;
        actor->planeX = actor->planeX * cos(-rotSpeed) - actor->planeY * sin(-rotSpeed);
        actor->planeY = oldPlaneX * sin(-rotSpeed) + actor->planeY * cos(-rotSpeed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {

        if (actor->mapInstance[int(actor->positionX - actor->planeX * moveSpeed)][int(actor->positionY)] <= '.')
            actor->positionX -= actor->planeX * moveSpeed;
        if (actor->mapInstance[int(actor->positionX)][int(actor->positionY - actor->planeY * moveSpeed)] <= '.')
            actor->positionY -= actor->planeY * moveSpeed;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {

        if (actor->mapInstance[int(actor->positionX + actor->planeX * moveSpeed)][int(actor->positionY)] <= '.')
            actor->positionX += actor->planeX * moveSpeed;
        if (actor->mapInstance[int(actor->positionX)][int(actor->positionY + actor->planeY * moveSpeed)] <= '.')
            actor->positionY += actor->planeY * moveSpeed;

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

        if (actor->isCloseToDoor) {
            unsigned char tile = actor->mapInstance[actor->doorX][actor->doorY];

            switch (tile) {
                case '5':
                    for (char collectedKey: actor->collectedKeys) {
                        if (collectedKey == '$') {
                            actor->mapInstance[actor->doorX][actor->doorY] = '.';
                        }
                    }
                    break;

                case '7':
                    for (char collectedKey: actor->collectedKeys) {
                        if (collectedKey == '&') {
                            actor->mapInstance[actor->doorX][actor->doorY] = '.';
                        }
                    }
                    break;

                case '6':
                    //get extra info for summary
                    actor->hasFinished = true;

                    break;


                default:;
                    //std::cout<<"Action key switch case unknown symbol"<<std::endl;
            }
        }
    }
}



Controller::Controls Controller::translateKeyboardControls() {

    //forwards or backwards
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        return UP;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        return DOWN;

    //turn left or right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
        return TURN_LEFT;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
        return TURN_RIGHT;

    //strafe left or right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
        return STRAFE_LEFT;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
        return STRAFE_RIGHT;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return ACTION;


    return EMPTY;
}
