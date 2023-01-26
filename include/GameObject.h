#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>

//class hierarchy that holds all game objects
//it splits into two main branches: Statics and Movings
//under Statics you'll find cookies, doors and stuff like those
//under Movings you'll find ghost and pacman
//
//ALL NONE LEAVES ARE ABSTRACT!
class GameObject : public sf::RectangleShape
{
public:
	GameObject(float edgeSize, sf::Vector2f position, char c);
	virtual void gotEaten() = 0;

private:

};
//---------------------------------------------------
class StaticObjects : public GameObject {
public:
	StaticObjects(float edgeSize, sf::Vector2f position, char c);
	bool beenEaten() const { return m_beenEaten; }
	void gotEaten() { m_beenEaten = true; } 
	virtual unsigned int pointsReward() const = 0;
	virtual int move(const sf::Vector2f &) = delete;

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
//----------------------------------------------------
class Wall : public StaticObjects
{
public:
	Wall(float edgeSize, sf::Vector2f position, char c, bool height = false, bool width = false);
	unsigned int pointsReward() const override { return 0; }

};
//----------------------------------------------------
class Door : public StaticObjects
{
public:
	using StaticObjects::StaticObjects;
	unsigned int pointsReward() const override { return 0; }
};
//----------------------------------------------------
class Key : public StaticObjects
{
public:
	using StaticObjects::StaticObjects;
	unsigned int pointsReward() const override { return KEYSPOINTS; }
};

//-------------	---------------------------------------
class Cookie : public StaticObjects
{
public:
	Cookie(float edgeSize, sf::Vector2f position, char c);
	unsigned int pointsReward() const override { return COOKIEPOINTS; }
};

//----------------------------------------------------
//sub hierarchy of all present types
//right now its prety useless but it creates a convinient platform for future changes
class Present : public StaticObjects
{
public:
	using StaticObjects::StaticObjects;
};
//----------------------------------------------------
class SuperPresent : public Present
{
public:
	using Present::Present;
	virtual unsigned int pointsReward() const override { return SUPER_POINTS; }
};
class FreezePresent : public Present
{
public:
	using Present::Present;
	virtual unsigned int pointsReward() const override { return FREEZE_POINTS; }
};
class TimePresent : public Present
{
public:
	using Present::Present;
	virtual unsigned int pointsReward() const override { return TIME_POINTS; }
};
class LivesPresent : public Present
{
public:
	using Present::Present;
	virtual unsigned int pointsReward() const override { return LIVES_POINTS; }
};

