#include "Pacman.h"

Pacman::Pacman(float edgeSize, sf::Vector2f position, char c, unsigned int score) :
    MovingObjects(edgeSize, position, c), m_isKeyPressed(false), m_lives(LIVES),
    m_score(score), m_bonusTime(false) {}


void Pacman::keyDirection(sf::Keyboard::Key key)
{
    //overrides a pressed key so the last arrow pressed will directs pacman
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

    if (!m_isKeyPressed)
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

    move(getDirection() * delta.asSeconds() * PACMANSPEED);
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