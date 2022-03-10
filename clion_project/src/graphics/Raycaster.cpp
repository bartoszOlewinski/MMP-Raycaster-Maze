//
// Created by Bartosz Olewinski on 09/02/2022.
//

#define PLAYER_DEBUG_DISPLAY



#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>

#include "Raycaster.h"


#include <cmath>
#include <iostream>


void Raycaster::runGame(Actor *actor, Actor *actorAI) {

    //debugConsole = DebugConsole(windowPtr);


    //establish actors, get pointers
    player = actor;
    agent = actorAI;

    gameSetup.setUpAttriubutes(&mapObject, player, agent);

    gameSetup.pickAndLoadMap();

    //set up starting point
    player->positionX = mapObject.startingPosX;
    player->positionY = mapObject.startingPosY;

    agent->positionX = mapObject.startingPosX;
    agent->positionY = mapObject.startingPosY;


    //copy the mapObject to the raycaster
    for (int i = 0; i < Map::MAP_SIZE; i++) {
        for (int j = 0; j < Map::MAP_SIZE; j++) {
            //mapInUse[i][j] = mapObject.mapArray[i][j];

            player->mapInstance[i][j] = mapObject.mapArray[i][j];
            agent->mapInstance[i][j] = mapObject.mapArray[i][j];
        }
    }

    menuObject.windowPtr = windowPtr;
    menuObject.maxPoints = mapObject.maxPoints;



    //floor and ceiling colour
    greyColor.r = 120;
    greyColor.g = 120;
    greyColor.b = 120;



    //load textures
    textureWallSheet.loadFromFile("../resources/textures/texture_sheet_test.png");
    bagTexture.loadFromFile("../resources/textures/bag_money.png");
    goldKeyTexture.loadFromFile("../resources/textures/golden_key.png");
    silverKeyTexture.loadFromFile("../resources/textures/silver_key.png");


    //set up clocks and times for time step
    sf::Clock fixedTimeStepClock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    sf::Event event{};




    //load font and initialize variables for text displays
    font.loadFromFile("arial.ttf");


    //information displays
    player->setupStatsText(&font, RENDER_WIDTH + 20, 15);
    agent->setupStatsText(&font, WINDOW_WIDTH - RENDER_WIDTH - 130, RENDER_HEIGHT - 115);



    //equipment displays
    player->setupEqText(&font, 20, RENDER_HEIGHT + 20);
    agent->setupEqText(&font, agent->renderX + 20, RENDER_HEIGHT + 20);


    //popup text
    player->setupPopupText(&font, 12, 12);
    agent->setupPopupText(&font, agent->renderX + 12, 12);




#ifdef PLAYER_DEBUG_DISPLAY
    //set up debugText and font
    debugText.setFont(font);
    debugText.setCharacterSize(15);
    debugText.setFillColor(sf::Color::Yellow);
    debugText.setPosition(20, WINDOW_HEIGHT - 100);
#endif


//=================MAIN GAME LOOP==========================

    mode = MENU_MODE;
    sf::RectangleShape indicator(sf::Vector2f(20,20));
    indicator.setPosition(230, 260);
    indicator.setFillColor(sf::Color::Yellow);
    indicator.setOutlineColor(sf::Color::Black);
    indicator.setOutlineThickness(1.0);
    indicator.setRotation(45.0);




    while (windowPtr->isOpen()) {

        //MENU====================

        if ((mode == MENU_MODE) && windowPtr->hasFocus()) {


            if (menuObject.drawMenu(&indicator, font, mode == LEVEL_SUMMARY)) {
                mode = PLAY_MODE;
                agentOption = menuObject.getAgentOption();
            }


            fixedTimeStepClock.restart();


        }


        //==========================


        while(windowPtr->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                windowPtr->close();
        }

        if (mode == PLAY_MODE) {

            //fixed time step, put logic and updates inside while loop
            //first add time to the timer
            if (!player->hasFinished)
                player->time += fixedTimeStepClock.getElapsedTime();

            if (!agent->hasFinished)
                agent->time += fixedTimeStepClock.getElapsedTime();


            timeSinceLastUpdate += fixedTimeStepClock.restart();


            while (timeSinceLastUpdate > TimePerFrame) {

                timeSinceLastUpdate -= TimePerFrame;


                update(player);
                update(agent);

                controllerObject.actorControls(player);
                controllerObject.actorControls(agent);

                //playerControls();
            }

            //raycaster
            renderWindow();

            //if escape pressed reset
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

                gameSetup.resetAttributes();


                mode = MENU_MODE;
            }

            if (mode == LEVEL_SUMMARY)
                gameSetup.resetAttributes();
        }
    }
    //========================================================
}


void Raycaster::renderWindow() {
    //get time before the render
    fpsStartTime = fpsClock.getElapsedTime();

    //RENDERING ============================
    //clear before drawing next frame
    windowPtr->clear(sf::Color::Black);





    //RAYCASTING VARIABLES
    sf::RenderStates wallState(&textureWallSheet);
    sf::RenderStates bagState(&bagTexture);
    sf::RenderStates goldKeyState(&goldKeyTexture);
    sf::RenderStates silverKeyState(&silverKeyTexture);




    //RENDER GAME SCREENS
    //might need to rework sprite textures to put them into single state
    raycastingRenderer(player, wallState, bagState,goldKeyState, silverKeyState);
    raycastingRenderer(agent, wallState,bagState, goldKeyState, silverKeyState);


    //debugConsole.activateDebug();
    //debugConsole.commandOpener();


    oldTime = fpsStartTime;
    fpsStartTime = fpsClock.getElapsedTime();
    frameTime = (fpsStartTime.asMilliseconds() - oldTime.asMilliseconds()) / 1000.0;


#ifdef PLAYER_DEBUG_DISPLAY
    windowPtr->draw(debugText);
#endif


    //essential text displays
    windowPtr->draw(player->statsText);
    windowPtr->draw(agent->statsText);


    windowPtr->draw(player->popupText);
    windowPtr->draw(agent->popupText);

    windowPtr->draw(player->eqText);
    windowPtr->draw(agent->eqText);


    //display everything that's been drawn in draw functions
    windowPtr->display();
}



void Raycaster::raycastingRenderer(Actor * actor, sf::RenderStates texState, sf::RenderStates bagState,
                                   sf::RenderStates goldKeyState, sf::RenderStates silverKeyState) {
    sf::VertexArray lines (sf::Lines,  RENDER_WIDTH); //why use RENDER_WIDTH and resize to 0 after???
    lines.resize(0);

    double spriteBuffer[RENDER_WIDTH];



    //==================START CASTING RAYS=====================================
    for (int x = 0; x < RENDER_WIDTH; x++) {
        double cameraX = 2 * x / double(RENDER_WIDTH) - 1;
        double rayDirX = actor->directionX + actor->planeX * cameraX;
        double rayDirY = actor->directionY + actor->planeY * cameraX;


        int mapX = (int) actor->positionX;
        int mapY = (int) actor->positionY;


        double sideDistX;
        double sideDistY;


        //is fine without the giant number :)
        double deltaDistX = std::abs(1/rayDirX);
        double deltaDistY = std::abs(1/rayDirY);


        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;


        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (actor->positionX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - actor->positionX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (actor->positionY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - actor->positionY) * deltaDistY;
        }




        bool hitDoor = false;

        double doorDistY;
        double doorDistX;

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

            //if (mapInUse[mapX][mapY] != '.' && mapInUse[mapX][mapY] > 48 && mapInUse[mapX][mapY] < 58)

            if (actor->mapInstance[mapX][mapY] != '.' && actor->mapInstance[mapX][mapY] != '#' && actor->mapInstance[mapX][mapY] != '!'
                && actor->mapInstance[mapX][mapY] != '$' && actor->mapInstance[mapX][mapY] != '&') {

                //if it's door calculate distances
                if (actor->mapInstance[mapX][mapY] == '5' || actor->mapInstance[mapX][mapY] == '6' || actor->mapInstance[mapX][mapY] == '7') {

                    double distance = sqrt((actor->positionX - mapX - 0.5f) * (actor->positionX - mapX - 0.5f) +
                                           (actor->positionY - mapY - 0.5f) * (actor->positionY - mapY - 0.5f));

                    if (distance < 1.5) {
                        actor->isCloseToDoor = true;
                        actor->doorX = mapX;
                        actor->doorY = mapY;
                    } else {
                        actor->isCloseToDoor = false;
                        actor->doorX = -1;
                        actor->doorY = -1;
                    }
                }

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
        lines.append(sf::Vertex(sf::Vector2f((float)x + (float)actor->renderX, (float)actor->renderY), greyColor,
                                sf::Vector2f( 640.0f,  0.0f)));

        int drawStart = int((float)-lineHeight * (1.0f - 0.5f) + RENDER_HEIGHT * 0.5f);
        int overflownPixels = -drawStart;


        if (drawStart < 0) {
            drawStart = 0;
        }

        lines.append(sf::Vertex(sf::Vector2f((float)x + (float)actor->renderX, (float) drawStart + (float)actor->renderY), greyColor,
                                sf::Vector2f( 640.0f,  0.0f)));
        //======================================================================





        //drawing floor=============================================
        lines.append(sf::Vertex(sf::Vector2f((float)x + (float)actor->renderX, (float) RENDER_HEIGHT + (float)actor->renderY), greyColor,
                                sf::Vector2f( 640.0f,  0.0f)));

        int drawEnd = int((float)lineHeight * 0.5f + RENDER_HEIGHT * 0.5f);

        int pixelAdjustment = 0;

        if (drawEnd > RENDER_HEIGHT) {
            drawEnd = RENDER_HEIGHT - 1;

            //simple ratio of total pixels to be rendered and single textureWallSheet pixel height
            pixelAdjustment = overflownPixels * singleTextureSize / (overflownPixels + overflownPixels + RENDER_HEIGHT);
        }

        lines.append(sf::Vertex(sf::Vector2f((float)x + (float)actor->renderX, (float) drawEnd + (float)actor->renderY), greyColor,
                                sf::Vector2f( 640.0f,  0.0f)));
        //==============================================================





        //getting the position of textureWallSheet in textureWallSheet sheet
        int textureNumber = int(actor->mapInstance[mapX][mapY]) - '0' - 1;

        int textureCoordX = textureNumber * singleTextureSize % textureSheetSize;
        int textureCoordY = textureNumber * singleTextureSize / textureSheetSize * singleTextureSize;




        //calculate where wall was hit
        double wallX;
        if (side == 0)
            wallX = actor->positionY + perpWallDist * rayDirY;
        else
            wallX = actor->positionX + perpWallDist * rayDirX;
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
        lines.append(sf::Vertex(sf::Vector2f((float)x + (float)actor->renderX, (float)drawStart + (float)actor->renderY),color,
                                sf::Vector2f((float)textureCoordX, (float)(textureCoordY + 1 + pixelAdjustment))));

        lines.append(sf::Vertex(sf::Vector2f((float)x + (float)actor->renderX, (float)drawEnd + (float)actor->renderY),color,
                                sf::Vector2f((float)textureCoordX, (float)(textureCoordY + singleTextureSize - 1 - pixelAdjustment))));
        //=======================================================






        //some distance buffers for sprites
        spriteBuffer[x] = perpWallDist;



        //drawing on screen for textured version
        windowPtr->draw(lines, texState);
    }
    //========================================================================




    //SPRITE CASTING ==========================================================

    sf::VertexArray spriteLines(sf::Lines, RENDER_WIDTH);
    spriteLines.resize(0);

    unsigned int numberOfSprites = actor->loadedSpriteList.size();

    int spriteOrder[numberOfSprites];
    double spriteDistance[numberOfSprites];


    for (int i = 0; i < numberOfSprites; i++) {
        spriteOrder[i] = i;
        spriteDistance[i] = ((actor->positionX - actor->loadedSpriteList[i].posX) * (actor->positionX - actor->loadedSpriteList[i].posX) +
                             (actor->positionY - actor->loadedSpriteList[i].posY) * (actor->positionY - actor->loadedSpriteList[i].posY));

    }


    //sort the sprites
    Sprite spriteSorter{};
    spriteSorter.sortSprites(spriteOrder, spriteDistance, numberOfSprites);


    //draw the sprites
    for (int j = 0; j < numberOfSprites; j++) {
        //clear vertex
        spriteLines.clear();

        double spriteX = actor->loadedSpriteList[spriteOrder[j]].posX - actor->positionX;
        double spriteY = actor->loadedSpriteList[spriteOrder[j]].posY - actor->positionY;



        double invDet = 1.0 / (actor->planeX * actor->directionY - actor->directionX * actor->planeY);

        double transformX = invDet * (actor->directionY * spriteX - actor->directionX * spriteY);
        double transformY = invDet * (-actor->planeY * spriteX + actor->planeX * spriteY);

        int spriteScreenX = int(( (float) RENDER_WIDTH / 2) * (1 + transformX / transformY));


        //stuff for scaling and moving sprites to the floor
#define vMove 128.0
#define SpriteScale 1.3
        int vMoveScreen = int(vMove / transformY);

        //stuff for scaling sprite in Y axis
        int overflowPixels = 0;
        int pixelAdjustment = 0;


        //calculating Y axis variables
        int spriteHeight = abs(int(RENDER_HEIGHT / (transformY))) / SpriteScale;

        int drawStartY = -spriteHeight / 2 + RENDER_HEIGHT / 2 + vMoveScreen;
        if(drawStartY < actor->renderY) {
            drawStartY = actor->renderY;
        }

        int drawEndY = spriteHeight / 2 + RENDER_HEIGHT / 2 + vMoveScreen;
        if (drawEndY >= RENDER_HEIGHT + actor->renderY) {
            overflowPixels = drawEndY - RENDER_HEIGHT - actor->renderY;

            pixelAdjustment = singleTextureSize * overflowPixels / RENDER_HEIGHT;


            drawEndY = RENDER_HEIGHT + actor->renderY;

        }


        //calculating X axis variables
        int spriteWidth = abs(int(RENDER_HEIGHT / (transformY))) / SpriteScale;

        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if (drawStartX < 0)
            drawStartX = actor->renderX;

        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if (drawEndX >= RENDER_WIDTH + actor->renderX)
            drawEndX = RENDER_WIDTH + actor->renderX - 1;


        unsigned char spriteHit = actor->loadedSpriteList[spriteOrder[j]].textureChar;


        int i = 1;
        //loop through every stripe of screen that must draw a sprite
        for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
            int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * singleTextureSize / spriteWidth) / 256;

            if (transformY > 0 && stripe > 0 && stripe < RENDER_WIDTH && transformY < spriteBuffer[stripe]) {


                //check for symbols and what to render
                spriteLines.append(sf::Vertex(sf::Vector2f((float) stripe + (float)actor->renderX, (float) drawStartY),
                                              sf::Vector2f((float) texX, (float) (1))));

                spriteLines.append(sf::Vertex(sf::Vector2f((float) stripe + (float)actor->renderX, (float) drawEndY),
                                              sf::Vector2f((float) texX, (float) (singleTextureSize - 1 - pixelAdjustment))));

                i++;


                switch (spriteHit) {
                    case '!':
                        windowPtr->draw(spriteLines, bagState);
                        break;

                    case '$':
                        windowPtr->draw(spriteLines, goldKeyState);
                        break;

                    case '&':
                        windowPtr->draw(spriteLines, silverKeyState);
                        break;

                    default:
                        std::cout<<"Unknown map symbol"<<std::endl;
                }

            }
        }
    }





    //=========================================================================


}


//PROTOTYPE ONLY, NEED PROPER INTERFACE ||| OR ||| another function that handles AI's inputs
void Raycaster::playerControls() {

#ifdef PLAYER_DEBUG_DISPLAY
    stringText = "Raycaster Maze v. " + gameVersion + "\nDEBUG:\nFPS: " + std::to_string((int) std::round(1.0f / frameTime))
                 + "\nFrame time: " + std::to_string( frameTime) + "s\nPlayer inputs: ";
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

            if (player->mapInstance[int(player->positionX + player->directionX * moveSpeed)][int(player->positionY)] <= '.')
                player->positionX += player->directionX * moveSpeed;
            if (player->mapInstance[int(player->positionX)][int(player->positionY + player->directionY * moveSpeed)] <= '.')
                player->positionY += player->directionY * moveSpeed;

        } else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Down))) {
            stringText += "DOWN, ";

            if (player->mapInstance[int(player->positionX - player->directionX * moveSpeed)][int(player->positionY)] <= '.')
                player->positionX -= player->directionX * moveSpeed;
            if (player->mapInstance[int(player->positionX)][int(player->positionY - player->directionY * moveSpeed)] <= '.')
                player->positionY -= player->directionY * moveSpeed;
        }

        //strafing
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
            stringText += "LEFT, ALT, ";

            if (player->mapInstance[int(player->positionX - player->planeX * moveSpeed)][int(player->positionY)] <= '.')
                player->positionX -= player->planeX * moveSpeed;
            if (player->mapInstance[int(player->positionX)][int(player->positionY - player->planeY * moveSpeed)] <= '.')
                player->positionY -= player->planeY * moveSpeed;

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
            stringText += "RIGHT, ALT, ";

            if (player->mapInstance[int(player->positionX + player->planeX * moveSpeed)][int(player->positionY)] <= '.')
                player->positionX += player->planeX * moveSpeed;
            if (player->mapInstance[int(player->positionX)][int(player->positionY + player->planeY * moveSpeed)] <= '.')
                player->positionY += player->planeY * moveSpeed;


        }

        /*
        //sprinting; currently can break actor out of bounds
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            moveSpeed *= 1.4;
        }
         */

        //action button
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            stringText += "SPACE, ";
            if (player->isCloseToDoor) {
                unsigned char tile =  player->mapInstance[player->doorX][player->doorY];

                switch (tile) {
                    case '5':
                        for (char collectedKey : player->collectedKeys) {
                            if (collectedKey == '$') {
                                player->mapInstance[player->doorX][player->doorY] = '.';
                            }
                        }
                        break;

                    case '7':
                        for (char collectedKey : player->collectedKeys) {
                            if (collectedKey == '&') {
                                player->mapInstance[player->doorX][player->doorY] = '.';
                            }
                        }
                        break;

                    case '6':
                        //get extra info for summary

                        menuObject.playerPrevScore = player->score;
                        menuObject.agentPrevScore = agent->score;


                        menuObject.playerPrevTime = player->time;
                        menuObject.agentPrevTime = agent->time;

                        player->hasFinished = true;

                        menuObject.playerHasFinished = player->hasFinished;
                        menuObject.agentHasFinished = agent->hasFinished;


                        mode = LEVEL_SUMMARY;

                        break;

                    default:
                        ;
                        //std::cout<<"Action key switch case unknown symbol"<<std::endl;
                }
            }
        }


#ifdef PLAYER_DEBUG_DISPLAY
        debugText.setString(stringText);
        //windowPtr->draw(debugText);
#endif

    }

}

//update texts and handle item hit detection
void Raycaster::update(Actor *actor) {

    //information column update===============================================
    unsigned char currentCell = actor->mapInstance[(int)actor->positionX][(int)actor->positionY];

    if ( currentCell != '#' && currentCell != '.') {
        switch (currentCell) {
            case '!':
                actor->score += 100;

                actor->popupString = "money bag picked up";
                break;

            case '$':
                actor->collectedKeys.push_back('$');

                actor->popupString = "golden key picked up";
                break;

            case '&':
                actor->collectedKeys.push_back('&');

                actor->popupString = "silver key picked up";
                break;

            default:
                std::cout<<"Hit detection encountered unknown instance."<<std::endl;
        }

        //std::cout<<actor->name<<" - item picked up, showing popup" <<std::endl;


        startPopUp = fpsClock.getElapsedTime();

        //std::cout<<actor->name<<" - time of start popup: "<<std::to_string(startPopUp.asSeconds()) <<std::endl;


        if (agent->name == "Player")
            playerNewItem = true;
        else
            agentNewItem = true;

        actor->popupText.setString(actor->popupString);



        actor->mapInstance[(int)actor->positionX][(int)actor->positionY] = '.';

        //delete the sprite from sprite list
        for(int i = 0; i < actor->loadedSpriteList.size(); i++) {
            if((int)actor->loadedSpriteList[i].posX == (int)actor->positionX && (int)actor->loadedSpriteList[i].posY == (int)actor->positionY) {

                actor->loadedSpriteList.erase(actor->loadedSpriteList.begin() + i);

            }
        }
    }


    sf::Time finishPopUp = fpsClock.getElapsedTime();


    if (finishPopUp.asSeconds() - startPopUp.asSeconds() > 1.2f && (playerNewItem || agentNewItem)) {
        /*
        std::cout<<actor->name<<" - time of end popup: "<<std::to_string(finishPopUp.asSeconds()) <<std::endl;
        std::cout<<actor->name<<" - difference "<<std::to_string(finishPopUp.asSeconds() - startPopUp.asSeconds()) <<std::endl;

        std::cout<<actor->name<<" - popup show, now erased." <<std::endl;
         */

        actor->popupString.clear();
        actor->popupText.setString(actor->popupString);

        if (actor->name == "Player")
            playerNewItem = false;
        else agentNewItem = false;

        startPopUp = sf::Time::Zero;
    }


    actor->scoreString = actor-> name + " Score\n" + std::to_string(actor->score);

    actor->timerString = "\n\n" + actor->name +" Time\n" + std::to_string(std::round(actor->time.asSeconds() * 100.0) / 100.0) + "s";


    actor->statsText.setString(actor->scoreString + actor->timerString);
    //===================================================



    //equipment text update================================================
    actor->eqString = "";
    for (char collectedKey : actor->collectedKeys) {
        switch (collectedKey) {
            case '$':
                actor->eqString += "golden key, ";
                break;
            case '&':
                actor->eqString += "silver key, ";
                break;

            default:
                actor->eqString = "empty";
        }
    }

    if (actor->eqString.empty())
        actor->eqString = "empty";



    actor->eqText.setString(eqDefaultString + actor->eqString);

    //==================================================================

}

