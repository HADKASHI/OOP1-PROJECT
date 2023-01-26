#pragma once
#include <SFML/Graphics.hpp> 

const unsigned int COOKIEPOINTS = 2;

const unsigned int LIVES = 3;

const unsigned int KEYSPOINTS = 7;

const unsigned int GHOSTPOINTS = 100;

const float GHOST_SPEED = 50.f;

const unsigned int FREEZETIMER = 8;

const unsigned int SUPERTIMER = 8;

const unsigned int TIMEBONUS = 8;

const float PACMANSPEED = 75.f;

const sf::Vector2f UP = { 0 , -1 };

const sf::Vector2f DOWN = { 0 , 1 };

const sf::Vector2f RIGHT = { 1 , 0 };

const sf::Vector2f LEFT = { -1 , 0 };

enum Sounds { TIMER, FINISH_LEVEL, GAME_OVER, PACMAN_DEAD, GHOST_EATEN, PRESENT, EAT_COOKIE, DOOR_OPEN };
