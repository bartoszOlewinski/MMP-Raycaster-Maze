//
// Created by barto on 18/02/2022.
//

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>

class DebugConsole {
private:
    sf::RenderWindow* windowPtr{};
    bool isActive = false;
    sf::Text text;
    sf::Font font;
    sf::RectangleShape rectangleShape;

    std::string optionListStr = "\n1. actor debug on/off.\n2. agent debug on/off.\n"
                                "3. music on/off.";


public:
    explicit DebugConsole(sf::RenderWindow* wPtr) {
        windowPtr = wPtr;
    }

    void activateDebug() {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {




            if (!isActive)
                isActive = true;
            else isActive = false;

            font.loadFromFile("arial.ttf");
            text.setFont(font);

            std::string activationStr = "===========CONSOLE ACTIVATED===========";
            activationStr += optionListStr;
            text.setString(activationStr);
            text.setPosition(650, 700);
            text.setFillColor(sf::Color::Yellow);
            text.setCharacterSize(15);

            rectangleShape.setFillColor(sf::Color::Blue);
            rectangleShape.setSize(sf::Vector2<float>(360,200));
            rectangleShape.setPosition(650, 700);
        }

    }

    void commandOpener() {
        if (isActive) {
                windowPtr->draw(rectangleShape);

                windowPtr->draw(text);

                commandListener();
        }
    }

    void commandListener() {
        //toggle actor debug debugText
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {


        }

        //toggle agent debug debugText
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {


        }

        //toggle music
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {


        }

    }


};

