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
    m_logo.setPosition({ 445, 170 });
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

    while (window->isOpen())
    {

        window->clear(sf::Color::Black);
        window->draw(m_logo);

        auto cursorLocation = sf::Vector2f({ sf::Mouse::getPosition(*window).x * 1.f,
                                             sf::Mouse::getPosition(*window).y * 1.f });

        checkMouseOnButton(window, cursorLocation);

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
    auto hud = HUD({ 40 + 40 * 15 + 40 + 60, 40 + 300 });

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