//
// Created by Bartosz Olewinski on 09/03/2022.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include "Menu.h"
#include "../game/Actor.h"
#include <cstdio>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>


bool Menu::drawMenu(sf::RectangleShape *indicator, const sf::Font &font, bool isSummary) {
    //draw menu==================


    //agent text for agent selection submenu
    sf::Text agentMenuText;
    std::string agentString;
    agentString = "easy\nmedium\nhard";

    agentMenuText.setFont(font);
    agentMenuText.setOutlineColor(sf::Color::Black);
    agentMenuText.setOutlineThickness(1.0);
    agentMenuText.setCharacterSize(40);
    agentMenuText.setFillColor(sf::Color::White);
    agentMenuText.setPosition(420, 250);
    agentMenuText.setString(agentString);


    //level selection text for submenu
    sf::Text levelMenuText;
    std::string levelString;
    levelString = "map01\nmap02\nmap03\nmap04\nmap05";

    levelMenuText.setFont(font);
    levelMenuText.setOutlineColor(sf::Color::Black);
    levelMenuText.setOutlineThickness(1.0);
    levelMenuText.setCharacterSize(40);
    levelMenuText.setFillColor(sf::Color::White);
    levelMenuText.setPosition(640, 250);
    levelMenuText.setString(levelString);




    sf::Text menuText;
    std::string menuString;
    menuString = "PLAY\n\nQUIT";

    std::string summaryString;
    sf::Text summaryText;

    if (isSummary) {
        summaryString = "\n==previous level stats==\n\nmap: " + prevLevelString + "\nagent difficulty: " + prevDifficultyString +
                        "\n\n==PLAYER==\nplayer has finished: " + std::to_string(playerHasFinished) + "\nplayer time: " +
                        std::to_string(playerPrevTime.asSeconds()) + "s\nplayer score: " +
                        std::to_string(playerPrevScore) + " / " + std::to_string(maxPoints) +
                        "\n\n==AGENT==\nagent has finished: " + std::to_string(agentHasFinished) + "\nagent time: " +
                        std::to_string(agentPrevTime.asSeconds()) + "s\nagent score: " +
                        std::to_string(agentPrevScore) + " / " + std::to_string(maxPoints);


        summaryText.setFont(font);
        summaryText.setString(summaryString);
        summaryText.setCharacterSize(22);
        summaryText.setFillColor(sf::Color::Yellow);
        summaryText.setOutlineThickness(1.0);
        summaryText.setOutlineColor(sf::Color::Black);
        summaryText.setPosition(900, 200);


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

    if (menuTime.asSeconds() - choiceMenuTime.asSeconds() > 0.08) {

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
                    agentOption = EASY;
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
                    choiceMenuTime = menuClock.getElapsedTime();
                    menuOption = PLAY;
                }

                levelOption = MAP01;

                switch (agentOption) {

                    case EASY:
                        indicator->setPosition(400, 265);
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            agentOption = EASY;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            agentOption = MEDIUM;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            choiceMenuTime = menuClock.getElapsedTime();
                            menuOption = LEVEL;

                        }

                        break;

                    case MEDIUM:
                        indicator->setPosition(400, 310);
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            agentOption = EASY;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            agentOption = HARD;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            choiceMenuTime = menuClock.getElapsedTime();
                            menuOption = LEVEL;

                        }
                        break;

                    case HARD:
                        indicator->setPosition(400, 360);
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            agentOption = MEDIUM;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            agentOption = EASY;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            choiceMenuTime = menuClock.getElapsedTime();
                            menuOption = LEVEL;

                        }
                        break;
                }
                break;

            case LEVEL:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    choiceMenuTime = menuClock.getElapsedTime();
                    menuOption = AGENT;
                }

                switch (levelOption) {
                    case MAP01:
                        indicator->setPosition(620, 265);
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            levelOption = MAP05;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            levelOption = MAP02;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            //return enum to let raycaster know to change into play mode and which agent and level to load in
                            return true;

                        }

                        break;
                    case MAP02:
                        indicator->setPosition(620, 310);
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            levelOption = MAP01;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            levelOption = MAP03;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            //return enum to let raycaster know to change into play mode and which agent and level to load in
                            return true;

                        }

                        break;
                    case MAP03:
                        indicator->setPosition(620, 355);
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            levelOption = MAP02;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            levelOption = MAP04;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            //return enum to let raycaster know to change into play mode and which agent and level to load in
                            return true;

                        }

                        break;
                    case MAP04:
                        indicator->setPosition(620, 400);
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            levelOption = MAP03;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            levelOption = MAP05;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            //return enum to let raycaster know to change into play mode and which agent and level to load in
                            return true;

                        }

                        break;
                    case MAP05:
                        indicator->setPosition(620, 445);
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            levelOption = MAP04;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            choiceMenuTime = menuClock.getElapsedTime();

                            levelOption = MAP01;

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            //return enum to let raycaster know to change into play mode and which agent and level to load in
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

    if (menuOption == AGENT )
        windowPtr->draw(agentMenuText);
    if (menuOption == LEVEL) {
        windowPtr->draw(agentMenuText);
        windowPtr->draw(levelMenuText);
    }


    windowPtr->draw(summaryText);
    windowPtr->display();

    return false;
}

Menu::AgentOption Menu::getAgentOption() {
    return agentOption;
}

Menu::LevelOption Menu::getLevelOption() {
    return levelOption;
}

void Menu::copyPreviousSessionDetails(Actor *player, Actor *agent, int maxPoints, AgentOption difficulty, LevelOption level) {
    this->playerPrevScore = player->score;
    this->agentPrevScore = agent->score;

    this->playerPrevTime = player->time;
    this->agentPrevTime = agent->time;

    this->playerHasFinished = player->hasFinished;
    this->agentHasFinished = agent->hasFinished;

    this->maxPoints = maxPoints;

    switch (difficulty) {
        case EASY:
            prevDifficultyString = "easy";
            break;
        case HARD:
            prevDifficultyString = "hard";
            break;
        case MEDIUM:
            prevDifficultyString = "medium";
            break;
    }

    switch(level) {

        case MAP01:
            prevLevelString = "map01";
            break;
        case MAP02:
            prevLevelString = "map02";
            break;
        case MAP03:
            prevLevelString = "map03";
            break;
        case MAP04:
            prevLevelString = "map04";
            break;
        case MAP05:
            prevLevelString = "map05";
            break;
    }
}
