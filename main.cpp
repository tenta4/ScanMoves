#include "gamemodule.h"
#include "movecreator.h"
#include "Qdebug"
int main(int argc, char** argv)
{
    if (argc == 0 ) GameModule gm;
    else
    {
        MoveCreator mc(argv[1]);
        qDebug()<<"test";

    }
    return 0;
}
