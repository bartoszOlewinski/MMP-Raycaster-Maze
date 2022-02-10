//
// Created by Bartosz Olewinski on 09/02/2022.
//

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>
#include "Raycaster.h"
#include "../game/Actor.h"

#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>


void Raycaster::runGame(Actor *actor, Actor *actorAI) {
    //establish actors, get pointers
    player = actor;
    agent = actorAI;

    handleWindow();
}


void Raycaster::handleWindow() {
    //variables for frame timing
    double frameTime;
    sf::Event event{};
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    sf::Time oldTime;

    //only when window is focused allow for player inputs
    if (windowPtr->hasFocus())
        playerControls();

    //handling closing window
    while(windowPtr->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            windowPtr->close();
    }



    //RENDERING ============================
    //clear before render
    sf::Color backgroundColor = sf::Color::Black;
    backgroundColor.r /= 4;
    backgroundColor.g /= 4;
    backgroundColor.b /= 4;

    windowPtr->clear(backgroundColor);

    //render game screens
    drawScreenPlayer();
    //drawScreenAI();

    //create info column
    //drawInfoColumn();

    //======================================


    oldTime = time;
    time = clock.getElapsedTime();
    frameTime = (time.asMilliseconds() - oldTime.asMilliseconds()) / 1000.0;

    //speeds shouldn't be tied to framerate, potentially game breaking, *B U G S*
    //rotSpeed = frameTime * 3.0;
    //moveSpeed = frameTime * 5.0;

    rotSpeed = 0.06;
    moveSpeed = 0.1;

    //display some info
    debugTextDisplay(frameTime);

    //display everything that's been drawn in draw functions
    windowPtr->display();
}

void Raycaster::raycastingRenderer(Actor * actor) {



}

void Raycaster::drawInfoColumn() {

}

void Raycaster::drawScreenAI() {

}

void Raycaster::drawScreenPlayer() {
    sf::VertexArray lines (sf::Lines, 18 * RENDER_WIDTH);
    lines.resize(0);

    for (int x = 0; x < RENDER_WIDTH; x++) {
        double cameraX = 2 * x / double(RENDER_WIDTH) - 1;
        double rayDirX = player->directionX + player->planeX * cameraX;
        double rayDirY = player->directionY + player->planeY * cameraX;


        int mapX = (int) player->positionX;
        int mapY = (int) player->positionY;


        double sideDistX;
        double sideDistY;


        double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1/rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1/rayDirY);


/*
        double deltaDistX = sqrt(1.0f + (rayDirY * rayDirY) / (rayDirX * rayDirX));
        double deltaDistY = sqrt(1.0f + (rayDirX * rayDirX) / (rayDirY * rayDirY));
*/

        double perpWallDist;


        int stepX;
        int stepY;

        int hit = 0;
        int side;


        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (player->positionX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->positionX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (player->positionY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->positionY) * deltaDistY;
        }


        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (testMap[mapX][mapY] > 0)
                hit = 1;
        }

        if(side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

        //height of line to draw on screen
        int lineHeight = (int) (RENDER_HEIGHT / perpWallDist);


        int drawStart = -lineHeight / 2 + RENDER_HEIGHT / 2;

        if (drawStart < 0)
            drawStart = 0;

        int drawEnd = lineHeight / 2 + RENDER_HEIGHT / 2;

        if (drawEnd >= RENDER_HEIGHT)
            drawEnd = RENDER_HEIGHT - 1;

        //selecting wall color based on number in the 2d map
        sf::Color color;
        switch (testMap[mapX][mapY]) {
            case 1: color = sf::Color::Blue;
            break;
            case 2: color = sf::Color::Magenta;
            break;
            case 3: color = sf::Color::Red;
            break;
            case 4: color = sf::Color::Cyan;
            break;
            case 5: color = sf::Color::Yellow;
            break;
            default: color = sf::Color::Green;
            break;
        }


        //different brightness of the wall
        if (side == 1) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }

        //floor and ceiling colour
        sf::Color greyColor;
        greyColor.r = 105;
        greyColor.g = 105;
        greyColor.b = 105;

        //drawing ceiling
        lines.append(sf::Vertex(sf::Vector2f((float)x+10, 0.0), greyColor));
        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float) drawStart), greyColor));
        //drawing floor
        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float) RENDER_HEIGHT-1), greyColor));
        //RENDER_HEIGHT - 1 to fix constant floor pixel at the bottom of the screen
        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float) drawEnd), greyColor));


        //drawing walls and their colours
        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float)drawStart),color));
        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float)drawEnd),color));

        //draw the vertex array onto the window
        windowPtr->draw(lines);
    }
}


//PROTOTYPE ONLY, NEED PROPER INTERFACE ||| OR ||| another function that handles AI's inputs
void Raycaster::playerControls() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

        double oldDirX = player->directionX;
        player->directionX = player->directionX * cos(-rotSpeed) - player->directionY * sin(-rotSpeed);
        player->directionY = oldDirX * sin(-rotSpeed) + player->directionY * cos(-rotSpeed);

        double oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(-rotSpeed) - player->planeY * sin(-rotSpeed);
        player->planeY = oldPlaneX * sin(-rotSpeed) + player->planeY * cos(-rotSpeed);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

        double oldDirX = player->directionX;
        player->directionX = player->directionX * cos(rotSpeed) - player->directionY * sin(rotSpeed);
        player->directionY = oldDirX * sin(rotSpeed) + player->directionY * cos(rotSpeed);

        double oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(rotSpeed) - player->planeY * sin(rotSpeed);
        player->planeY = oldPlaneX * sin(rotSpeed) + player->planeY * cos(rotSpeed);

    }
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Up))) {

        if (testMap[int(player->positionX + player->directionX * moveSpeed)][int(player->positionY)] == 0)
            player->positionX += player->directionX * moveSpeed;
        if (testMap[int(player->positionX)][int(player->positionY + player->directionY * moveSpeed)] == 0)
            player->positionY += player->directionY * moveSpeed;

    }else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Down))) {
        if (testMap[int(player->positionX - player->directionX * moveSpeed)][int(player->positionY)] == 0)
            player->positionX -= player->directionX * moveSpeed;
        if (testMap[int(player->positionX)][int(player->positionY - player->directionY * moveSpeed)] == 0)
            player->positionY -= player->directionY * moveSpeed;
    }

    //
    //ADD STRAFING AND ACTION BUTTON (alt & space)
    //

}

void Raycaster::debugTextDisplay(double frameTime) const {
    sf::Text text;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);

    std::string stringText = "PLAYER SCREEN DEBUG:\nFPS: " + std::to_string((int) std::round(1.0/frameTime))
                             + "\nFrame time: " + std::to_string( frameTime) + "s\nInputs: ";

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        stringText += "UP, ";
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        stringText += "DOWN, ";
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        stringText += "LEFT, ";
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        stringText += "RIGHT, ";
    }

    text.setString(stringText);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 750);


    windowPtr->draw(text);
}


