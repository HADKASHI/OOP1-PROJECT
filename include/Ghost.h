#pragma once
#include "GameObject.h"

//----------------------------------------------------
class Ghost : public MovingObjects
{
public:
	Ghost(float edgeSize, sf::Vector2f position, char c);
	void update(sf::Time delta, sf::Vector2f targetPosition);
	virtual void moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection) = 0;
	void gotStuck() { m_stuck = true; }
	bool isStuck() const { return m_stuck; }
	void scatter(sf::Time delta);
	void setMomentum(sf::Vector2f direction) { m_momentum = direction; }
	void freeToGo() {/* m_stuckDown = m_stuckLeft = m_stuckRight = m_stuckUp = true;*/m_stuck = false; }
	sf::Vector2f setMomentum() const { return m_momentum; }
	void alternateMove(sf::Time delta) ;

private:
	bool m_stuck;
	/*bool m_stuckRight;
	bool m_stuckLeft;
	bool m_stuckUp;
	bool m_stuckDown;*/
	bool m_alternating;
	sf::Vector2f m_momentum;
	sf::Vector2f m_alternatePosition;
	sf::Vector2f m_alternateDirection;
};
//----------------------------------------------------
class RedGhost : public Ghost
{
public:
	using Ghost::Ghost;
	void moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection) override;

	//	void move(Controller& controller) override;
};
//----------------------------------------------------
class GreenGhost : public Ghost
{
public:
	using Ghost::Ghost;
	void moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection);

	//	void move(Controller& controller) override;
};//----------------------------------------------------
class PinkGhost : public Ghost
{
public:
	using Ghost::Ghost;
	void moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection) override;

	//	void move(Controller& controller) override;
};//----------------------------------------------------
class OrangeGhost : public Ghost
{
public:
	using Ghost::Ghost;
	void moveGhost(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection);
	//	void move(Controller& controller) override;
};