#pragma once
#include "MainMenu.h"
#include "Board.h"
#include "HUD.h"
#include "Resources.h"
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
#include <fstream>


MainMenu::MainMenu()
    :m_logo(sf::RectangleShape({ 400, 150 })),
    m_buttons({ sf::Text("PLAY GAME", Resources::instance().getFont()),
                sf::Text("HELP", Resources::instance().getFont()),
                sf::Text("EXIT", Resources::instance().getFont()) })
{
    m_logoTexture.loadFromFile("logo1.png");
    m_logo.setTexture(&m_logoTexture);
    m_logo.setPosition(MENU_LOGO_POSITION);
    m_logo.setOrigin(m_logo.getSize() / 2.f);

    float y = 320;
    for (int i = 0; i < m_buttons.size(); i++)
    {
        m_buttons[i].setPosition({ 445, y });
        y += 100;
        m_buttons[i].setFillColor(sf::Color::Yellow);
        m_buttons[i].setOutlineThickness(0.5);
        m_buttons[i].setOutlineColor(sf::Color::Black);
    }
}



void MainMenu::menuLoop(Render* render)
{
    auto window = render->getP2Window();
    Resources::instance().playBackGround();

    sf::Clock spawnTimer;
    sf::Clock moveTimer;
    while (window->isOpen())
    {

        window->clear(sf::Color::Black);
        auto timer = spawnTimer.getElapsedTime();
        if (timer.asSeconds() > SPAWN_TIME) spawnTimer.restart();

        auto delta = moveTimer.restart();
        drawBackGroundCharacters(window, delta, timer);
        window->draw(m_logo);

        auto cursorLocation = sf::Vector2f({ sf::Mouse::getPosition(*window).x * 1.f,
                                             sf::Mouse::getPosition(*window).y * 1.f });

        checkMouseOnButton(window, cursorLocation);

        window->display();

        for (auto event = sf::Event{}; window->pollEvent(event); )
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                window->close();
                break;
            }

            case sf::Event::MouseButtonReleased:
            {
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Left:
                {
                    if (m_buttons[0].getGlobalBounds().contains(cursorLocation))
                    {
                        handleClickOnPlayGame(render);
                        Resources::instance().playBackGround();
                    }

                    else if (m_buttons[1].getGlobalBounds().contains(cursorLocation))
                        handleClickOnHelp(window);

                    else if (m_buttons[2].getGlobalBounds().contains(cursorLocation))
                        window->close();

                    break;
                }
                }
            }
            }
        }
    }
}

void MainMenu::drawBackGroundCharacters(sf::RenderWindow* window, sf::Time delta, sf::Time timer)
{
    if (timer.asSeconds() >= SPAWN_TIME)
        addRandomCharacter();

    for (size_t i = 0; i < m_backGroundCharacters.size(); i++)
    {
        if (m_backGroundCharacters[i]->getPosition().x < - BACKGROUND_CHAR_SIZE*2 || m_backGroundCharacters[i]->getPosition().x > WINDOW_SIZE.x + BACKGROUND_CHAR_SIZE*2)
            m_backGroundCharacters.erase(m_backGroundCharacters.begin() + i);

        else
        {
            m_backGroundCharacters[i]->
                move(m_backGroundCharacters[i]->getDirection() * delta.asSeconds() * float(rand() % 200 + 30));
            window->draw(*m_backGroundCharacters[i]);
        }
    }
}

void MainMenu::addRandomCharacter()
{
    auto num = rand() % 4;
    float xAxis;
    if (rand() % 2 == 0)
        xAxis = -BACKGROUND_CHAR_SIZE;
    else
        xAxis = WINDOW_SIZE.x + BACKGROUND_CHAR_SIZE;

    auto yAxis = rand() % int(WINDOW_SIZE.y);

    sf::Vector2f direction;

    if (xAxis < 0)
        direction = RIGHT;
    else
        direction = LEFT;

    switch (num)
    {
    case 0:
    {
        m_backGroundCharacters.push_back
        (std::make_unique<GreenGhost>(BACKGROUND_CHAR_SIZE + rand()%30 , sf::Vector2f{1.f * xAxis, 1.f * yAxis}, 'g'));

        m_backGroundCharacters[m_backGroundCharacters.size() - 1]->setDirection(direction);
        break;
    }
    case 1:
    {
        m_backGroundCharacters.push_back
        (std::make_unique<RedGhost>(BACKGROUND_CHAR_SIZE + rand() % 30, sf::Vector2f{ 1.f * xAxis, 1.f * yAxis }, 'r'));

        m_backGroundCharacters[m_backGroundCharacters.size() -1]->setDirection(direction);
        break;
    }
    case 2:
    {
        m_backGroundCharacters.push_back
        (std::make_unique<OrangeGhost>(BACKGROUND_CHAR_SIZE + rand() % 30, sf::Vector2f{ 1.f * xAxis, 1.f * yAxis }, 'o'));

        m_backGroundCharacters[m_backGroundCharacters.size() -1]->setDirection(direction);
        break;
    }
    case 3:
    {
        m_backGroundCharacters.push_back
        (std::make_unique<PinkGhost>(BACKGROUND_CHAR_SIZE + rand() % 30, sf::Vector2f{ 1.f * xAxis, 1.f * yAxis }, 'p'));

        m_backGroundCharacters[m_backGroundCharacters.size() -1]->setDirection(direction);
        break;
    }
    }
}


void MainMenu::checkMouseOnButton(sf::RenderWindow* window, sf::Vector2f cursorLocation)
{
    for (int i = 0; i < m_buttons.size(); i++)
    {
        m_buttons[i].setScale(1.5, 1.5);

        if (m_buttons[i].getGlobalBounds().contains(cursorLocation))
            m_buttons[i].setScale(2.0, 2.0);


        m_buttons[i].setOrigin(m_buttons[i].getLocalBounds().width / 2.f,
            m_buttons[i].getLocalBounds().height / 2.f);
        window->draw(m_buttons[i]);
    }
}



void MainMenu::handleClickOnPlayGame(Render* render)
{
    auto hud = HUD(HUD_POSITION);

    bool finished = false;

    render->gameLoop(hud, finished);
}


void MainMenu::handleClickOnHelp(sf::RenderWindow* window)
{
    sf::RectangleShape help(sf::Vector2f(window->getSize()));
    sf::Texture texture;
    texture.loadFromFile("help.png");
    help.setTexture(&texture);
    help.setPosition(window->getSize().x / 2.f, window->getSize().y / 2.f);
    help.setOrigin(help.getSize() / 2.f);

    sf::RectangleShape back({ 70, 50 });
    back.setPosition({ 790, 580 });

    while (window->isOpen())
    {
        window->clear(sf::Color::Black);
        window->draw(help);
        window->display();

        if (auto event = sf::Event{}; window->waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                window->close();
                break;
            }

            case sf::Event::MouseButtonReleased:
            {
                auto location = window->mapPixelToCoords({ event.mouseButton.x,
                                                           event.mouseButton.y });
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Left:
                {
                    if (back.getGlobalBounds().contains(location))
                        return;
                    break;
                }
                }
            }
            }
        }
    }
}