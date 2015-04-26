#include <QApplication>

#include "gameengine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Constructs GameEngine and starts the game
    GameEngine game;

    //If the game builds successfully, return the QApplication exec - else exit;
    if (game.running()) {
        return a.exec();
    } else {
        return 0;
    }

}

