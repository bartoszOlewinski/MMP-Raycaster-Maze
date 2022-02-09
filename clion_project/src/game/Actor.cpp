//
// Created by Bartosz Olewinski on 09/02/2022.
//

#include "Actor.h"

double Actor::getPositionX() const {
    return positionX;
}

void Actor::setPositionX(double positionX) {
    Actor::positionX = positionX;
}

double Actor::getPositionY() const {
    return positionY;
}

void Actor::setPositionY(double positionY) {
    Actor::positionY = positionY;
}

double Actor::getDirectionX() const {
    return directionX;
}

void Actor::setDirectionX(double directionX) {
    Actor::directionX = directionX;
}

double Actor::getDirectionY() const {
    return directionY;
}

void Actor::setDirectionY(double directionY) {
    Actor::directionY = directionY;
}

double Actor::getPlaneX() const {
    return planeX;
}

void Actor::setPlaneX(double planeX) {
    Actor::planeX = planeX;
}

double Actor::getPlaneY() const {
    return planeY;
}

void Actor::setPlaneY(double planeY) {
    Actor::planeY = planeY;
}
