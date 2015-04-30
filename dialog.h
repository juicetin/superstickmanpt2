#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <QKeyEvent>
#include <QPushButton>

#include "game.h"
#include "fileio.h"

namespace Ui {
class Dialog;
}

//Handles draw and key events
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void setGame(Game * game);
    void setFileIO(FileIO * fileReader);
    void setSize(int width, int height);

public slots:
    void nextFrame();
    void handleSaveButton();
    void handleQuitButton();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent* event);

private:
    Ui::Dialog *ui;
    int m_counter;
    bool m_paused;

    QPushButton * saveButton, * quitButton;
    Game * m_game;
    FileIO * m_FileIO;

    //Added
    QTimer *m_timer;
    bool m_update_flag;
};

#endif // DIALOG_H
