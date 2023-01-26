#pragma once
#include "SFML/Graphics.hpp"
class Ghost;


// a singleton class that handles all whats comes with pacman different states
// (i.e superPacman, freezing pacman and so on...)
// this class handles mainly ghost movement, ghost textures.
// in addition it tells to whomever interested what exactly is pacman state
class PacmanState
{
public:
	PacmanState(const PacmanState&) = delete;
	static PacmanState& instance();
	void operator = (const PacmanState&) = delete;
	void move(Ghost& ghost, sf::Time delta, sf::Vector2f targetPosition);
	void superState();
	void setTexture(Ghost& ghost);
	bool isSuper() const { return m_superPacman; }
	bool isFreeze() const { return m_freeze; }
	void handleCollision(Ghost& ghost) const;
	void freezeGhosts() { m_freeze = true; m_freezeTimer.restart(); }

private:
	PacmanState() : m_freeze(false), m_superPacman(false) {}
	void alternateMove(Ghost& ghost, sf::Time delta);
	void randMove(Ghost& ghost, sf::Time delta);
	void goHome(Ghost& ghost, sf::Time delta) const;
	bool m_superPacman;
	sf::Clock m_superTimer;
	bool m_freeze;
	sf::Clock m_freezeTimer;
};