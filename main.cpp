#include "gamemodule.h"
#include "movecreator.h"
#include "Qdebug"
int main(int argc, char** argv)
{
    if (argc == 1 )
        GameModule gm;
    else
    {
        MoveCreator mc(argv[1]);
    }
    return 0;
}
