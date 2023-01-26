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

const sf::Vector2f WINDOW_SIZE = { 890.f, 680.f };

const float SPAWN_TIME = 0.5f;

const sf::Vector2f BOARD_SIZE = sf::Vector2f{ 15 * 40, 15 * 40 };

const sf::Vector2f BOARD_POSITION = sf::Vector2f{ 40.f + 20 * 15, 40.f + 20 * 15 };

const sf::Color BOARD_OUTLINE_COLOR = sf::Color(19, 43, 209);

const sf::Vector2u HUD_SIZE = sf::Vector2u{ 180, 600 };

const sf::Vector2f HUD_LIVES_ICON_SIZE = sf::Vector2f({ 25 , 25 });

const int HUD_COLOR = 120;

const int HUD_LIVES_HEIGHT = 110;

const int HUD_SCORE_HEIGHT = 376;

const int HUD_TIME_HEIGHT = 509;

//sf::Vector2f MENU_LOGO_SIZE = sf::Vector2f{ 400, 150 };

const sf::Vector2f MENU_LOGO_POSITION = sf::Vector2f{ 445, 170 };

const int BACKGROUND_CHAR_SIZE = 60;

const int TILE_SIZE = 40;

const sf::Vector2f HUD_POSITION = sf::Vector2f{ TILE_SIZE + TILE_SIZE * 15 + TILE_SIZE + 60, TILE_SIZE + 300 };

const float EYES_SPEED = 90.f;

const unsigned int MOMENTUM = 500;

const sf::Color WINDOW_COLOR = sf::Color(250, 211, 231);
