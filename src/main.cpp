#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "../inc/Block.h"
#include "../inc/Point.h"

int main()
{
    // Gets video mode
    sf::VideoMode currentMode = sf::VideoMode::getDesktopMode();
    
    // Creates window
    sf::RenderWindow window;
    window.create(currentMode, "3b1b's pi approximation mehtod",
                  /* sf::Style::Titlebar |
                  sf::Style::Resize |
                  sf::Style::Close */
                  sf::Style::Fullscreen);

    int wx = window.getSize().x;
    int wy = window.getSize().y;

    Block* b1 = new Block(wx, wy, 100, 1.5, 150);
    Block* b2 = new Block(wx, wy, 1, 0, 100);


    b1->setPosition(wx, wy, wx/4);
    b2->setPosition(wx, wy, wx/2 + 150);

    window.setFramerateLimit(60);

    sf::Font garamond;

    if ( !garamond.loadFromFile("data/Garamond.ttf"))
    {
        std::cout << "Error loading file" << std::endl;

        system( "pause" );
    }

    sf::Text hitNumber;
    sf::Text title;
    sf::Text textHits;
    sf::Text massRatio;

    std::string mrat = "m1/m2 = ";
    mrat += std::to_string(int(b1->getMass()/b2->getMass()));
    const int hitposition = 220 -wx/2;
    
    massRatio.setFont(garamond);
    massRatio.setString(mrat);
    massRatio.setCharacterSize(64);
    massRatio.setFillColor(sf::Color::Black);
    massRatio.setOrigin( 185 -wx/2, -150 -wy/5);

    textHits.setFont(garamond);
    textHits.setString("#hits:");
    textHits.setCharacterSize(128);
    textHits.setFillColor(sf::Color::Black);
    textHits.setOrigin( hitposition, -wy/5);

    title.setFont(garamond);
    title.setString("3blue1brown's pi approximation method");
    title.setCharacterSize(72);
    title.setFillColor(sf::Color::Black);
    title.setOrigin(  565 -wx/2, 60 -wy/5);
    
    hitNumber.setFont(garamond);
    hitNumber.setString("0");
    hitNumber.setCharacterSize(128);
    hitNumber.setFillColor(sf::Color::Black);
    hitNumber.setOrigin(hitposition - 300, -5 -wy/5);
    
    sf::Event event;

    float aux;
    int hits = 0;
    while(window.isOpen())
    {
        while(window.pollEvent(event)) // "event = Dequeue(pollEvent)"
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        window.close();
                    }
                    break;
                default:
                    break;
            }
        }
        window.clear(sf::Color(142, 106, 45));
        window.draw(b1->getRect());
        window.draw(b2->getRect());
        window.draw(hitNumber);
        window.draw(title);
        window.draw(textHits);
        window.draw(massRatio);
        window.display();

        b1->setPosition(wx, wy, b1->getDistRW() + b1->getVelocity());
        b2->setPosition(wx, wy, b2->getDistRW() + b2->getVelocity());

        if(b2->getDistRW() - b1->getDistRW() <= b1->getSize())
        {
            hits++;
            hitNumber.setString(std::to_string(hits));

            aux = b2->getVelocity();
            b2->setVelocity( ((2*b1->getMass()*b1->getVelocity()) + b2->getVelocity()*
                                (b2->getMass() - b1->getMass()))/(b2->getMass() + b1->getMass()));  
            b1->setVelocity(aux + b2->getVelocity() - b1->getVelocity());
        }

        if(b2->getDistRW() + b2->getSize() >= wx)
        {
            hits++;
            hitNumber.setString(std::to_string(hits));
            b2->setVelocity(-b2->getVelocity());
        }
            
    }

    std::cout << "\tCreating a window!" << std::endl;

    return 0;
}
