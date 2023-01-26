=====================================================================

OOP, project

			SUPER-PACMAN
                  ======================

by: Hadar Kashi & Ziv Molodic
I.D: Hadar  - 315216515
     Ziv    - 206998668

=====================================================================

                       Description
                     =================				 

This program is based on the classic 'PACMAN' game that we all know and love

This game is a three level based game and three lives as well

Ganmeplay:

The goal of the game is to finish all levels using 3 lives.
The end of a level is when Pacman managed to eat all the cookies on the board within the allotted time.
When Pacman encounters a ghost, he will lose a life, so you should be very careful.
If the allotted time runs out, the game is over.
Pacman movement will be done by the keyboard arrows.
Pacman cannot pass through walls and doors.
In order to open the doors, Pacman must collect keys.

During the game Pacman will be able to take gifts that will help him succeed in the mission:
-  A gift that will turn Pacman into Super Pacman for a certain time, so, he can encounter ghosts without losing a life, 
   and passing  through doors without a key.
-  A gift that will add time to the passage of the level.
-  A gift that will temporarily freeze the ghosts.
-  A gift that will add one life.


=====================================================================

                         Included files
                        =================	

There are 11 object files built by us:

1) Controller.cpp
This class provides the platform the action gameplay needs

2)  Board.cpp
This class holds all game objects that apears on the game board (excepts for pacman)
e.g cookies, ghosts, the current map etc

3) Collisions.h
This namespace handles all collisions creating a double v-table

4) GameObject.cpp
A class hierarchy that holds all game objects
it splits into two main branches: Statics and Movings
under Statics you'll find cookies, doors and stuff like those
under Movings you'll find ghost and pacman

ALL NONE LEAVES ARE ABSTRACT!

5) Ghost.cpp
This class hierarchy of enemys
each ghost chases in a different strategy and therefore they divided into different classes
the ghost movement is handled by PacmanState class what leads to
the ghost base class has a very wide and rich interface

6) HUD.cpp
This class holds and handles all the HUD (Head-Up Display)
i.e time left, score and lives etc

7) MainMenu.cpp
This class handles the main menu of the game
handles clicks and their effects

8) Pacman.cpp
Used as the player class. holds the score ,lives and handles movement

9) PacmanState.cpp
A singleton class that handles all whats comes with pacman different states
(i.e superPacman, freezing pacman and so on...)
this class handles mainly ghost movement, ghost textures.
in addition it tells to whomever interested what exactly is pacman state

10) Render.cpp
This class handles all the window presentation and rendering
e.g the game looop itsel

11) Resources.cpp
This is a static singleton class. it provides and handles
all game graphics and sound

Every '.cpp' file has a header file which includes the
definition of the class.

21 files in total.

=====================================================================

                           Data Structure
                           ==============

Hash table- in Resources get char and sends texture.
	    in Collisions get classes name and sends them to the function.

=====================================================================

                           Algorithms worth mention:
                         =============================

Ghost movement algorithm:
=========================
The algorithm is includes three main terms: momentum, alternating and direction. which
obbey two simple rules:
1) Always try to get around obstacle
2) Dont get back to your previously tile

Direction:
The ghost computes wich direction will get him the closest to pacman using distance formula
and 'trying' to move there. if the desired move is been blocked its alternating its movement (which will be explained).

If Super Pac-Man mode has been activated the ghost computes farest direction and do the same thing.

Alternating:
If the ghost got stuck while moving horizontal it'll move vertical until it'll be ablle to move horizontal again
If the ghost got stuck while moving vertical it'll move horizontal until it'll be ablle to move vertical again
If got stuck while 'Alternating' it picks random direction (and so avoiding getting stuck in corners)

Momentum:
Ghost can choose direction only if it gained enough momentum, what creates a more 'Pacman'-ish movment

Door opened algorithm:
=====================
The algorithm picks a random door by generating a random number and modulating (%) it by the amount of doors


=====================================================================

			       Design
                           ===============

1) Controller.cpp
This class provides the platform the action gameplay needs

2)  Board.cpp
This class holds all game objects that apears on the game board (excepts for pacman)
e.g cookies, ghosts, the current map etc

3) Collisions.h
This namespace handles all collisions creating a double v-table

4) GameObject.cpp
A class hierarchy that holds all game objects
it splits into two main branches: Statics and Movings
under Statics you'll find cookies, doors and stuff like those
under Movings you'll find ghost and pacman

ALL NONE LEAVES ARE ABSTRACT!

5) Ghost.cpp
This class hierarchy of enemys
each ghost chases in a different strategy and therefore they divided into different classes
the ghost movement is handled by PacmanState class what leads to
the ghost base class has a very wide and rich interface

6) HUD.cpp
This class holds and handles all the HUD (Head-Up Display)
i.e time left, score and lives etc

7) MainMenu.cpp
This class handles the main menu of the game
handles clicks and their effects

8) Pacman.cpp
Used as the player class. holds the score ,lives and handles movement

9) PacmanState.cpp
A singleton class that handles all whats comes with pacman different states
(i.e superPacman, freezing pacman and so on...)
this class handles mainly ghost movement, ghost textures.
in addition it tells to whomever interested what exactly is pacman state

10) Render.cpp
This class handles all the window presentation and rendering
e.g the game looop itsel

11) Resources.cpp
This is a static singleton class. it provides and handles
all game graphics and sound


Interaction:
Controller creates Render and MainMenu wich from this point will take charge of the program
MainMenu runs ths MenuLoop (using Render's window) and activates the chosen users clicks
When 'Play Game' pressed Render activates the GameLoop
GameLoop creates Board and HUD wich will from now on will lead the live gameplay
Render will handle the game over and start new game situations

In Game interactions:
Board will update all the game objects (excepts pacman)
using Collision's handle functions
Ghost will move using PacamState methods
pacman will interact only with the keyboard

====================================================================

                          Known bugs
                        ===============



=====================================================================

                            Comments
                         ==============
1. The levels are read from the "Board.txt" file
    In the first line will be the time specified in this template: 00:00
    The second row will have the number of rows and columns that will indicate the size of the board
    After that there will be a drawing of the board itself.
    The characters that represented the stage:
    a- Pacman
    p, r, o, g - ghosts
    $, T, L, I - presents
    # - wall
    % - key
    D - door
    * - cookie
    Space - an empty slot
    There will be a blank line between a step.


2. Super Pacman, a gift of increasing time and freezing the ghosts - all set for a time of 8 seconds

3. The game do not supports going 'through' game boundries to the other side

=====================================================================

