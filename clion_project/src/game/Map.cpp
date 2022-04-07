//
// Created by Bartosz Olewinski on 21/02/2022.
//

#include "Map.h"




//#define TEST_MAP
//#define MAP01
//#define MAP02
//#define MAP03
//#define MAP04
//#define MAP05
//#define MAP06




void Map::loadMapDetails(int mapNumber) {
    //first empty map details
    numOfSprites = 0;
    maxPoints = 0;
    spriteList.clear();


    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {


            //load map
            switch(mapNumber) {
                case 0:
                    mapArray[i][j] = map01[i][j];
                    break;
                case 1:
                    mapArray[i][j] = map02[i][j];
                    break;
                case 2:
                    mapArray[i][j] = map03[i][j];
                    break;
                case 3:
                    mapArray[i][j] = map04[i][j];
                    break;
                case 4:
                    mapArray[i][j] = map05[i][j];
                    break;
                case 5:
                    mapArray[i][j] = map06[i][j];
                    break;
                default:
                    mapArray[i][j] = testMap[i][j];
            }



#ifdef TEST_MAP
            mapArray[i][j] = testMap[i][j];
#endif

#ifdef MAP01
            mapArray[i][j] = map01[i][j];
#endif
#ifdef MAP02
            mapArray[i][j] = map02[i][j];
#endif
#ifdef MAP03
            mapArray[i][j] = map03[i][j];
#endif
#ifdef MAP04
            mapArray[i][j] = map04[i][j];
#endif
#ifdef MAP05
            mapArray[i][j] = map05[i][j];
#endif
#ifdef MAP06
            mapArray[i][j] = map06[i][j];
#endif


            // + 0.5f to move the positions into center of the cell they occupy
            //ACTOR SPAWN
            if (mapArray[i][j] == '#') {
                Map::startingPosX = (float)i + 0.5f;
                Map::startingPosY = (float)j + 0.5f;

            }
            //BAG OF MONEY
            else if (mapArray[i][j] == '!') {
                Map::numOfSprites++;
                Map::maxPoints += 100;

                Sprite tempSprite{};
                tempSprite.posX = (float)i + 0.5f;
                tempSprite.posY = (float)j + 0.5f;
                tempSprite.textureChar = '!';
                tempSprite.score = 100;

                spriteList.push_back(tempSprite);
            }
            //GOLDEN KEY
            else if (mapArray[i][j] == '$') {
                Map::numOfSprites++;

                Sprite tempSprite{};
                tempSprite.posX = (float)i + 0.5f;
                tempSprite.posY = (float)j + 0.5f;
                tempSprite.textureChar = '$';


                spriteList.push_back(tempSprite);
            }
                //SILVER KEY
            else if (mapArray[i][j] == '&') {
                Map::numOfSprites++;

                Sprite tempSprite{};
                tempSprite.posX = (float)i + 0.5f;
                tempSprite.posY = (float)j + 0.5f;
                tempSprite.textureChar = '&';


                spriteList.push_back(tempSprite);
            }
            // FURTHER ELSE IF FOR OTHER TYPES OF ITEMS

        }
    }
}
