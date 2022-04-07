//
// Created by Bartosz Olewinski on 09/03/2022.
//

#ifndef RAYCASTER_CONTROLLER_H
#define RAYCASTER_CONTROLLER_H


#include "Actor.h"


class Menu;
class Controller {

public:
    enum Controls {
        UP,
        DOWN,
        TURN_LEFT,
        TURN_RIGHT,
        STRAFE_LEFT,
        STRAFE_RIGHT,
        ACTION,
        EMPTY,
    };

    void actorControls(Actor *actor);

    void agentControls(Actor *agent, int controls);



private:

    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    double rotSpeed = TimePerFrame.asSeconds() * 3.0;

    double moveSpeed = TimePerFrame.asSeconds() * 4.0;




    std::tuple<sf::Keyboard::Key, Controls> playerKeyBindArray[7];

    std::tuple<sf::Keyboard::Key, Controls> agentKeyBindArray[7];


    Actor *player;
    Actor *agent;


    static Controls translateKeyboardControls();


    void controls();

    void loadKeyMapping(Actor *actor);
};


#endif //RAYCASTER_CONTROLLER_H
