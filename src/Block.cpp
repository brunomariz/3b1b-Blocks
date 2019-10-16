#include "../inc/Block.h"

Block::Block (float maxWidth, float maxHeight, float mass, float velocity, float size):
mass(mass), velocity(velocity), size(size)
{

    this->position = new Point(0, 0);
    this->rectangle.setFillColor(sf::Color(110, 175, 231));
    this->rectangle.setSize(sf::Vector2f(size, size));

    this->setPosition(maxWidth, maxHeight, 0);
}

Block::Block()
{
}

Block::~Block()
{
}

float Block::getMomentum()
{
    return this->mass*this->velocity;
}

float Block::getVelocity()
{
    return this->velocity;
}

float Block::getMass()
{
    return this->mass;
}

void Block::setVelocity(float v)
{
    this->velocity = v;
}


// Returns position (distance from right wall to right side of rectangle)
float Block::getDistRW()
{
    return this->position->x;
}

float Block::getSize()
{
    return this->size;
}

// Cria retangulo na parte inferior da tela, posicionado a x de distancia da parte direita da tela
void Block::setPosition(float maxWidth, float maxHeight, float x)
{
    rectangle.setPosition(sf::Vector2f(maxWidth - x - this->size, maxHeight - this->size));
    this->position->x = maxWidth - this->rectangle.getPosition().x - this->size;
    this->position->y = maxHeight - this->rectangle.getPosition().y;
}

sf::RectangleShape Block::getRect(){
    return this->rectangle;
}




