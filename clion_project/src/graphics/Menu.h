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
    explicit Menu() {
        menuOption = PLAY;

        greyColor.r = 120;
        greyColor.g = 120;
        greyColor.b = 120;
    }

    sf::RenderWindow *windowPtr;

    enum AgentOption{
        HARD,
        MEDIUM,
        EASY,
    };


    int maxPoints;

    AgentOption prevDifficulty;

    sf::Time playerPrevTime;
    sf::Time agentPrevTime;

    int playerPrevScore{};
    int agentPrevScore{};

    bool playerHasFinished{};
    bool agentHasFinished{};

    bool drawMenu(sf::RectangleShape *indicator, const sf::Font& font, bool isSummary);

    AgentOption getAgentOption();


private:
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


    void copyPreviousSessionDetails();
};


#endif //RAYCASTER_MENU_H
