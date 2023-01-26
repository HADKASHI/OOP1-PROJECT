#include "Ghost.h"
#include "Resources.h"

Ghost::Ghost(float edgeSize, sf::Vector2f position, char c) :
    MovingObjects(edgeSize, position, c),
    m_stuck(false), m_alternating(false), m_momentum(0), m_score(GHOSTPOINTS) {}

//void Ghost::gotStuck(sf::Vector2f direction)
//{
//    if (direction == UP)
//        m_stuckUp = true;
//    else if (direction == DOWN)
//        m_stuckDown = true;
//    else if (direction == RIGHT)
//        m_stuckRight = true;
//    else if (direction == LEFT)
//        m_stuckLeft = true;
//}
//
//bool Ghost::isStuck(sf::Vector2f direction) const
//{
//    if (direction == UP)
//        return m_stuckUp;
//    else if (direction == DOWN)
//        return m_stuckDown;
//    else if (direction == RIGHT)
//        return m_stuckRight;
//    else if (direction == LEFT)
//        return m_stuckLeft;
//}

//float distance(sf::Vector2f point1, sf::Vector2f point2);
//void Ghost::update(sf::Time delta, sf::Vector2f targetPosition)
//{
//    //ghost did NOT reached to its target location
//    if (m_alternating && !this->getGlobalBounds().contains(m_alternatePosition))
//    {
//        if (this->isStuck())
//            alternateMove(delta);
//        else
//            move(m_alternateDirection * delta.asSeconds() * 50.f);
//    }
//
//    //ghost got stucked in prev try so it alternating its movment
//    else if (this->isStuck())
//    {
//        this->freeToGo();
//        alternateMove(delta);
//    }
//
//    else
//    {
//        auto up = this->getPosition() + UP + sf::Vector2f{ 0, -10 };
//        auto down = this->getPosition() + DOWN + sf::Vector2f{ 0, 10 };
//        auto right = this->getPosition() + RIGHT + sf::Vector2f{ 10, 0 };
//        auto left = this->getPosition() + LEFT + sf::Vector2f{ -10, 0 };
//
//        auto minDistance = distance(right, targetPosition);
//        auto direction = RIGHT;
//        if (distance(left, targetPosition) < minDistance)
//        {
//            minDistance = distance(left, targetPosition);
//            direction = LEFT;
//        }
//        if (distance(up, targetPosition) < minDistance)
//        {
//            minDistance = distance(up, targetPosition);
//            direction = UP;
//        }
//        if (distance(down, targetPosition) < minDistance)
//        {
//            minDistance = distance(down, targetPosition);
//            direction = DOWN;
//        }
//
//        //if (isStuck(direction) || direction == this->getDirection() * -1.f)
//        //    scatter(delta);
//        if (direction != this->getDirection() * -1.f /*&& direction != m_alternateDirection * -1.f*/)
//        {
//            setDirection(direction);
//        }
//
//        move(getDirection() * delta.asSeconds() * 50.f);
//        m_alternating = false;
//        this->freeToGo();
//        m_momentum++;
//        if (m_momentum >= 200)
//            m_alternateDirection = getDirection();
//    }
//}
//
//float distance(sf::Vector2f point1, sf::Vector2f point2)
//{
//    return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2) * 1.0);
//}
//
//void Ghost::alternateMove(sf::Time delta)
//{
//    m_alternating = true;
//    this->freeToGo();
//
//    if (m_momentum > 200 || m_momentum < 1)
//        randMove(delta);
//
//    else if (getDirection() == UP || getDirection() == DOWN)
//    {
//        if (m_alternateDirection != LEFT)
//        {
//            m_alternatePosition = sf::Vector2f({ getPosition().x + getSize().x * 1.2f, getPosition().y });
//            m_alternateDirection = RIGHT;
//            this->setDirection(RIGHT);
//            move(m_alternateDirection * delta.asSeconds() * 50.f);
//        }
//        else
//        {
//            m_alternatePosition = sf::Vector2f({ getPosition().x - getSize().x * 1.2f, getPosition().y });
//            m_alternateDirection = LEFT;
//            this->setDirection(LEFT);
//            move(m_alternateDirection * delta.asSeconds() * 50.f);
//        }
//    }
//    else
//    {
//        if (m_alternateDirection != UP)
//        {
//            m_alternatePosition = sf::Vector2f({ getPosition().x, getPosition().y + getSize().y * 1.2f });
//            m_alternateDirection = DOWN;
//            this->setDirection(DOWN);
//            move(m_alternateDirection * delta.asSeconds() * 50.f);
//        }
//        else
//        {
//            m_alternatePosition = sf::Vector2f({ getPosition().x, getPosition().y - getSize().y * 1.2f });
//            m_alternateDirection = UP;
//            this->setDirection(UP);
//            move(m_alternateDirection * delta.asSeconds() * 50.f);
//        }
//    }
//
//    m_momentum = 0;
//}
//
//void Ghost::randMove(sf::Time delta)
//{
//    if (getDirection() == UP || getDirection() == DOWN)
//    {
//        if (rand() % 2 == 1)
//        {
//            m_alternatePosition = sf::Vector2f({ getPosition().x + getSize().x * 1.2f, getPosition().y });
//            m_alternateDirection = RIGHT;
//            this->setDirection(RIGHT);
//            move(m_alternateDirection * delta.asSeconds() * 50.f);
//        }
//        else
//        {
//            m_alternatePosition = sf::Vector2f({ getPosition().x - getSize().x * 1.2f, getPosition().y });
//            m_alternateDirection = LEFT;
//            this->setDirection(LEFT);
//            move(m_alternateDirection * delta.asSeconds() * 50.f);
//        }
//    }
//    else
//    {
//        if (rand() % 2 == 0)
//        {
//            m_alternatePosition = sf::Vector2f({ getPosition().x, getPosition().y + getSize().y * 1.2f });
//            m_alternateDirection = DOWN;
//            this->setDirection(DOWN);
//            move(m_alternateDirection * delta.asSeconds() * 50.f);
//        }
//        else
//        {
//            m_alternatePosition = sf::Vector2f({ getPosition().x, getPosition().y - getSize().y * 1.2f });
//            m_alternateDirection = UP;
//            this->setDirection(UP);
//            move(m_alternateDirection * delta.asSeconds() * 50.f);
//        }
//    }
//}


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