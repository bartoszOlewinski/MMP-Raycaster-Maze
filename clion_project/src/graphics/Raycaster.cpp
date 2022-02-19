//
// Created by Bartosz Olewinski on 09/02/2022.
//

#define PLAYER_DEBUG_DISPLAY



#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>

#include "Raycaster.h"
#include "../game/Actor.h"


#include <cmath>
#include <iostream>
#include <thread>


void Raycaster::runGame(Actor *actor, Actor *actorAI) {
    //establish actors, get pointers
    player = actor;
    agent = actorAI;

    debugConsole = DebugConsole(windowPtr);


    sf::Clock clock;

    sf::Time timeSinceLastUpdate = sf::Time::Zero;


    sf::Event event{};


    //floor and ceiling colour
    greyColor.r = 105;
    greyColor.g = 105;
    greyColor.b = 105;


    //load textures
    texture.loadFromFile("../resources/textures/texture_sheet_test.png");



#ifdef PLAYER_DEBUG_DISPLAY
    //set up text and font
    font.loadFromFile("arial.ttf");
    text.setFont(font);

    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 750);
#endif


//=================MAIN GAME LOOP==========================

    while (windowPtr->isOpen()) {


        while(windowPtr->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                windowPtr->close();
        }

        //fixed time step, put logic and updates inside while loop
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TimePerFrame) {

            timeSinceLastUpdate -= TimePerFrame;

            playerControls();
        }


        //raycaster
        renderWindow();
    }
    //========================================================
}


void Raycaster::renderWindow() {
    //get time before the render
    time = fpsClock.getElapsedTime();

    //RENDERING ============================
    //clear before drawing next frame
    windowPtr->clear();


    //RENDER GAME SCREENS
    drawScreenPlayer();
    //drawScreenAI();

    //create info column
    //drawInfoColumn();
    debugConsole.activateDebug();
    debugConsole.commandOpener();


    oldTime = time;
    time = fpsClock.getElapsedTime();
    frameTime = (time.asMilliseconds() - oldTime.asMilliseconds()) / 1000.0;


#ifdef PLAYER_DEBUG_DISPLAY
    windowPtr->draw(text);
#endif

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
    sf::VertexArray lines (sf::Lines,  RENDER_WIDTH); //why use RENDER_WIDTH and resize to 0 after???
    lines.resize(0);

    sf::RenderStates state(&texture);

    for (int x = 0; x < RENDER_WIDTH; x++) {
        double cameraX = 2 * x / double(RENDER_WIDTH) - 1;
        double rayDirX = player->directionX + player->planeX * cameraX;
        double rayDirY = player->directionY + player->planeY * cameraX;


        int mapX = (int) player->positionX;
        int mapY = (int) player->positionY;


        double sideDistX;
        double sideDistY;



        //1e30 for avoiding zeros, technically should be fine since c++ can handle division by 0
        /*
        double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1/rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1/rayDirY);
         */

        //is fine without the giant number :)
        double deltaDistX = std::abs(1/rayDirX);
        double deltaDistY = std::abs(1/rayDirY);



// EUCLIDEAN DISTANCE, CREATES FISHEYE EFFECT

        //double deltaDistX = sqrt(1.0f + (rayDirY * rayDirY) / (rayDirX * rayDirX));
        //double deltaDistY = sqrt(1.0f + (rayDirX * rayDirX) / (rayDirY * rayDirY));




        double perpWallDist = 0.0f;

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

                //perpWallDist = (mapX - player->positionX + (1 - stepX) / 2) / rayDirX;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;

                //perpWallDist = (mapY - player->positionY + (1 - stepY) / 2) / rayDirY;
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
        int startAdjustment = 0;
        int endAdjustment = 0;

        //drawing ceiling======================================================
        lines.append(sf::Vertex(sf::Vector2f((float)x+10, 0), greyColor,
                                sf::Vector2f( 640.0f,  128.0f)));

        int drawStart = int(-lineHeight * (1.0f - 0.5f) + RENDER_HEIGHT * 0.5f);

        int overflowStartPixels = -drawStart;


        if (drawStart < 0) {
            drawStart = 0;

        }

        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float) drawStart), greyColor,
                                sf::Vector2f( 640.0f,  128.0f)));
        //======================================================================



        //drawing floor=============================================
        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float) RENDER_HEIGHT), greyColor,
                                sf::Vector2f( 640.0f,  128.0f)));

        int drawEnd = int(lineHeight * 0.5f + RENDER_HEIGHT * 0.5f);

        int overflowEndPixels = drawEnd - RENDER_HEIGHT;


        if (drawEnd > RENDER_HEIGHT) {
            drawEnd = RENDER_HEIGHT - 1;

            int size = overflowStartPixels + overflowEndPixels + RENDER_HEIGHT;

            endAdjustment = overflowEndPixels * singleTextureSize / size;
            startAdjustment = overflowStartPixels * singleTextureSize / size;
        }

        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float) drawEnd), greyColor,
                                sf::Vector2f( 640.0f,  128.0f)));
        //==============================================================



        //getting the position of texture in texture sheet
        int textureNumber = testMap[mapX][mapY] - 1;

        int textureCoordX = textureNumber * singleTextureSize % textureSheetSize;
        int textureCoordY = textureNumber * singleTextureSize / textureSheetSize * singleTextureSize;




        //calculate where wall was hit
        double wallX;
        if (side == 0)
            wallX = player->positionY + perpWallDist * rayDirY;
        else
            wallX = player->positionX + perpWallDist * rayDirX;
        wallX -= floor(wallX);


        //get x coordinate
        int textureX = int(wallX * double(singleTextureSize));

        //flip texture
        if (!side && rayDirX <= 0)
            textureX = singleTextureSize - textureX - 1;
        if (side && rayDirY >= 0)
            textureX = singleTextureSize - textureX - 1;

        textureCoordX += textureX;

        //shading
        sf::Color color = sf::Color::White;
        if (side == 0) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }




        //drawing textured lines==================================
        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float)drawStart),color,
                                sf::Vector2f((float)textureCoordX, (float)(textureCoordY + 1 + startAdjustment))));

        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float)(drawEnd)),color,
                                sf::Vector2f((float)textureCoordX, (float)(textureCoordY + singleTextureSize - 1 - endAdjustment))));
        //=======================================================



        //drawing on screen for textured version
        windowPtr->draw(lines, state);
    }
}


//PROTOTYPE ONLY, NEED PROPER INTERFACE ||| OR ||| another function that handles AI's inputs
void Raycaster::playerControls() {

#ifdef PLAYER_DEBUG_DISPLAY
    stringText = "PLAYER SCREEN DEBUG:\nFPS: " + std::to_string((int) std::round(1.0f/frameTime))
                 + "\nFrame time: " + std::to_string( frameTime) + "s\nInputs: ";
#endif


    if (windowPtr->hasFocus()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
            stringText += "LEFT, ";

            double oldDirX = player->directionX;
            player->directionX = player->directionX * cos(-rotSpeed) - player->directionY * sin(-rotSpeed);
            player->directionY = oldDirX * sin(-rotSpeed) + player->directionY * cos(-rotSpeed);

            double oldPlaneX = player->planeX;
            player->planeX = player->planeX * cos(-rotSpeed) - player->planeY * sin(-rotSpeed);
            player->planeY = oldPlaneX * sin(-rotSpeed) + player->planeY * cos(-rotSpeed);

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
            stringText += "RIGHT, ";

            double oldDirX = player->directionX;
            player->directionX = player->directionX * cos(rotSpeed) - player->directionY * sin(rotSpeed);
            player->directionY = oldDirX * sin(rotSpeed) + player->directionY * cos(rotSpeed);

            double oldPlaneX = player->planeX;
            player->planeX = player->planeX * cos(rotSpeed) - player->planeY * sin(rotSpeed);
            player->planeY = oldPlaneX * sin(rotSpeed) + player->planeY * cos(rotSpeed);

        }
        if (sf::Keyboard::isKeyPressed((sf::Keyboard::Up))) {
            stringText += "UP, ";

            if (testMap[int(player->positionX + player->directionX * moveSpeed)][int(player->positionY)] == 0)
                player->positionX += player->directionX * moveSpeed;
            if (testMap[int(player->positionX)][int(player->positionY + player->directionY * moveSpeed)] == 0)
                player->positionY += player->directionY * moveSpeed;

        } else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Down))) {
            stringText += "DOWN, ";

            if (testMap[int(player->positionX - player->directionX * moveSpeed)][int(player->positionY)] == 0)
                player->positionX -= player->directionX * moveSpeed;
            if (testMap[int(player->positionX)][int(player->positionY - player->directionY * moveSpeed)] == 0)
                player->positionY -= player->directionY * moveSpeed;
        }

        //strafing
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
            stringText += "LEFT, ALT, ";

            if (testMap[int(player->positionX - player->planeX * moveSpeed)][int(player->positionY)] == 0)
                player->positionX -= player->planeX * moveSpeed;
            if (testMap[int(player->positionX)][int(player->positionY - player->planeY * moveSpeed)] == 0)
                player->positionY -= player->planeY * moveSpeed;

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
            stringText += "RIGHT, ALT, ";

            if (testMap[int(player->positionX + player->planeX * moveSpeed)][int(player->positionY)] == 0)
                player->positionX += player->planeX * moveSpeed;
            if (testMap[int(player->positionX)][int(player->positionY + player->planeY * moveSpeed)] == 0)
                player->positionY += player->planeY * moveSpeed;


        }

        /*
        //sprinting; currently can break player out of bounds
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            moveSpeed *= 1.4;
        }
         */

        //action button
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            stringText += "SPACE, ";

        }


#ifdef PLAYER_DEBUG_DISPLAY
        text.setString(stringText);
        //windowPtr->draw(text);
        //std::cout<<stringText<<std::endl;
#endif

    }

}

void Raycaster::setupWindow() {

}


