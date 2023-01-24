#include "Render.h"
#include "HUD.h"
#include "Board.h"
#include "Graphics.h"
#include <SFML/Graphics.hpp>

Render::Render(const sf::Vector2f& size):
    m_size(size), m_window( sf::VideoMode(size.x, size.y), "Pacman" )
{
    this->setIcon();
}


//game main loop
void Render::gameLoop(HUD &hud, bool &finished)
{
    unsigned int score = 0;
    std::fstream file("Board.txt", std::fstream::in);
    unsigned int timeAsSecond, level = 1;

    int cookies = 2;

    while (m_window.isOpen() &&  !file.eof())
    {
        timeAsSecond = initTimer(file);
        auto board = Board(file, getBoardSize(), getBoardPosition());
        auto pacman = Pacman(board.getTileSize(), board.getPacmanPosition(), 'a', score);

        startLevel(pacman, board, hud, level, timeAsSecond);

        auto gameClock = sf::Clock();
        sf::Clock timer;

        while (pacman.getLives() > 0 &&
               !finished &&
               timeAsSecond - timer.getElapsedTime().asSeconds() > 0 &&
               /*!board.noCookiesLeft()*/ cookies!= 0)
        {

            m_window.clear(sf::Color(250, 211, 231));
            board.drawBoard(m_window);
            hud.drawHUD(m_window, pacman.getLives(), 
                        pacman.getScore(), level, 
                        timeAsSecond - timer.getElapsedTime().asSeconds());
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
                    pacman.setDirection(event.key.code);
                    break;
                }
                case sf::Event::KeyReleased:
                    pacman.notMoving(event.key.code);
                    cookies--;
                    break;
                }
            }
            auto delta = gameClock.restart();
            pacman.update(delta);
        }

        int endTime = timeAsSecond - timer.getElapsedTime().asSeconds();

        if (cookies == 0 /*board.noCookiesLeft()*/ && !file.eof())
        {
            TransitionSlide("Yay! you moved on to the next level",
                60, sf::Color::Black, sf::Color::White);
            score = pacman.getScore();
            score += 50 + 2 * board.getGhostsNumber();
            level++;
        }

        else if (pacman.getLives() == 0 ||
            endTime <= 0)
        {
            TransitionSlide("Game Over", 100, sf::Color::Red, sf::Color::Black);
            break;
        }

        else if (file.eof())
            TransitionSlide("You won! see you next time",
                60, sf::Color::Black, sf::Color::White);

        else if (finished)
            exit(EXIT_SUCCESS);
    }
}


unsigned int Render::initTimer(std::fstream& file)
{
    int timer , temp;
    file >> timer;
    timer *= 60;
    file.ignore();
    file >> temp;
    timer += temp;
    file.ignore();

    return timer;
}


void Render::setIcon()
{
    auto image = sf::Image();
    if (!image.loadFromFile("redGhost.png"))
        exit(EXIT_FAILURE);

    m_window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}



void Render::TransitionSlide(const char* str, int fontSize, sf::Color textColor, sf::Color outLineColor)
{
    sf::RectangleShape backGround(sf::Vector2f(m_window.getSize()));
    backGround.setFillColor(sf::Color(0, 0, 0, 150));

    sf::Text text(str, Graphics::instance().getFont(), fontSize);
    text.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f - 30);
    text.setOutlineThickness(4);
    text.setOutlineColor(outLineColor);
    text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
    text.setFillColor(textColor);

    m_window.draw(backGround);
    m_window.draw(text);
    m_window.display();
    sf::sleep(sf::seconds(3));
}


void Render::startLevel(Pacman& pacman, Board& board, HUD& hud, int level, int timeAsSec)
{
    sf::RectangleShape startLevelBG(sf::Vector2f(m_window.getSize()));
    startLevelBG.setFillColor(sf::Color(0, 0, 0, 150));

    sf::Text startLevelText(" ", Graphics::instance().getFont(), 150);
    startLevelText.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f - 30);
    startLevelText.setFillColor(sf::Color::Black);
    startLevelText.setOutlineThickness(7);
    startLevelText.setOutlineColor(sf::Color::White);

    for (int sec = 3; sec > 0; sec--)
    {
        startLevelText.setString(std::to_string(sec));
        startLevelText.setOrigin(startLevelText.getLocalBounds().width / 2.f,
            startLevelText.getLocalBounds().height / 2.f);
        m_window.clear(sf::Color(250, 211, 231));
        board.drawBoard(m_window);
        hud.drawHUD(m_window, pacman.getLives(),
            pacman.getScore(), level, timeAsSec);
        m_window.draw(pacman);
        m_window.draw(startLevelBG);
        m_window.draw(startLevelText);
        m_window.display();
        sf::sleep(sf::seconds(1));
    }
    
}


