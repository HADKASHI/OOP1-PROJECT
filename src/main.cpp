#include "Macros.h"
#include "Controller.h"
#include "Resources.h"
#include "Board.h"

int main()
{
    auto controller = Controller();
    controller.run();
 
    return EXIT_SUCCESS;
}
