#include "Controller.h"
#include "Graphics.h"
#include "MainMenu.h"
#include "Board.h"

int main()
{
    auto controller = Controller();
    controller.run();
 
    return EXIT_SUCCESS;
}
