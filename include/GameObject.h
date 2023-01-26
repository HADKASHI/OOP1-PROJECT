#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>

class GameObject : public sf::RectangleShape
{
public:
	GameObject(float edgeSize, sf::Vector2f position, char c);

private:

};
//---------------------------------------------------
class StaticObjects : public GameObject {
public:
	StaticObjects(float edgeSize, sf::Vector2f position, char c);
	bool beenEaten() const { return m_beenEaten; }
	void isEaten() { m_beenEaten = true; } 

private:
	bool m_beenEaten;
};
//---------------------------------------------------
class MovingObjects : public GameObject 
{
public:
	MovingObjects(float edgeSize, sf::Vector2f position, char c);
	sf::Vector2f getDirection() const { return m_direction; }
	void setDirection(sf::Vector2f direction) { m_direction = direction; }
	void reset() { setPosition(m_startPoint); }
	sf::Vector2f getStartPoint() const { return m_startPoint; }
	bool isDead() const { return !m_alive; }
	void alive() { m_alive = true; }
	virtual void gotEaten() = 0;
	void died() { m_alive = false; }

private:
	sf::Vector2f m_direction;
	sf::Vector2f m_startPoint;
	bool m_alive;
};
//---------------------------------------------------
class Pacman: public MovingObjects
{
public:
	Pacman(float edgeSize, sf::Vector2f position, char c, unsigned int score);
	void keyDirection(sf::Keyboard::Key key);
	void update(sf::Time delta);
	void notMoving(sf::Keyboard::Key key);
	void addPoints(unsigned int points) { m_score += points; }
	void gotEaten() { m_lives--; this->reset(); this->died(); }
	void addLives() { m_lives++; }
	void addTime() { m_bonusTime = true; }
	unsigned int getBonusTime() const { if (m_bonusTime) return TIMEBONUS; return 0; }
	unsigned int getScore() const { return m_score; }
	unsigned int getLives() const { return m_lives; }


private:
	unsigned int m_bonusTime;
	bool m_isKeyPressed;
	unsigned int m_lives;
	unsigned int m_score;
};

//----------------------------------------------------
class Wall : public StaticObjects
{
public:
	Wall(float edgeSize, sf::Vector2f position, char c, bool height = false, bool width = false);
};
//----------------------------------------------------
class Door : public StaticObjects
{
public:
	using StaticObjects::StaticObjects;
};
//----------------------------------------------------
class Key : public StaticObjects
{
public:
	using StaticObjects::StaticObjects;
	unsigned int pointsReward() { return KEYSPOINTS; }
};

//-------------	---------------------------------------
class Cookie : public StaticObjects
{
public:
	Cookie(float edgeSize, sf::Vector2f position, char c);
	unsigned int pointsReward() { return COOKIEPOINTS; }
};

//----------------------------------------------------
class Present : public StaticObjects
{
public:
	using StaticObjects::StaticObjects;
	virtual unsigned int pointsReward() const = 0;
};
//----------------------------------------------------
class SuperPresent : public Present
{
public:
	using Present::Present;
	virtual unsigned int pointsReward() const override { return 50; }
};
class FreezePresent : public Present
{
public:
	using Present::Present;
	virtual unsigned int pointsReward() const override { return 30; }
};
class TimePresent : public Present
{
public:
	using Present::Present;
	virtual unsigned int pointsReward() const override { return 10; }
};
class LivesPresent : public Present
{
public:
	using Present::Present;
	virtual unsigned int pointsReward() const override { return 20; }
};

