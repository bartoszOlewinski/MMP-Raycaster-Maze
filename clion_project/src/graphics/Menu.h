//
// Created by barto on 09/03/2022.
//

#ifndef RAYCASTER_MENU_H
#define RAYCASTER_MENU_H


#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Menu {

public:
    explicit Menu(sf::RenderWindow *windowPtr, int maxPoints) {
        this->windowPtr = windowPtr;
        this->maxPoints = maxPoints;

        menuOption = PLAY;

        greyColor.r = 120;
        greyColor.g = 120;
        greyColor.b = 120;
    }



    enum AgentOption{
        HARD,
        MEDIUM,
        EASY,
    };

    bool drawMenu(sf::RectangleShape *indicator, const sf::Font& font, bool isSummary);

    AgentOption getAgentOption();

private:
    sf::RenderWindow *windowPtr;

    sf::Color greyColor;


    sf::Clock menuClock;
    sf::Time menuTime = menuClock.getElapsedTime();
    sf::Time choiceMenuTime = sf::Time::Zero;


    enum MenuOption {
        PLAY,
        AGENT,
        QUIT,
    };

    MenuOption menuOption;
    AgentOption agentOption;

    int maxPoints;

    sf::Time playerPrevTime;
    sf::Time agentPrevTime;

    int playerPrevScore{};
    int agentPrevScore{};

    bool playerHasFinished{};
    bool agentHasFinished{};



};


#endif //RAYCASTER_MENU_H
