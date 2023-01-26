#pragma once
#include "Ghost.h"
#include "Resources.h"

Ghost::Ghost(float edgeSize, sf::Vector2f position, char c) :
    MovingObjects(edgeSize, position, c),
    m_stuck(false), m_alternating(false), m_momentum(0), m_score(GHOSTPOINTS) {}

void RedGhost::moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection)
{
    PacmanState::instance().move(*this, delta, pacmanPosition);
}

void PinkGhost::moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection)
{
    if (pacmanDirection != sf::Vector2f{ 0, 0 })
        pacmanDirection = pacmanDirection;

    PacmanState::instance().move(*this, delta, pacmanPosition + (pacmanDirection * getSize().x * 4.f) );
}

void OrangeGhost::moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection)
{
    PacmanState::instance().move(*this, delta, pacmanPosition);
}

void GreenGhost::moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection)
{
    PacmanState::instance().move(*this, delta, pacmanPosition + (pacmanDirection * getSize().x * 4.f));
}

void Ghost::gotEaten()
{
    this->setTexture(&Resources::instance().getTexture('e'));
    this->died();
}

void RedGhost::revive()
{
    this->setTexture(&Resources::instance().getTexture('r'));
    this->alive();
}

void PinkGhost::revive()
{
    this->setTexture(&Resources::instance().getTexture('p'));
    this->alive();
}

void OrangeGhost::revive()
{
    this->setTexture(&Resources::instance().getTexture('o'));
    this->alive();
}

void GreenGhost::revive()
{
    this->setTexture(&Resources::instance().getTexture('g'));
    this->alive();
}