//
// Created by Bartosz Olewinski on 09/03/2022.
//

#ifndef RAYCASTER_CONTROLLER_H
#define RAYCASTER_CONTROLLER_H


#include "Actor.h"

/**
 * Class that handles controlling movement of Player and Agent
 */
class Controller {

public:

    /**
    * Handles keyboard inputs for the Player
    * @param actor Player object
    */
    void actorControls(Actor *actor);

    /**
    * handles agent movement depending on input action
    * @param actor Agent object
    * @param controls int that represents action to take
    */
    void agentControls(Actor *agent, int controls);



private:

    //cont variables that moderates speed of movement
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    double rotSpeed = TimePerFrame.asSeconds() * 3.0;

    double moveSpeed = TimePerFrame.asSeconds() * 4.0;


    //Actor *player;
    Actor *agent;

};


#endif //RAYCASTER_CONTROLLER_H
