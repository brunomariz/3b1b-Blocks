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

    int wx = window.getSize().x; // Width of the screen
    int wy = window.getSize().y; // Height of the screen

    // Create block objects with masses 100 and 1
    Block* b1 = new Block(wx, wy, 100, 1.5, 150); 
    Block* b2 = new Block(wx, wy, 1, 0, 100);

    // Set the blocks positions
    b1->setPosition(wx, wy, wx/4); // Position block 1 1/4 of the screens width away from the right side
    b2->setPosition(wx, wy, wx/2 + 150); // Position block 2 1/2 of the screens width away from the right
                                         // side plus 150 pixels

    window.setFramerateLimit(60); // Set framerate limit for window 


    // Create font object to use in texts
    sf::Font garamond;

    if ( !garamond.loadFromFile("data/Garamond.ttf"))
    {
        std::cout << "Error loading file" << std::endl;

        system( "pause" );
    }

    // Create text objects
    sf::Text hitNumber; // Text object to display the number of hits so far.
                        // Updated every window iteration
    sf::Text title; // Text object to display the string "3blue1brown's pi approximation method"
    sf::Text textHits; // Text object to display the string "#hits:"
    sf::Text massRatio; // Text object to display the mass ratio

    std::string mrat = "m1/m2 = "; // String that'll be used by the massRatio object to display
                                   // "m1/m2 = " followed by the mass ratio on the string
    mrat += std::to_string(int(b1->getMass()/b2->getMass())); // Add the ratio to the string
                                                              // Mass ratio converted to integer in order
                                                              // to omit decimal cases for aesthetic purposes
    const int hitposition = 220 -wx/2; // Variable that contains the position of textHits
                                       // used to easily align the strings "hits:" and the number of
                                       // hits displayed by the object hitNumber
    
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

    float aux; // Saves the velocity of block 2 in order to make later calculations for b1's velocity
    int hits = 0; // Counts the number of times that block 2 hits block 1 or the wall
    // Window loop
    while(window.isOpen())
    {
        // Process events
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                // Close window if spacebar is pressed
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
        window.clear(sf::Color(142, 106, 45)); // Clear previous window
        window.draw(b1->getRect()); // Draw block 1
        window.draw(b2->getRect()); // Draw block 2
        // Draw strings
        window.draw(hitNumber); 
        window.draw(title);
        window.draw(textHits);
        window.draw(massRatio);
        window.display(); // Display everything on the window

        // Set new positions based on velocity
        b1->setPosition(wx, wy, b1->getDistRW() + b1->getVelocity());
        b2->setPosition(wx, wy, b2->getDistRW() + b2->getVelocity());

        // If the blocks touched
        if(b2->getDistRW() - b1->getDistRW() <= b1->getSize())
        {
            hits++; // Increment hit count
            hitNumber.setString(std::to_string(hits)); // Update string in hitNumber object

            aux = b2->getVelocity();
            // Set new velocities according to elastic collision laws
            b2->setVelocity( ((2*b1->getMass()*b1->getVelocity()) + b2->getVelocity()*
                                (b2->getMass() - b1->getMass()))/(b2->getMass() + b1->getMass()));  
            b1->setVelocity(aux + b2->getVelocity() - b1->getVelocity());
        }

        // If block 2 hits the left wall
        if(b2->getDistRW() + b2->getSize() >= wx)
        {
            hits++; // Increment hit count
            hitNumber.setString(std::to_string(hits)); // Update string in hitNumber object
            b2->setVelocity(-b2->getVelocity()); // Change block 2's velocity according to elastic collision laws
        }
            
    }
    return 0;
}
