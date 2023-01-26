#include "Render.h"
#include "HUD.h"
#include "Board.h"
#include "Resources.h"
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>

Render::Render(const sf::Vector2f& size):
    m_size(size), m_window( sf::VideoMode(size.x, size.y),"Pacman")
{
    this->setIcon();
}


//game main loop
void Render::gameLoop(HUD& hud, bool& finished)
{
    unsigned int lives = LIVES, score = 0, endLevelScore = 0,
                 startTime, timeAsSecond, level = 1;
    std::fstream file("Board.txt", std::fstream::in);

    while (m_window.isOpen() && !file.eof())
    {
        startTime = timeAsSecond = initTimer(file);
        auto board = Board(file, getBoardSize(), getBoardPosition());
        auto pacman = Pacman(board.getTileSize(), board.getPacmanPosition(), 'a', score);
        pacman.setLives(lives);

        startLevelSlide(pacman, board, hud, level, startTime);

        auto gameClock = sf::Clock();
        sf::Clock timer;
        Resources::instance().playBackGround();

        while (pacman.getLives() > 0 &&
            !finished &&
            !board.noCookiesLeft())
        {
            if (timeAsSecond - timer.getElapsedTime().asSeconds() <= 0)
            {
                timeAsSecond = startTime;
                handleTimeUp(pacman, board, timer, hud, level, startTime, endLevelScore);
            }

            eventsLoop(pacman, finished);
  
            auto delta = gameClock.restart();
            pacman.update(delta);
            board.update(pacman, delta);
            drawWindow(board, hud, pacman, level, timeAsSecond - timer.getElapsedTime().asSeconds());
            Resources::instance().volumeBackGround(50);
            timeAsSecond += pacman.getBonusTime();
        }

        if (board.noCookiesLeft() && !file.eof())
        {
            lives = pacman.getLives();
            endLevelScore = pacman.getScore();
            drawWindow(board, hud, pacman, level, timeAsSecond - timer.getElapsedTime().asSeconds());
            Resources::instance().playMusic(FINISH_LEVEL, 50);
            TransitionSlide("Yay! next level",
                60, 2, sf::Color::Black, sf::Color::White);
            score = pacman.getScore();
            score += 50 + 2 * board.getGhostsNumber();
            endLevelScore = score;
            level++;
        }

        else if (pacman.getLives() == 0)
        {         
            Resources::instance().playMusic(GAME_OVER);
            TransitionSlide("Game Over", 100, 2, sf::Color::Red, sf::Color::Black);
            break;
        }

        else if (file.eof())
        {
            drawWindow(board, hud, pacman, level, timeAsSecond - timer.getElapsedTime().asSeconds());
            Resources::instance().playMusic(FINISH_LEVEL, 50);
            TransitionSlide("You won! see you next time",
                60, 4, sf::Color::Black, sf::Color::White);
        }

        else if (finished)
            exit(EXIT_SUCCESS);
    }
}



unsigned int Render::initTimer(std::fstream& file)
{
    int timer, temp;
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

void Render::drawWindow(Board& board, HUD& hud, Pacman& pacman, int level, int time)
{
    m_window.clear(sf::Color(250, 211, 231));
    board.drawBoard(m_window);
    hud.drawHUD(m_window, pacman.getLives(),
        pacman.getScore(), level,
        time);
    m_window.draw(pacman);
    m_window.display();
}

void Render::handleTimeUp(Pacman &pacman, Board &board,sf::Clock &timer, 
               HUD &hud, int level, int startTime, int endLevelScore)
{
    Resources::instance().playMusic(PACMAN_DEAD);
    TransitionSlide("Time up! try again", 80, 2, sf::Color::Red, sf::Color::Black);
    pacman.setScore(endLevelScore);
    board.resetLevel();
    pacman.setPosition(board.getPacmanPosition());
    timer.restart();
    pacman.setLives(pacman.getLives() - 1);
    if (pacman.getLives() == 0)
        return;
    startLevelSlide(pacman, board, hud, level, startTime);
    Resources::instance().playBackGround();
}

void Render::eventsLoop(Pacman& pacman, bool& finished)
{
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
}

void Render::TransitionSlide(const char* str, int fontSize, double sleepTime,
    sf::Color textColor, sf::Color outLineColor)
{
    sf::RectangleShape backGround(sf::Vector2f(m_window.getSize()));
    backGround.setFillColor(sf::Color(0, 0, 0, 150));

    sf::Text text(str, Resources::instance().getFont(), fontSize);
    text.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f - 30);
    text.setOutlineThickness(4);
    text.setOutlineColor(outLineColor);
    text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
    text.setFillColor(textColor);

    m_window.draw(backGround);
    m_window.draw(text);
    m_window.display();
    sf::sleep(sf::seconds(sleepTime));
}


void Render::startLevelSlide(Pacman& pacman, Board& board, HUD& hud, int level, int timeAsSec)
{
    sf::RectangleShape startLevelBG(sf::Vector2f(m_window.getSize()));
    startLevelBG.setFillColor(sf::Color(0, 0, 0, 150));

    sf::Text startLevelText(" ", Resources::instance().getFont(), 150);
    startLevelText.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f - 30);
    startLevelText.setFillColor(sf::Color::Black);
    startLevelText.setOutlineThickness(7);
    startLevelText.setOutlineColor(sf::Color::White);

    for (int sec = 3; sec > 0; sec--)
    {
        Resources::instance().playMusic(TIMER, 60);
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

