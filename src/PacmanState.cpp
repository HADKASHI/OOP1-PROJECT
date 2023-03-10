#pragma once
#include "PacmanState.h"
#include "Ghost.h"
#include "Resources.h"

PacmanState& PacmanState:: instance()
{
    static auto pacmanState = PacmanState();
    return pacmanState;
}

void PacmanState::superState()
{
    m_superPacman = true;
    m_superTimer.restart();
}

void PacmanState::setTexture(Ghost& ghost)
{
    if (m_superPacman)
        ghost.setTexture(&Resources::instance().getTexture('f'), true);

    else if (m_freeze)
    {
        ghost.setTexture(&Resources::instance().getTexture('F'), true);
    }

    else
    {
        if (std::string(typeid(ghost).name()) == "class RedGhost")
            ghost.setTexture(&Resources::instance().getTexture('r'), true);
        else if (std::string(typeid(ghost).name()) == "class PinkGhost")
            ghost.setTexture(&Resources::instance().getTexture('p'), true);
        else if (std::string(typeid(ghost).name()) == "class GreenGhost")
            ghost.setTexture(&Resources::instance().getTexture('g'), true);
        else if (std::string(typeid(ghost).name()) == "class OrangeGhost")
            ghost.setTexture(&Resources::instance().getTexture('o'), true);
    }
}

float distance(sf::Vector2f point1, sf::Vector2f point2);
sf::Vector2f maxDistanceDirection(Ghost& ghost, sf::Vector2f targetPosition);
sf::Vector2f minDistanceDirection(Ghost& ghost, sf::Vector2f targetPosition);

void PacmanState::move(Ghost& ghost, sf::Time delta, sf::Vector2f targetPosition)
{
    if (m_freeze)
    {
        if (m_freezeTimer.getElapsedTime().asSeconds() > FREEZETIMER)
            m_freeze = false;
        else
            return;
    }

    if (m_superPacman && m_superTimer.getElapsedTime().asSeconds() > SUPERTIMER)
    {
        m_superPacman = false;
    }

    if (ghost.isDead())
    {
        //ghost got to its home
        if (ghost.getGlobalBounds().contains(ghost.getStartPoint()))
            ghost.revive();
        else
            goHome(ghost, delta);

        return;
    }

    //ghost did NOT reached to its target location
    if (ghost.isAlternating() && !ghost.getGlobalBounds().contains(ghost.getAlternatePostion()))
    {
        //got stuck again while trying to pass an obstacle
        if (ghost.isStuck())
            alternateMove(ghost, delta);
        //keep trys to get around the obstacle
        else
            ghost.move(ghost.getAlternateDirection() * delta.asSeconds() * GHOST_SPEED);
    }

    //ghost got stucked in prev try so it alternating its movment
    else if (ghost.isStuck())
    {
        ghost.freeToGo();
        alternateMove(ghost, delta);
    }

    //free to choose a direction
    else
    {
        sf::Vector2f direction;
        if (m_superPacman)
            direction = maxDistanceDirection(ghost, targetPosition);
        else
            direction = minDistanceDirection(ghost, targetPosition);

        //going to choosed firection iff its not reversing and not immediate turn (creates a continous motion)
        if (direction != ghost.getDirection() * -1.f && direction != ghost.getAlternateDirection() * -1.f 
            && ghost.getMomentum() >= MOMENTUM)
        {
            if (direction != ghost.getDirection())
                ghost.stopMomentum();

            ghost.setDirection(direction);
            ghost.setAlternateDirection(ghost.getDirection());
        }

        ghost.move(ghost.getDirection() * delta.asSeconds() * GHOST_SPEED);
        ghost.notAlternating();
        ghost.freeToGo();
        ghost.gainMomentum();
    }
}

float distance(sf::Vector2f point1, sf::Vector2f point2)
{
    return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2) * 1.0);
}

void PacmanState::alternateMove(Ghost &ghost, sf::Time delta)
{
    ghost.alternating();
    ghost.freeToGo();

    //if its walked for a while or stuck in a corner moves randomly
    if (ghost.getMomentum() > MOMENTUM || ghost.getMomentum() < 1)
        randMove(ghost, delta);


    //needs to keep its momentum since it couldnt pass the obstacle
    else if (ghost.getDirection() == UP || ghost.getDirection() == DOWN)
    {
        if (ghost.getAlternateDirection() != LEFT)
        {
            ghost.setAlternatePosition(sf::Vector2f({ ghost.getPosition().x + ghost.getSize().x * 1.2f, ghost.getPosition().y }));
            ghost.setAlternateDirection(RIGHT);
            ghost.setDirection(RIGHT);
            ghost.move(ghost.getAlternateDirection() * delta.asSeconds() * GHOST_SPEED);
        }
        else
        {
            ghost.setAlternatePosition(sf::Vector2f({ ghost.getPosition().x - ghost.getSize().x * 1.2f, ghost.getPosition().y }));
            ghost.setAlternateDirection(LEFT);
            ghost.setDirection(LEFT);
            ghost.move(ghost.getAlternateDirection() * delta.asSeconds() * GHOST_SPEED);
        }
    }
    else
    {
        if (ghost.getAlternateDirection() != UP)
        {
            ghost.setAlternatePosition(sf::Vector2f({ ghost.getPosition().x, ghost.getPosition().y + ghost.getSize().y * 1.2f }));
            ghost.setAlternateDirection(DOWN);
            ghost.setDirection(DOWN);
            ghost.move(ghost.getAlternateDirection() * delta.asSeconds() * GHOST_SPEED);
        }
        else
        {
            ghost.setAlternatePosition(sf::Vector2f({ ghost.getPosition().x, ghost.getPosition().y - ghost.getSize().y * 1.2f }));
            ghost.setAlternateDirection(UP);
            ghost.setDirection(UP);
            ghost.move(ghost.getAlternateDirection() * delta.asSeconds() * GHOST_SPEED);
        }
    }

    ghost.stopMomentum();
}

void PacmanState::randMove(Ghost & ghost,sf::Time delta)
{
    if (ghost.getDirection() == UP || ghost.getDirection() == DOWN)
    {
        if (rand() % 2 == 1)
        {
            ghost.setAlternatePosition(sf::Vector2f({ ghost.getPosition().x + ghost.getSize().x * 1.2f, ghost.getPosition().y }));
            ghost.setAlternateDirection(RIGHT);
            ghost.setDirection(RIGHT);
            ghost.move(ghost.getAlternateDirection() * delta.asSeconds() * GHOST_SPEED);
        }
        else
        {
            ghost.setAlternatePosition(sf::Vector2f({ ghost.getPosition().x - ghost.getSize().x * 1.2f, ghost.getPosition().y }));
            ghost.setAlternateDirection(LEFT);
            ghost.setDirection(LEFT);
            ghost.move(ghost.getAlternateDirection() * delta.asSeconds() * GHOST_SPEED);
        }
    }
    else
    {
        if (rand() % 2 == 0)
        {
            ghost.setAlternatePosition(sf::Vector2f({ ghost.getPosition().x, ghost.getPosition().y + ghost.getSize().y * 1.2f }));
            ghost.setAlternateDirection(DOWN);
            ghost.setDirection(DOWN);
            ghost.move(ghost.getAlternateDirection() * delta.asSeconds() * GHOST_SPEED);
        }
        else
        {
            ghost.setAlternatePosition(sf::Vector2f({ ghost.getPosition().x, ghost.getPosition().y - ghost.getSize().y * 1.2f }));
            ghost.setAlternateDirection(UP);
            ghost.setDirection(UP);
            ghost.move(ghost.getAlternateDirection() * delta.asSeconds() * GHOST_SPEED);
        }
    }
}

sf::Vector2f minDistanceDirection(Ghost &ghost, sf::Vector2f targetPosition)
{
    auto up = ghost.getPosition() + UP + sf::Vector2f{ 0, -10 };
    auto down = ghost.getPosition() + DOWN + sf::Vector2f{ 0, 10 };
    auto right = ghost.getPosition() + RIGHT + sf::Vector2f{ 10, 0 };
    auto left = ghost.getPosition() + LEFT + sf::Vector2f{ -10, 0 };

    auto minDistance = distance(right, targetPosition);
    auto direction = RIGHT;
    if (distance(left, targetPosition) < minDistance)
    {
        minDistance = distance(left, targetPosition);
        direction = LEFT;
    }
    if (distance(up, targetPosition) < minDistance)
    {
        minDistance = distance(up, targetPosition);
        direction = UP;
    }
    if (distance(down, targetPosition) < minDistance)
    {
        minDistance = distance(down, targetPosition);
        direction = DOWN;
    }

    return direction;
}

sf::Vector2f maxDistanceDirection(Ghost& ghost, sf::Vector2f targetPosition)
{
    auto up = ghost.getPosition() + UP + sf::Vector2f{ 0, -10 };
    auto down = ghost.getPosition() + DOWN + sf::Vector2f{ 0, 10 };
    auto right = ghost.getPosition() + RIGHT + sf::Vector2f{ 10, 0 };
    auto left = ghost.getPosition() + LEFT + sf::Vector2f{ -10, 0 };

    auto maxDistance = distance(right, targetPosition);
    auto direction = RIGHT;
    if (distance(left, targetPosition) > maxDistance)
    {
        maxDistance = distance(left, targetPosition);
        direction = LEFT;
    }
    if (distance(up, targetPosition) > maxDistance)
    {
        maxDistance = distance(up, targetPosition);
        direction = UP;
    }
    if (distance(down, targetPosition) > maxDistance)
    {
        maxDistance = distance(down, targetPosition);
        direction = DOWN;
    }

    return direction;
}

void PacmanState::handleCollision(Ghost& ghost) const
{
    ghost.gotEaten();
}

void PacmanState::goHome(Ghost& ghost, sf::Time delta) const
{
    sf::Vector2f direction;
    direction = minDistanceDirection(ghost, ghost.getStartPoint());

    ghost.move(direction * delta.asSeconds() * GHOST_SPEED * 1.5f);
}
