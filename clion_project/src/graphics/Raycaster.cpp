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

//MAIN GAME FUNCTION
void Raycaster::runGame(Actor* actor) {

    player = actor;
    handleWindow();


}


void Raycaster::handleWindow() {
    double frameTimeForSpeeds;

    sf::Event event{};
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    sf::Time oldTime;

    playerControls();

    //handling closing window
    while(windowPtr->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            windowPtr->close();
    }

    //clear before render
    windowPtr->clear();

    //draw here
    drawScreenPlayer();


    //drawScreenAI();
    //drawInfoColumn();


    oldTime = time;
    time = clock.getElapsedTime();

    frameTimeForSpeeds = (time.asMilliseconds() - oldTime.asMilliseconds()) / 1000.0;

    rotSpeed = frameTimeForSpeeds * 3.0;
    moveSpeed = frameTimeForSpeeds * 5.0;


    sf::Text text;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setString("FPS: " + std::to_string((int) std::round(1.0/frameTimeForSpeeds))
    + "\nFrame time: " + std::to_string( frameTimeForSpeeds) + "s");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setPosition(60, 500);




    windowPtr->draw(text);

    //end of frame
    windowPtr->display();
}

void Raycaster::raycastingRenderer(int screenPosX, int screenPosY) {


}

void Raycaster::drawInfoColumn() {

}

void Raycaster::drawScreenAI() {

}

void Raycaster::drawScreenPlayer() {
    sf::VertexArray lines (sf::Lines, 18 * RENDER_WIDTH);
    //lines.resize(0);

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
            case 2: color = sf::Color::Red;
            break;
            case 3: color = sf::Color::White;
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


        //drawing the vertical line of pixels
        lines.append(sf::Vertex(
                sf::Vector2f((float)x, (float)drawStart),color));
        lines.append(sf::Vertex(
                sf::Vector2f((float)x, (float)drawEnd),color));

        windowPtr->draw(lines);

    }
}

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

    } else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Up))) {

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

}


