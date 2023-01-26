#pragma once
#include "GameObject.h"
#include "PacmanState.h"

//class hierarchy of enemys
// each ghost chases in a different strategy and therefore they divided into different classes
// the ghost movement is handled by PacmanState class what leads to
// the ghost base class has a very wide and rich interface
//
class Ghost : public MovingObjects
{
public:
	Ghost(float edgeSize, sf::Vector2f position, char c);
	virtual void moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection) = 0;
	void gotStuck() { m_stuck = true; }
	bool isStuck() const { return m_stuck; }
	bool isAlternating() const { return m_alternating; }
	void freeToGo() { m_stuck = false; }
	void alternating() { m_alternating = true; }
	void notAlternating() { m_alternating = false; }
	void gainMomentum() { m_momentum++; }
	void stopMomentum() { m_momentum = 0; }
	unsigned int getMomentum() { return m_momentum; }
	sf::Vector2f getAlternatePostion() const { return m_alternatePosition; }
	sf::Vector2f getAlternateDirection() const { return m_alternateDirection; }
	void setAlternateDirection(sf::Vector2f direction) { m_alternateDirection = direction; }
	void setAlternatePosition(sf::Vector2f position) { m_alternatePosition = position; }
	void gotEaten();
	virtual void revive() = 0;
	unsigned int pointsReward() const { return m_score; }

private:
	bool m_stuck;
	unsigned int m_score;
	bool m_alternating;
	unsigned int m_momentum;
	sf::Vector2f m_alternatePosition;
	sf::Vector2f m_alternateDirection;
};
//----------------------------------------------------
class RedGhost : public Ghost
{
public:
	using Ghost::Ghost;
	void moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection) override;
	virtual void revive() override;
};
//----------------------------------------------------
class GreenGhost : public Ghost
{
public:
	using Ghost::Ghost;
	void moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection) override;
	virtual void revive() override;
};
//----------------------------------------------------
class PinkGhost : public Ghost
{
public:
	using Ghost::Ghost;
	void moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection) override;
	virtual void revive() override;
};
//----------------------------------------------------
class OrangeGhost : public Ghost
{
public:
	using Ghost::Ghost;
	void moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection) override;;
	virtual void revive() override;
};