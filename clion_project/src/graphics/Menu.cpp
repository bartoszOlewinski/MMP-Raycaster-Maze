//
// Created by barto on 09/03/2022.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include "Menu.h"
#include <cstdio>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>


bool Menu::drawMenu(sf::RectangleShape *indicator, const sf::Font &font, bool isSummary) {
    //draw menu==================
    sf::Text agentMenuText;
    std::string agentString;
    agentString = "hard\nmedium\neasy";

    agentMenuText.setFont(font);
    agentMenuText.setOutlineColor(sf::Color::Black);
    agentMenuText.setOutlineThickness(1.0);
    agentMenuText.setCharacterSize(40);
    agentMenuText.setFillColor(sf::Color::White);
    agentMenuText.setPosition(420, 250);
    agentMenuText.setString(agentString);


    sf::Text menuText;
    std::string menuString;
    menuString = "PLAY\n\nQUIT";

    std::string summaryString;
    sf::Text summaryText;

    if (isSummary) {
        summaryString = "\n==previous level stats==\n"
                        "==PLAYER==\nplayer has finished: " + std::to_string(playerHasFinished) + "\nplayer time: " +
                        std::to_string(playerPrevTime.asSeconds()) + "s\nplayer score: " +
                        std::to_string(playerPrevScore) + " / " + std::to_string(maxPoints) +
                        "\n==AGENT==\nagent has finished: " + std::to_string(agentHasFinished) + "\nagent time: " +
                        std::to_string(agentPrevTime.asSeconds()) + "s\nagent score: " +
                        std::to_string(agentPrevScore) + " / " + std::to_string(maxPoints);


        summaryText.setFont(font);
        summaryText.setString(summaryString);
        summaryText.setCharacterSize(22);
        summaryText.setFillColor(sf::Color::Yellow);
        summaryText.setOutlineThickness(1.0);
        summaryText.setOutlineColor(sf::Color::Black);
        summaryText.setPosition(900, 250);


    }

    menuText.setFont(font);
    menuText.setString(menuString);
    menuText.setCharacterSize(40);
    menuText.setFillColor(sf::Color::White);
    menuText.setOutlineThickness(1.0);
    menuText.setOutlineColor(sf::Color::Black);
    menuText.setPosition(250, 250);


    windowPtr->clear(greyColor);

    menuTime = menuClock.getElapsedTime();

    if (menuTime.asSeconds() - choiceMenuTime.asSeconds() > 0.1) {

        // handling input
        switch (menuOption) {
            case PLAY:
                indicator->setPosition(230, 260);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    choiceMenuTime = menuClock.getElapsedTime();


                    menuOption = QUIT;

                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    choiceMenuTime = menuClock.getElapsedTime();
                    //choose agents
                    menuOption = AGENT;
                    agentOption = HARD;
                    windowPtr->draw(agentMenuText);

                }
                break;

            case QUIT:
                indicator->setPosition(230, 355);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    choiceMenuTime = menuClock.getElapsedTime();


                    menuOption = PLAY;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    windowPtr->close();
                }
                break;

            case AGENT:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    menuOption = PLAY;
                }

                switch (agentOption) {
                    case HARD:
                        indicator->setPosition(400, 265);
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            agentOption = EASY;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            agentOption = MEDIUM;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            //return flag true to let raycaster know to change into play mode
                            return true;

                        }

                        break;

                    case MEDIUM:
                        indicator->setPosition(400, 310);
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            agentOption = HARD;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            agentOption = EASY;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            //return enum to let raycaster know to change into play mode and which agent to load in
                            return true;

                        }
                        break;

                    case EASY:
                        indicator->setPosition(400, 360);
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            agentOption = MEDIUM;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            agentOption = HARD;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            //return enum to let raycaster know to change into play mode and which agent to load in
                            return true;

                        }
                        break;
                }
                break;

            default:
                std::cout << "Error menu switch" << std::endl;
        }
    }


    sf::Texture titleTexture;
    titleTexture.loadFromFile("../resources/textures/title_card.png");

    sf::Sprite spriteTitle;
    spriteTitle.setTexture(titleTexture, true);


    windowPtr->draw(spriteTitle);
    windowPtr->draw(*indicator);
    windowPtr->draw(menuText);

    if (menuOption == AGENT)
        windowPtr->draw(agentMenuText);

    windowPtr->draw(summaryText);
    windowPtr->display();

    return false;
}

Menu::AgentOption Menu::getAgentOption() {
    return agentOption;
}
