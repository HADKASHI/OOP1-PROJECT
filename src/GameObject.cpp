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

Pacman :: Pacman(float edgeSize, sf::Vector2f position, char c, unsigned int score):
    MovingObjects(edgeSize, position, c), m_isKeyPressed(false), m_lives(LIVES),
    m_score(score), m_bonusTime(false) {}


void Pacman::keyDirection(sf::Keyboard::Key key)
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
            setDirection(LEFT);
            setRotation(0);
            setScale(-0.9f, 0.9f);
            break;
        }
        case sf::Keyboard::Right:
        {
            setDirection(RIGHT);
            setRotation(0);
            setScale(0.9f, 0.9f);
            break;
        }
        case sf::Keyboard::Up:
        {
            setDirection(UP);
            setScale(0.9f, 0.9f);
            setRotation(270);
            break;
        }
        case sf::Keyboard::Down:
            setDirection(DOWN);
            setScale(0.9f, 0.9f);
            setRotation(90);
            break;
        case sf::Keyboard::Space:
            setDirection({ 0, 0 });
            break;
        }
    }
    else
        m_isKeyPressed = false;
}
//---------------------------------------
void Pacman::update(sf::Time delta)
{
    m_bonusTime = false;

    if(!m_isKeyPressed)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            setDirection(LEFT);
            setRotation(0);
            setScale(-0.9f, 0.9f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            setDirection(RIGHT);
            setRotation(0);
            setScale(0.9f, 0.9f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            setDirection(UP);
            setScale(0.9f, 0.9f);
            setRotation(270);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            setDirection(DOWN);
            setScale(0.9f, 0.9f);
            setRotation(90);
        }
        else
        {
            setDirection({ 0 , 0 });
            return;
        }
    }

    move (getDirection() * delta.asSeconds() * PACMANSPEED);
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