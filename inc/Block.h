#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

#include "Point.h"

class Block{
public:
    Block(float maxWidth, float maxHeight, float mass, float velocity, float size);

    Block();
    ~Block();

    float getDistRW();
    float getSize();
    float getMomentum();
    float getVelocity();
    float getMass();
    void setVelocity(float v);

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