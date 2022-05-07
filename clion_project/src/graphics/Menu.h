//
// Created by Bartosz Olewinski on 09/03/2022.
//

#ifndef RAYCASTER_MENU_H
#define RAYCASTER_MENU_H


#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../game/Actor.h"

/**
 * Map responsible for menu handling
 */
class Menu {

public:
    explicit Menu() {
        menuOption = PLAY;

        greyColor.r = 120;
        greyColor.g = 120;
        greyColor.b = 120;
    }

    sf::RenderWindow *windowPtr{};

    enum AgentOption{
        HARD,
        MEDIUM,
        EASY,
    };

    enum LevelOption{
        MAP01,
        MAP02,
        MAP03,
        MAP04,
        MAP05,
        MAP06,
    };

    enum MenuOption {
        PLAY,
        AGENT,
        LEVEL,
        QUIT,
    };

    MenuOption menuOption;
    LevelOption levelOption;
    AgentOption agentOption;



    int maxPoints{};

    sf::Time playerPrevTime;
    sf::Time agentPrevTime;

    int playerPrevScore{};
    int agentPrevScore{};

    bool playerHasFinished{};
    bool agentHasFinished{};

    std::string prevLevelString;
    std::string prevDifficultyString;


    /**
    * Draws menu, indicator
    * @param indicator indicates currently chosen option
    * @param font font to use
    * @param isSummary if menu needs to draw summary block
    * @return whether map has been chosen
    */
    bool drawMenu(sf::RectangleShape *indicator, const sf::Font& font, bool isSummary);

    /**
    * Gets difficulty of the agent
    * @return bool
    */
    AgentOption getAgentOption() const;

    /**
    * Gets map id that was chosen
    * @return Level Option enum
    */
    LevelOption getLevelOption() const;

    /**
    * copies previous session details to display in summary menu block
    * @param player actor object
    * @param agent actor object
    * @param maxPoints max points of the map
    * @param difficulty difficulty of the agent
    * @param level map id
    */
    void copyPreviousSessionDetails(Actor *player, Actor *agent, int maxPoints, AgentOption difficulty, LevelOption level);

private:
    sf::Color greyColor;

    sf::Clock menuClock;
    sf::Time menuTime = menuClock.getElapsedTime();
    sf::Time choiceMenuTime = sf::Time::Zero;


};


#endif //RAYCASTER_MENU_H
