#pragma once

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include "GameObject.h"
#include "Resources.h"


namespace { // unnamed namespace — the standard way to make function "static"
    // primary collision-processing functions
    float getOverLap(sf::Vector2f direction, sf::FloatRect rect1, sf::FloatRect rect2);
    sf::Vector2f overLapDirection(float overLap, sf::FloatRect rect1, sf::FloatRect rect2);

    void pacmanWithWall(GameObject& pacman,
        GameObject& wall)
    {
        Pacman& c_pacman = dynamic_cast<Pacman&>(pacman);
        Wall& c_wall = dynamic_cast<Wall&>(wall);

        auto pacmanBounds = c_pacman.getGlobalBounds();
        auto wallBounds = c_wall.getGlobalBounds();

        auto overLap = getOverLap(c_pacman.getDirection(), pacmanBounds, wallBounds);

        //handles the 'narrow aisles' cases 
        if (overLap < 7.f && overLap > 0.f)
        {
            sf::Vector2f direction = overLapDirection(overLap, pacmanBounds, wallBounds);

            //'fixes' pacman to eneter to the narrow aisle
            while (c_pacman.getGlobalBounds().intersects(c_wall.getGlobalBounds()))
                c_pacman.move(direction);
        }
        else
        {
            auto reverseDirection = c_pacman.getDirection() * -1.f;

            //moves back till gets out of wall bounds
            while (c_pacman.getGlobalBounds().intersects(c_wall.getGlobalBounds()))
                c_pacman.move(reverseDirection * 0.1f);
        }
    }

    float getOverLap(sf::Vector2f direction, sf::FloatRect rect1, sf::FloatRect rect2)
    {
        auto leftCorner = abs(rect1.left + rect1.width - rect2.left);
        auto rightCorner = abs(rect1.left - (rect2.left + rect2.width));
        if (direction == RIGHT || direction == LEFT)
            return std::min(abs(rect1.top + rect1.height - rect2.top), abs(rect1.top - (rect2.top + rect2.height)));

        else if (direction == UP || direction == DOWN)
            return std::min(rightCorner, leftCorner);
    }

    sf::Vector2f overLapDirection(float overLap, sf::FloatRect rect1, sf::FloatRect rect2)
    {
        if (overLap == abs(rect1.left + rect1.width - rect2.left))
            return LEFT;
        else if (overLap == abs(rect1.left - (rect2.left + rect2.width)))
            return RIGHT;
        else if (overLap == abs(rect1.top - (rect2.top + rect2.height)))
            return DOWN;
        else if (overLap == abs(rect1.top + rect1.height - rect2.top))
            return UP;
    }

    void pacmanWithBoard(GameObject& pacman,
        const Board& board)
    {
        Pacman& c_pacman = dynamic_cast<Pacman&>(pacman);

        auto reverseDirection = c_pacman.getDirection() * -1.f;

        //moves back till gets out of wall bounds
        while (!board.inBounds(c_pacman.getGlobalBounds()))
            c_pacman.move(reverseDirection * 0.1f);
    }

    void ghostWithBoard(Ghost& ghost,
        const Board& board)
    {
        ghost.gotStuck();

        auto reverseDirection = ghost.getDirection() * -1.f;

        //moves back till gets out of wall bounds
        while (!board.inBounds(ghost.getGlobalBounds()))
            ghost.move(reverseDirection * 0.1f);
    }

    void pacmanWithDoor(GameObject& pacman,
        GameObject& door)
    {
        Door& c_door = dynamic_cast<Door&>(door);
        if (PacmanState::instance().isSuper())
        {
            Resources::instance().playMusic(DOOR_OPEN);
            c_door.isEaten();
        }
        else
        {
            auto wall = Wall(c_door.getSize().x, c_door.getPosition(), '#');
            pacmanWithWall(pacman, wall);
        }
    }

    void pacmanWithCookie(GameObject& pacman,
        GameObject& cookie)
    {
        Resources::instance().playMusic(EAT_COOKIE);
        Pacman& c_pacman = dynamic_cast<Pacman&>(pacman);
        Cookie& c_cookie = dynamic_cast<Cookie&>(cookie);
        c_pacman.addPoints(c_cookie.pointsReward());
        c_cookie.isEaten();
    }

    void pacmanWithSuperPresent(GameObject& pacman,
        GameObject& present)
    {
        Resources::instance().playMusic(PRESENT);
        Pacman& c_pacman = dynamic_cast<Pacman&>(pacman);
        SuperPresent& c_present = dynamic_cast<SuperPresent&>(present);
        c_pacman.addPoints(c_present.pointsReward());
        c_present.isEaten();
        PacmanState::instance().superState();
    }

    void pacmanWithTimePresent(GameObject& pacman,
        GameObject& present)
    {
        Resources::instance().playMusic(PRESENT);
        Pacman& c_pacman = dynamic_cast<Pacman&>(pacman);
        TimePresent& c_present = dynamic_cast<TimePresent&>(present);
        c_pacman.addPoints(c_present.pointsReward());
        c_pacman.addTime();
        c_present.isEaten();
    }

    void pacmanWithLivesPresent(GameObject& pacman,
        GameObject& present)
    {
        Resources::instance().playMusic(PRESENT);
        Pacman& c_pacman = dynamic_cast<Pacman&>(pacman);
        LivesPresent& c_present = dynamic_cast<LivesPresent&>(present);
        c_pacman.addPoints(c_present.pointsReward());
        c_present.isEaten();
        c_pacman.addLives();
    }

    void pacmanWithFreezePresent(GameObject& pacman,
        GameObject& present)
    {
        Resources::instance().playMusic(PRESENT);
        Pacman& c_pacman = dynamic_cast<Pacman&>(pacman);
        FreezePresent& c_present = dynamic_cast<FreezePresent&>(present);
        c_pacman.addPoints(c_present.pointsReward());
        c_present.isEaten();
        PacmanState::instance().freezeGhosts();
    }

    void pacmanWithKey(GameObject& pacman,
        GameObject& key)
    {
        Resources::instance().playMusic(DOOR_OPEN);
        Pacman& c_pacman = dynamic_cast<Pacman&>(pacman);
        Key& c_key = dynamic_cast<Key&>(key);
        c_pacman.addPoints(c_key.pointsReward());
        c_key.isEaten();
    }

    void pacmanWithGhost(GameObject& pacman,
        GameObject& ghost)
    {
        if (PacmanState::instance().isSuper())
        {
            Resources::instance().playMusic(GHOST_EATEN);
            PacmanState::instance().handleCollision(dynamic_cast<Ghost&>(ghost));
            Pacman& c_pacman = dynamic_cast<Pacman&>(pacman);
            c_pacman.addPoints(GHOSTPOINTS);
        }

        else if (PacmanState::instance().isFreeze())
            return;

        else
        {
            Resources::instance().playMusic(PACMAN_DEAD, 50);
            Pacman& c_pacman = dynamic_cast<Pacman&>(pacman);
            c_pacman.gotEaten();
        }
    }

    void pacmanWithRedGhost(GameObject& pacman,
        GameObject& ghost)
    {
        RedGhost& c_redGhost = dynamic_cast<RedGhost&>(ghost);
        if (c_redGhost.isDead())
            return;
        else
            pacmanWithGhost(pacman, ghost);
    }

    
    void pacmanWithPinkGhost(GameObject& pacman,
        GameObject& ghost)
    {
        PinkGhost& c_pinkGhost = dynamic_cast<PinkGhost&>(ghost);
        if (c_pinkGhost.isDead())
            return;

        pacmanWithGhost(pacman, ghost);
    }

    void pacmanWithGreenGhost(GameObject& pacman,
        GameObject& ghost)
    {
        GreenGhost& c_greenGhost = dynamic_cast<GreenGhost&>(ghost);
        if (c_greenGhost.isDead())
            return;

        pacmanWithGhost(pacman, ghost);
    }

    void pacmanWithOrangeGhost(GameObject& pacman,
        GameObject& ghost)
    {
        OrangeGhost& c_orangeGhost = dynamic_cast<OrangeGhost&>(ghost);
        if (c_orangeGhost.isDead())
            return;

        pacmanWithGhost(pacman, ghost);
    }

    void redGhostWithPacman(GameObject& ghost,
        GameObject& pacman)
    {
        pacmanWithRedGhost(pacman, ghost);
    }

    void pinkGhostWithPacman(GameObject& ghost,
        GameObject& pacman)
    {
        pacmanWithPinkGhost(pacman, ghost);
    }

    void orangeGhostWithPacman(GameObject& ghost,
        GameObject& pacman)
    {
        pacmanWithOrangeGhost(pacman, ghost);
    }

    void greenGhostWithPacman(GameObject& ghost,
        GameObject& pacman)
    {
        pacmanWithGreenGhost(pacman, ghost);
    }

    void redGhostWithWall(GameObject& redGhost,
        GameObject& wall)
    {
        RedGhost& c_redGhost = dynamic_cast<RedGhost&>(redGhost);
        Wall& c_wall = dynamic_cast<Wall&>(wall);

        if (c_redGhost.isDead())
            return;

        auto pacmanBounds = c_redGhost.getGlobalBounds();
        auto wallBounds = c_wall.getGlobalBounds();

        auto overLap = getOverLap(c_redGhost.getDirection(), pacmanBounds, wallBounds);

        //handles the 'narrow aisles' cases 
        if (overLap < 7.f && overLap > 0.f)
        {
            sf::Vector2f direction = overLapDirection(overLap, pacmanBounds, wallBounds);

            //'fixes' pacman to eneter to the narrow aisle
            while (c_redGhost.getGlobalBounds().intersects(c_wall.getGlobalBounds()))
                c_redGhost.move(direction);
        }
        else
        {
            c_redGhost.gotStuck();

            auto reverseDirection = c_redGhost.getDirection() * -1.f;

            //moves back till gets out of wall bounds
            while (c_redGhost.getGlobalBounds().intersects(c_wall.getGlobalBounds()))
                c_redGhost.move(reverseDirection * 0.1f);
        }
    }

    void pinkGhostWithWall(GameObject& pinkGhost,
        GameObject& wall)
    {
        PinkGhost& c_pinkGhost = dynamic_cast<PinkGhost&>(pinkGhost);
        if (c_pinkGhost.isDead())
            return;

        auto position = sf::Vector2f({ c_pinkGhost.getPosition().x - 0.5f * c_pinkGhost.getSize().x,
            c_pinkGhost.getPosition().y - 0.5f * c_pinkGhost.getSize().y });
        RedGhost redGhost(c_pinkGhost.getSize().x, position , 'r');
        redGhost.setDirection(c_pinkGhost.getDirection());
        redGhostWithWall(redGhost, wall);

        c_pinkGhost.setPosition(redGhost.getPosition());
        if (redGhost.isStuck())
            c_pinkGhost.gotStuck();
    }

    void greenGhostWithWall(GameObject& greenGhost,
        GameObject& wall)
    {
        GreenGhost& c_greenGhost = dynamic_cast<GreenGhost&>(greenGhost);
        if (c_greenGhost.isDead())
            return;

        auto position = sf::Vector2f({ c_greenGhost.getPosition().x - 0.5f * c_greenGhost.getSize().x,
            c_greenGhost.getPosition().y - 0.5f * c_greenGhost.getSize().y });
        RedGhost redGhost(c_greenGhost.getSize().x, position, 'r');
        redGhost.setDirection(c_greenGhost.getDirection());
        redGhostWithWall(redGhost, wall);

        c_greenGhost.setPosition(redGhost.getPosition());
        if (redGhost.isStuck())
            c_greenGhost.gotStuck();
    }

    void orangeGhostWithWall(GameObject& orangeGhost,
        GameObject& wall)
    {
        OrangeGhost& c_orangeGhost = dynamic_cast<OrangeGhost&>(orangeGhost);
        if (c_orangeGhost.isDead())
            return;

        auto position = sf::Vector2f({ c_orangeGhost.getPosition().x - 0.5f * c_orangeGhost.getSize().x,
            c_orangeGhost.getPosition().y - 0.5f * c_orangeGhost.getSize().y });
        RedGhost redGhost(c_orangeGhost.getSize().x, position, 'r');
        redGhost.setDirection(c_orangeGhost.getDirection());
        redGhostWithWall(redGhost, wall);

        c_orangeGhost.setPosition(redGhost.getPosition());
        if (redGhost.isStuck())
            c_orangeGhost.gotStuck();
    }

    void redGhostWithDoor(GameObject& redGhost,
        GameObject& door)
    {
        Door& c_door = dynamic_cast<Door&>(door);
        RedGhost& c_redGhost = dynamic_cast<RedGhost&>(redGhost);

        auto wall = Wall(c_door.getSize().x, c_door.getPosition(), '#');
        redGhostWithWall(c_redGhost, wall);
    }

    void pinkGhostWithDoor(GameObject& pinkGhost,
        GameObject& door)
    {
        Door& c_door = dynamic_cast<Door&>(door);
        PinkGhost& c_pinkGhost = dynamic_cast<PinkGhost&>(pinkGhost);
        if (c_pinkGhost.isDead())
            return;

        auto wall = Wall(c_door.getSize().x, c_door.getPosition(), '#');
        pinkGhostWithWall(c_pinkGhost, wall);
    }

    void greenGhostWithDoor(GameObject& greenGhost,
        GameObject& door)
    {
        Door& c_door = dynamic_cast<Door&>(door);
        GreenGhost& c_greenGhost = dynamic_cast<GreenGhost&>(greenGhost);
        if (c_greenGhost.isDead())
            return;

        auto wall = Wall(c_door.getSize().x, c_door.getPosition(), '#');
        greenGhostWithWall(c_greenGhost, wall);
    }

    void orangeGhostWithDoor(GameObject& orangeGhost,
        GameObject& door)
    {
        Door& c_door = dynamic_cast<Door&>(door);
        OrangeGhost& c_orangeGhost = dynamic_cast<OrangeGhost&>(orangeGhost);
        if (c_orangeGhost.isDead())
            return;

        auto wall = Wall(c_door.getSize().x, c_door.getPosition(), '#');
        orangeGhostWithWall(c_orangeGhost, wall);
    }

    using collisionFunc = void (*) (GameObject& object1, GameObject& object2);
    using CollisionMap = std::unordered_map<std::string, collisionFunc>;


    std::unique_ptr<CollisionMap> CreateMap() {
        std::unique_ptr<CollisionMap> cm = std::make_unique<CollisionMap>();

        (*cm)[std::string(typeid(Pacman).name()) + std::string(typeid(Wall).name())] = pacmanWithWall;
        (*cm)[std::string(typeid(Pacman).name()) + std::string(typeid(Door).name())] = pacmanWithDoor;
        (*cm)[std::string(typeid(Pacman).name()) + std::string(typeid(Key).name())] = pacmanWithKey;
        (*cm)[std::string(typeid(Pacman).name()) + std::string(typeid(SuperPresent).name())] = pacmanWithSuperPresent;
        (*cm)[std::string(typeid(Pacman).name()) + std::string(typeid(TimePresent).name())] = pacmanWithTimePresent;
        (*cm)[std::string(typeid(Pacman).name()) + std::string(typeid(LivesPresent).name())] = pacmanWithLivesPresent;
        (*cm)[std::string(typeid(Pacman).name()) + std::string(typeid(FreezePresent).name())] = pacmanWithFreezePresent;

        (*cm)[std::string(typeid(Pacman).name()) + std::string(typeid(Cookie).name())] = pacmanWithCookie;
        (*cm)[std::string(typeid(Pacman).name()) + std::string(typeid(RedGhost).name())] = pacmanWithRedGhost;
        (*cm)[std::string(typeid(Pacman).name()) + std::string(typeid(PinkGhost).name())] = pacmanWithPinkGhost;
        (*cm)[std::string(typeid(Pacman).name()) + std::string(typeid(OrangeGhost).name())] = pacmanWithOrangeGhost;
        (*cm)[std::string(typeid(Pacman).name()) + std::string(typeid(GreenGhost).name())] = pacmanWithGreenGhost;
        (*cm)[std::string(typeid(RedGhost).name()) + std::string(typeid(Pacman).name())] = redGhostWithPacman;
        (*cm)[std::string(typeid(PinkGhost).name()) + std::string(typeid(Pacman).name())] = pinkGhostWithPacman;
        (*cm)[std::string(typeid(GreenGhost).name()) + std::string(typeid(Pacman).name())] = greenGhostWithPacman;
        (*cm)[std::string(typeid(OrangeGhost).name()) + std::string(typeid(Pacman).name())] = orangeGhostWithPacman;
        (*cm)[std::string(typeid(RedGhost).name()) + std::string(typeid(Wall).name())] = redGhostWithWall;
        (*cm)[std::string(typeid(PinkGhost).name()) + std::string(typeid(Wall).name())] = pinkGhostWithWall;
        (*cm)[std::string(typeid(GreenGhost).name()) + std::string(typeid(Wall).name())] = greenGhostWithWall;
        (*cm)[std::string(typeid(OrangeGhost).name()) + std::string(typeid(Wall).name())] = orangeGhostWithWall;
        (*cm)[std::string(typeid(RedGhost).name()) + std::string(typeid(Door).name())] = redGhostWithDoor;
        (*cm)[std::string(typeid(PinkGhost).name()) + std::string(typeid(Door).name())] = pinkGhostWithDoor;
        (*cm)[std::string(typeid(GreenGhost).name()) + std::string(typeid(Door).name())] = greenGhostWithDoor;
        (*cm)[std::string(typeid(OrangeGhost).name()) + std::string(typeid(Door).name())] = orangeGhostWithDoor;

        return cm;
    }

    collisionFunc lookup(const std::string& object1, const std::string& object2)
    {
        static std::unique_ptr<CollisionMap> map = CreateMap();
        std::string name = object1 + object2;
        auto itr = map->find(object1 + object2);
        if (itr == map->end())
            return nullptr;

        return itr->second;
    }


    void processCollision(GameObject& object1,
        GameObject& object2)
    {
        collisionFunc p2f = lookup(typeid(object1).name(),
            typeid(object2).name());
        if (p2f)
            p2f(object1, object2);
    }
}