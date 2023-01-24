#include "Render.h"
#include "HUD.h"
#include "Board.h"
#include <SFML/Graphics.hpp>

Render::Render(const sf::Vector2f& size):
    m_size(size), m_window( sf::VideoMode(size.x, size.y), "Pacman" )
{
    this->setIcon();
}


//game main loop
void Render::gameLoop(Board &board, HUD &hud, bool &finished)
{
    m_window.setFramerateLimit(30);
    auto pacman = Pacman(board.getTileSize(), board.getPacmanPosition(), 'a');
    auto gameClock = sf::Clock();
    while (m_window.isOpen())
    {

        m_window.clear(sf::Color(144, 158, 181));

        board.drawBoard(m_window);

        hud.drawHUD(m_window);

        m_window.draw(pacman);   

        m_window.display();

        for (auto event = sf::Event{}; m_window.pollEvent(event); )
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                m_window.close();
                finished = true;
                break;
            }
            case sf::Event::KeyPressed:
            {
                pacman.keyDirection(event.key.code);
                break;
            }
            case sf::Event::KeyReleased:
                pacman.notMoving(event.key.code);
                break;
            }
        }
        auto delta = gameClock.restart();
        pacman.update(delta);
        board.update(pacman, delta);
     }
}





void Render::setIcon()
{
    auto image = sf::Image();
    if (!image.loadFromFile("redGhost.png"))
        exit(EXIT_FAILURE);

    m_window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}