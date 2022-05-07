//
// Created by Bartosz Olewinski on 09/03/2022.
//

#include <SFML/Window/Event.hpp>
#include <valarray>
#include "Controller.h"


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


void Controller::agentControls(Actor *actor, int controls) {

    double oldDirX;
    double oldPlaneX;

    //if controls == -1 then do nothing


    if (controls == 1) {

        if (actor->mapInstance[int(actor->positionX + actor->directionX * moveSpeed)][int(actor->positionY)] <= '.')
            actor->positionX += actor->directionX * moveSpeed;
        if (actor->mapInstance[int(actor->positionX)][int(actor->positionY + actor->directionY * moveSpeed)] <= '.')
            actor->positionY += actor->directionY * moveSpeed;

    } else if (controls == 0) {

        if (actor->mapInstance[int(actor->positionX - actor->directionX * moveSpeed)][int(actor->positionY)] <= '.')
            actor->positionX -= actor->directionX * moveSpeed;
        if (actor->mapInstance[int(actor->positionX)][int(actor->positionY - actor->directionY * moveSpeed)] <= '.')
            actor->positionY -= actor->directionY * moveSpeed;
    }

    if (controls == 2) {

        oldDirX = actor->directionX;
        actor->directionX = actor->directionX * cos(rotSpeed) - actor->directionY * sin(rotSpeed);
        actor->directionY = oldDirX * sin(rotSpeed) + actor->directionY * cos(rotSpeed);

        oldPlaneX = actor->planeX;
        actor->planeX = actor->planeX * cos(rotSpeed) - actor->planeY * sin(rotSpeed);
        actor->planeY = oldPlaneX * sin(rotSpeed) + actor->planeY * cos(rotSpeed);

    } else if (controls == 3) {

        oldDirX = actor->directionX;
        actor->directionX = actor->directionX * cos(-rotSpeed) - actor->directionY * sin(-rotSpeed);
        actor->directionY = oldDirX * sin(-rotSpeed) + actor->directionY * cos(-rotSpeed);

        oldPlaneX = actor->planeX;
        actor->planeX = actor->planeX * cos(-rotSpeed) - actor->planeY * sin(-rotSpeed);
        actor->planeY = oldPlaneX * sin(-rotSpeed) + actor->planeY * cos(-rotSpeed);
    }

    //handle door opening and interaction
    if (controls == 4) {

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
