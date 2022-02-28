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
    debugConsole = DebugConsole(windowPtr);

    //pick random number, feed it to loading function,
    //switch case loads map
    mapObject.loadMapDetails();

    loadedSpriteList = mapObject.spriteList;


    //establish actors, get pointers
    player = actor;
    agent = actorAI;

    //set up starting point
    player->positionX = mapObject.startingPosX;
    player->positionY = mapObject.startingPosY;
    agent->positionX = mapObject.startingPosX;
    agent->positionY = mapObject.startingPosY;


    //copy the mapObject to the raycaster
    for (int i = 0; i < Map::MAP_SIZE; i++) {
        for (int j = 0; j < Map::MAP_SIZE; j++) {
            mapInUse[i][j] = mapObject.mapArray[i][j];
        }
    }



    //floor and ceiling colour
    greyColor.r = 105;
    greyColor.g = 105;
    greyColor.b = 105;


    //load textures
    textureWallSheet.loadFromFile("../resources/textures/texture_sheet_test.png");
    spriteTexture.loadFromFile("../resources/textures/bag_money.png");

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Event event{};

    font.loadFromFile("arial.ttf");

    infoString = "PLAYER SCORE: " + std::to_string(player->score);

    infoText.setFont(font);
    infoText.setFillColor(sf::Color::White);
    infoText.setString(infoString);
    infoText.setPosition(660, 40);
    infoText.setCharacterSize(20);


#ifdef PLAYER_DEBUG_DISPLAY
    //set up text and font
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


            if (mapInUse[(int)player->positionX][(int)player->positionY] == '!') {
                mapInUse[(int)player->positionX][(int)player->positionY] = '.';
                player->score += 100;
                infoString = "PLAYER:SCORE: " + std::to_string(player->score);
                infoText.setString(infoString);

                //delete the sprite from sprite list
                for(int i = 0; i < loadedSpriteList.size(); i++) {
                    if((int)loadedSpriteList[i].posX == (int)player->positionX &&
                            (int)loadedSpriteList[i].posY == (int)player->positionY) {
                        loadedSpriteList.erase(loadedSpriteList.begin() + i);
                    }
                }
            }



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

    windowPtr->draw(infoText);
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
    sf::RenderStates spriteState(&spriteTexture);

    double spriteBuffer[RENDER_WIDTH];


    //START CASTING RAYS
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
            //if (mapInUse[mapX][mapY] != '.' && mapInUse[mapX][mapY] > 48 && mapInUse[mapX][mapY] < 58)
            if (mapInUse[mapX][mapY] != '.' && mapInUse[mapX][mapY] != '#' && mapInUse[mapX][mapY] != '!') {
                hit = 1;
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
        int textureNumber = int(mapInUse[mapX][mapY]) - '0' - 1;

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
        if (!side && rayDirX > 0)
            textureX = singleTextureSize - textureX - 1;
        if (side && rayDirY <= 0)
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






        //some distance buffers for sprites
        spriteBuffer[x] = perpWallDist;



        //drawing on screen for textured version
        windowPtr->draw(lines, state);
    }


    //SPRITE CASTING ==========================================================

    sf::VertexArray spriteLines(sf::Lines, RENDER_WIDTH);
    spriteLines.resize(0);

    unsigned int numberOfSprites = loadedSpriteList.size();

    int spriteOrder[numberOfSprites];
    double spriteDistance[numberOfSprites];


    for (int i = 0; i <numberOfSprites; i++) {
        spriteOrder[i] = i;
        spriteDistance[i] = ((player->positionX - loadedSpriteList[i].posX) * (player->positionX - loadedSpriteList[i].posX) +
                             player->positionY - loadedSpriteList[i].posY) * (player->positionY - loadedSpriteList[i].posY);


    }

    //sort the sprites
    sortSprites(spriteOrder, spriteDistance, numberOfSprites);

    //draw the sprites
    for (int j = 0; j < numberOfSprites; j++) {
        double spriteX = loadedSpriteList[spriteOrder[j]].posX - player->positionX;
        double spriteY = loadedSpriteList[spriteOrder[j]].posY - player->positionY;


        double invDet = 1.0 / (player->planeX * player->directionY - player->directionX * player->planeY);

        double transformX = invDet * (player->directionY * spriteX - player->directionX * spriteY);
        double transformY = invDet * (-player->planeY * spriteX + player->planeX * spriteY);

        int spriteScreenX = int((RENDER_WIDTH / 2) * (1 + transformX / transformY));


        //calculating Y axis variables
        int spriteHeight = abs(int(RENDER_HEIGHT / (transformY)));

        int drawStartY = -spriteHeight / 2 + RENDER_HEIGHT / 2;
        if(drawStartY < 10)
            drawStartY = 10;

        int drawEndY = spriteHeight / 2 + RENDER_HEIGHT / 2;
        if (drawEndY >= RENDER_HEIGHT + 10)
            drawEndY = RENDER_HEIGHT + 10 - 1;

        //calculating X axis variables
        int spriteWidth = abs(int(RENDER_HEIGHT / (transformY)));

        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if (drawStartX < 10)
            drawStartX = 10;

        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if (drawEndX >= RENDER_WIDTH + 10)
            drawEndX = RENDER_WIDTH + 10 - 1;




        int i = 1;
        //loop through every stripe of screen that must draw a sprite
        for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
            int texX = int(256 *(stripe - (-spriteWidth / 2+ spriteScreenX)) * singleTextureSize / spriteWidth) / 256;

            if (transformY > 0 && stripe > 0 && stripe < RENDER_WIDTH && transformY < spriteBuffer[stripe]) {

                //check for symbols and what to render
                spriteLines.append(sf::Vertex(sf::Vector2f((float) stripe + 10, (float) drawStartY),
                                              sf::Vector2f((float) texX, (float) (1))));

                spriteLines.append(sf::Vertex(sf::Vector2f((float) stripe + 10, (float) drawEndY),
                                              sf::Vector2f((float) texX, (float) (singleTextureSize - 1))));

                i++;
                windowPtr->draw(spriteLines,spriteState);
            }
        }
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
            stringText += "RIGHT, ";

            double oldDirX = player->directionX;
            player->directionX = player->directionX * cos(-rotSpeed) - player->directionY * sin(-rotSpeed);
            player->directionY = oldDirX * sin(-rotSpeed) + player->directionY * cos(-rotSpeed);

            double oldPlaneX = player->planeX;
            player->planeX = player->planeX * cos(-rotSpeed) - player->planeY * sin(-rotSpeed);
            player->planeY = oldPlaneX * sin(-rotSpeed) + player->planeY * cos(-rotSpeed);

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
            stringText += "LEFT, ";

            double oldDirX = player->directionX;
            player->directionX = player->directionX * cos(rotSpeed) - player->directionY * sin(rotSpeed);
            player->directionY = oldDirX * sin(rotSpeed) + player->directionY * cos(rotSpeed);

            double oldPlaneX = player->planeX;
            player->planeX = player->planeX * cos(rotSpeed) - player->planeY * sin(rotSpeed);
            player->planeY = oldPlaneX * sin(rotSpeed) + player->planeY * cos(rotSpeed);

        }
        if (sf::Keyboard::isKeyPressed((sf::Keyboard::Up))) {
            stringText += "UP, ";

            if (mapInUse[int(player->positionX + player->directionX * moveSpeed)][int(player->positionY)] <= '.')
                player->positionX += player->directionX * moveSpeed;
            if (mapInUse[int(player->positionX)][int(player->positionY + player->directionY * moveSpeed)] <= '.')
                player->positionY += player->directionY * moveSpeed;

        } else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Down))) {
            stringText += "DOWN, ";

            if (mapInUse[int(player->positionX - player->directionX * moveSpeed)][int(player->positionY)] <= '.')
                player->positionX -= player->directionX * moveSpeed;
            if (mapInUse[int(player->positionX)][int(player->positionY - player->directionY * moveSpeed)] <= '.')
                player->positionY -= player->directionY * moveSpeed;
        }

        //strafing
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
            stringText += "LEFT, ALT, ";

            if (mapInUse[int(player->positionX - player->planeX * moveSpeed)][int(player->positionY)] <= '.')
                player->positionX -= player->planeX * moveSpeed;
            if (mapInUse[int(player->positionX)][int(player->positionY - player->planeY * moveSpeed)] <= '.')
                player->positionY -= player->planeY * moveSpeed;

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
            stringText += "RIGHT, ALT, ";

            if (mapInUse[int(player->positionX + player->planeX * moveSpeed)][int(player->positionY)] <= '.')
                player->positionX += player->planeX * moveSpeed;
            if (mapInUse[int(player->positionX)][int(player->positionY + player->planeY * moveSpeed)] <= '.')
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

void Raycaster::getSpriteLocations() {

}

void Raycaster::update() {



}



//COPIED FROM TUTORIAL BY LODEV
void Raycaster::sortSprites(int *order, double *dist, int amount) {
    std::vector<std::pair<double, int>> sprites(amount);
    for(int i = 0; i < amount; i++) {
        sprites[i].first = dist[i];
        sprites[i].second = order[i];
    }
    std::sort(sprites.begin(), sprites.end());
    // restore in reverse order to go from farthest to nearest
    for(int i = 0; i < amount; i++) {
        dist[i] = sprites[amount - i - 1].first;
        order[i] = sprites[amount - i - 1].second;
    }
}



