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
#include "../game/Sprite.h"


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
    textureWallSheet.loadFromFile("../resources/textures/texture_sheet_test.png");


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

    sf::RenderStates state(&textureWallSheet);

    //sprites
    double spriteBuffer[RENDER_WIDTH];

    int numberOfSprites = 3;

    int spriteOrder[numberOfSprites];
    double spriteDistance[numberOfSprites];
    Sprite spriteArray[numberOfSprites];



    for (int x = 0; x < RENDER_WIDTH; x++) {
        double cameraX = 2 * x / double(RENDER_WIDTH) - 1;
        double rayDirX = player->directionX + player->planeX * cameraX;
        double rayDirY = player->directionY + player->planeY * cameraX;


        int mapX = (int) player->positionX;
        int mapY = (int) player->positionY;


        double sideDistX;
        double sideDistY;


        //is fine without the giant number :)
        double deltaDistX = std::abs(1/rayDirX);
        double deltaDistY = std::abs(1/rayDirY);


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
            //if (testMap[mapX][mapY] != '.' && testMap[mapX][mapY] > 48 && testMap[mapX][mapY] < 58)
            if (testMap[mapX][mapY] != '.') {
                hit = 1;
            } else if (testMap[mapX][mapY] < '.') { //if it's an object
                //need to figure out counter to know what index to use



            }

        }


        if(side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);





        //height of line to draw on screen
        int lineHeight = (int) (RENDER_HEIGHT / perpWallDist);

        //drawing ceiling======================================================
        lines.append(sf::Vertex(sf::Vector2f((float)x+10, 10), greyColor,
                                sf::Vector2f( 640.0f,  128.0f)));

        int drawStart = int(-lineHeight * (1.0f - 0.5f) + RENDER_HEIGHT * 0.5f);
        int overflownPixels = -drawStart;


        if (drawStart < 0) {
            drawStart = 0;
        }

        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float) drawStart + 10), greyColor,
                                sf::Vector2f( 640.0f,  128.0f)));
        //======================================================================



        //drawing floor=============================================
        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float) RENDER_HEIGHT + 10), greyColor,
                                sf::Vector2f( 640.0f,  128.0f)));

        int drawEnd = int(lineHeight * 0.5f + RENDER_HEIGHT * 0.5f);

        int pixelAdjustment = 0;

        if (drawEnd > RENDER_HEIGHT) {
            drawEnd = RENDER_HEIGHT - 1;

            //simple ratio of total pixels to be rendered and single textureWallSheet pixel height
            pixelAdjustment = overflownPixels * singleTextureSize / (overflownPixels + overflownPixels + RENDER_HEIGHT);
        }

        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float) drawEnd + 10), greyColor,
                                sf::Vector2f( 640.0f,  128.0f)));
        //==============================================================



        //getting the position of textureWallSheet in textureWallSheet sheet
        int textureNumber = int(testMap[mapX][mapY]) - '0' - 1;

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

        //flip textureWallSheet
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
        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float)drawStart + 10),color,
                                sf::Vector2f((float)textureCoordX, (float)(textureCoordY + 1 + pixelAdjustment))));

        lines.append(sf::Vertex(sf::Vector2f((float)x+10, (float)(drawEnd + 10)),color,
                                sf::Vector2f((float)textureCoordX, (float)(textureCoordY + singleTextureSize - 1 - pixelAdjustment))));
        //=======================================================



        spriteBuffer[x] = perpWallDist;





        //drawing on screen for textured version
        windowPtr->draw(lines, state);
    }

    //SPRITE CASTING ==========================================================
    for (int i = 0; i < numberOfSprites; i++) {
        spriteOrder[i] = i;
        //spriteDistance[i] = ((player->positionX ))

    }

    //=========================================================================
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

            if (testMap[int(player->positionX + player->directionX * moveSpeed)][int(player->positionY)] <= '.')
                player->positionX += player->directionX * moveSpeed;
            if (testMap[int(player->positionX)][int(player->positionY + player->directionY * moveSpeed)] <= '.')
                player->positionY += player->directionY * moveSpeed;

        } else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Down))) {
            stringText += "DOWN, ";

            if (testMap[int(player->positionX - player->directionX * moveSpeed)][int(player->positionY)] <= '.')
                player->positionX -= player->directionX * moveSpeed;
            if (testMap[int(player->positionX)][int(player->positionY - player->directionY * moveSpeed)] <= '.')
                player->positionY -= player->directionY * moveSpeed;
        }

        //strafing
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
            stringText += "LEFT, ALT, ";

            if (testMap[int(player->positionX - player->planeX * moveSpeed)][int(player->positionY)] <= '.')
                player->positionX -= player->planeX * moveSpeed;
            if (testMap[int(player->positionX)][int(player->positionY - player->planeY * moveSpeed)] <= '.')
                player->positionY -= player->planeY * moveSpeed;

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
            stringText += "RIGHT, ALT, ";

            if (testMap[int(player->positionX + player->planeX * moveSpeed)][int(player->positionY)] <= '.')
                player->positionX += player->planeX * moveSpeed;
            if (testMap[int(player->positionX)][int(player->positionY + player->planeY * moveSpeed)] <=  '.')
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


