#include "GameObject.h"
#include "Graphics.h"
#include <iostream>

GameObject::GameObject(float edgeSize, sf::Vector2f position, char c)
	:sf::RectangleShape({ edgeSize, edgeSize })
{
	setPosition(position);
	setTexture(&Graphics::instance().getTexture(c));
}


MovingObjects::MovingObjects(float edgeSize, sf::Vector2f position, char c) :
    GameObject(edgeSize, position, c)
{
    setOrigin(getSize() / 2.f);
    setPosition({ getPosition().x + 0.5f * edgeSize,
        getPosition().y + 0.5f * edgeSize });
}


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

Pacman :: Pacman(float edgeSize, sf::Vector2f position, char c, unsigned int score):
    MovingObjects(edgeSize, position, c), m_isKeyPressed(false), m_lives(3), m_score(score) {}


void Pacman::setDirection(sf::Keyboard::Key key)
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && key != sf::Keyboard::Up) ||
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && key != sf::Keyboard::Down) ||
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && key != sf::Keyboard::Left) ||
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && key != sf::Keyboard::Right))
    {
        m_isKeyPressed = true;

        switch (key)
        {
        case sf::Keyboard::Left:
        {
            m_direction = { -1, 0 };
            setRotation(0);
            setScale(-1, 1);
            break;
        }
        case sf::Keyboard::Right:
        {
            m_direction = { 1, 0 };
            setRotation(0);
            setScale(1, 1);
            break;
        }
        case sf::Keyboard::Up:
        {
            m_direction = { 0, -1 };
            setScale(1, 1);
            setRotation(270);
            break;
        }
        case sf::Keyboard::Down:
            m_direction = { 0, 1 };
            setScale(1, 1);
            setRotation(90);
            break;
        case sf::Keyboard::Space:
            m_direction = { 0, 0 };
            break;
        }
    }
    else
        m_isKeyPressed = false;
}
//---------------------------------------
void Pacman::update(sf::Time delta)
{
    auto PacmanSpeed = 60.f;

    if(!m_isKeyPressed)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            m_direction = { -1, 0 };
            setRotation(0);
            setScale(-1, 1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            m_direction = { 1, 0 };
            setRotation(0);
            setScale(1, 1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            m_direction = { 0, -1 };
            setScale(1, 1);
            setRotation(270);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            m_direction = { 0, 1 };
            setScale(1, 1);
            setRotation(90);
        }
        else
            return;
    }

    move (m_direction * delta.asSeconds() * PacmanSpeed);
}
//--------------------------------------
void Pacman::notMoving(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up ||
        key == sf::Keyboard::Down ||
        key == sf::Keyboard::Left ||
        key == sf::Keyboard::Right)
        m_isKeyPressed = false;
}



