#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

#include "Point.h"

class Block{
public:
    // Constructor
    // @param maxWidth Maximum width of the screen
    // @param maxHeight Maximum height of the screen
    // @param mass Mass of the block
    // @param velocity Inicial velocity of the block
    // @param size Size of blocks sides
    Block(float maxWidth, float maxHeight, float mass, float velocity, float size);

    Block();
    ~Block();

    float getDistRW(); // Returns the distance from the block to the right wall
    float getSize();
    float getMomentum();
    float getVelocity();
    float getMass();
    void setVelocity(float v); // Sets the velocity of the block to v

    // Sets the position of the right side of the block to the bottom of the screen, 
    //x away from the right wall
    void setPosition(float maxWidth, float maxHeight, float x); 

    sf::RectangleShape getRect();

private:

    Point* position;
    float mass;
    float velocity;
    float size;

    sf::RectangleShape rectangle;



};

#endif