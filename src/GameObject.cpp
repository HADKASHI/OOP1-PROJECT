#pragma once
#include "GameObject.h"
#include "Resources.h"
#include <iostream>

GameObject::GameObject(float edgeSize, sf::Vector2f position, char c)
	:sf::RectangleShape({ edgeSize, edgeSize })
{
	setPosition(position);
	setTexture(&Resources::instance().getTexture(c));
}


MovingObjects::MovingObjects(float edgeSize, sf::Vector2f position, char c) :
    GameObject(edgeSize, position, c), m_direction({ 0 , 0 }), m_alive(true)
{
    setOrigin(getSize() / 2.f);
    setPosition({ getPosition().x + 0.5f * edgeSize,
        getPosition().y + 0.5f * edgeSize });

    m_startPoint = this->getPosition();

    setScale({ 0.9f, 0.9f });
}

StaticObjects::StaticObjects(float edgeSize, sf::Vector2f position, char c) :
    GameObject(edgeSize, position, c), m_beenEaten(false)
{ }


Cookie::Cookie(float edgeSize, sf::Vector2f position, char c):
    StaticObjects( edgeSize, position, c)
{
    setOrigin(getSize() / 2.f);
    setPosition({ getPosition().x + 0.5f * edgeSize,
        getPosition().y + 0.5f * edgeSize });
    setScale({ 0.5,0.5 });
}


Wall::Wall(float edgeSize, sf::Vector2f position, char c, bool height, bool width) :
    StaticObjects(edgeSize, position, c)
{
    setOrigin(getSize() / 2.f);
    setPosition({ getPosition().x + 0.5f * edgeSize,
        getPosition().y + 0.5f * edgeSize });

    setScale({float( 1 - 0.3 * width) , float(1 - 0.3 * height) });
}