//
// Created by Bartosz Olewinski on 09/02/2022.
//

#include "Actor.h"

void Actor::setupStatsText(sf::Font *font, int posX, int posY) {
    statsText.setFont(*font);
    statsText.setFillColor(sf::Color::White);
    statsText.setString(scoreString + timerString);
    statsText.setPosition((float)posX, (float) posY);
    statsText.setCharacterSize(20);


}


void Actor::setupPopupText(sf::Font *font, int posX, int posY) {
    popupText.setFont(*font);
    popupText.setFillColor(sf::Color::Yellow);
    popupText.setOutlineColor(sf::Color::Black);
    popupText.setOutlineThickness(1.0);
    popupText.setString(popupString);
    popupText.setPosition((float) posX, (float) posY);
    popupText.setCharacterSize(20);

}


void Actor::setupEqText(sf::Font *font, int posX, int posY) {
    eqText.setFont(*font);
    eqText.setFillColor(sf::Color::White);
    eqText.setString(eqString);
    eqText.setPosition((float) posX, (float) posY);
    eqText.setCharacterSize(20);


}