#include "dialog.h"
#include "ui_dialog.h"

#include <iostream>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_counter(0),
    m_paused(false)
{

    ui->setupUi(this);
    this->update();

    //Construct the buttons and connect them to the appropriate handler functions
    saveButton = new QPushButton(this);
    quitButton = new QPushButton(this);
    saveButton->setText("Save");
    quitButton->setText("Quit");
//    saveButton->setFocusPolicy(Qt::NoFocus);
//    quitButton->setFocusPolicy(Qt::NoFocus);
    connect(saveButton, SIGNAL(released()), this, SLOT(handleSaveButton()));
    connect(quitButton, SIGNAL(released()), this, SLOT(handleQuitButton()));

    //Construct the timer and connect to the nextFrame slot
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    m_timer->start(32);

    m_update_flag = false;

    //Construct the QLabel for displaying the character animation
    //Idk where this went??? But it's working...


}

Dialog::~Dialog()
{
    delete ui;
    delete saveButton;
    delete quitButton;

    //Added
    delete m_timer;
}

//Sets the game pointer to the game constructed by the builder
void Dialog::setGame(Game *game)
{
    m_game = game;
    setSize(m_game->getXDimension(), m_game->getYDimension());
    m_game->getPlayer()->m_moving_player.beginPlayerAnimation(this);



    gameInfo game_info;
    game_info.obstacle_speed = atoi(m_FileIO->getValues("background-speed"));
    game_info.x_dimension = atoi(m_FileIO->getValues("x-dimension"));
    game_info.y_dimension = atoi(m_FileIO->getValues("y-dimension"));
    m_game->setObstacles(new ObstacleCollection(m_FileIO->getObstacleProperties(), game_info));

    m_game->getPlayer()->m_moving_player.set_obstacle_list_pointer(
                m_game->getObstacles()->getObstacles());

    m_game->getBackground()->setCollision(
        m_game->getPlayer()->m_moving_player.get_collision());

    m_game->getObstacles()->setCollision(
        m_game->getPlayer()->m_moving_player.get_collision());

}

void Dialog::setFileIO(FileIO *fileReader)
{
    m_FileIO = fileReader;
}

//Resizes the dialog box
void Dialog::setSize(int width, int height)
{
    this->resize(width, height);
}

//If the game is not paused, calls update()
void Dialog::nextFrame()
{  
    if (!m_paused) {
        saveButton->hide();
        quitButton->hide();
        update();
        m_update_flag = true;
    } else {
        saveButton->setGeometry(this->width()/3, this->height()/3, 100, 50);
        quitButton->setGeometry(2*this->width()/3 - 100, this->height()/3, 100, 50);
        saveButton->show();
        quitButton->show();
    }
}

void Dialog::handleSaveButton()
{
    m_FileIO->saveGame(m_game);
}

void Dialog::handleQuitButton()
{
    this->close();
}

//Handles the key events:
//'P' pauses the game
//'<' and '>' increment the player position
void Dialog::keyPressEvent(QKeyEvent *event)
{

    //Pause Event
    if (event->key() == Qt::Key_P && !m_paused) {
        m_paused = true;
        m_game->getPlayer()->m_moving_player.pause(m_paused);
    } else if (event->key() == Qt::Key_P && m_paused) {
        m_paused = false;
        m_game->getPlayer()->m_moving_player.pause(m_paused);
    }

    if (!m_paused) {
        std::string jump_flag = m_FileIO->getValues("jump-flag");

        if (event->key() == Qt::Key_Period)
        {
            m_game->getPlayer()->m_moving_player.movePlayerX(2);
        }
        else if (event->key() == Qt::Key_Comma)
        {
            m_game->getPlayer()->m_moving_player.movePlayerX(-2);
        }
        //Initiate jump sequence if not currently mid-jmp
        else if (event->key() == Qt::Key_Space
                   && !m_game->getPlayer()->m_moving_player.is_jumping()
                   && strcmp(jump_flag.c_str(), "on") == 0)
        {
           m_game->getPlayer()->m_moving_player.set_jumping(true);
        }
    }
}

//Renders the background image
void Dialog::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    m_game->getPlayer()->m_moving_player.jump(m_update_flag, painter);
    m_game->getBackground()->renderBackground(m_update_flag, painter, !m_paused);

    std::string obst_flag = m_FileIO->getValues("obstacle-flag");
    if (strcmp(obst_flag.c_str(), "on") == 0)
    {
        m_game->getObstacles()->renderObstacles(m_update_flag, painter, !m_paused);
    }
    m_update_flag = false;
    m_counter++;
}
