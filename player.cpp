#include "player.h"

//Constructs the player and the QMovie that handles the GIF animation
Player::Player(std::string imagePath, std::string size, int initialPosition)
    : m_imagePath(imagePath),
      m_size(size),
      m_initialPosition(initialPosition)
{
    m_playerAnimation = new QMovie(m_imagePath.c_str());
}

Player::~Player()
{
    delete m_label;
    delete m_playerAnimation;
}

//Returns the image path
std::string Player::getImagePath() const
{
    return m_imagePath;
}

//Sets the image path
void Player::setImagePath(const std::string &imagePath)
{
    m_imagePath = imagePath;
}

//Returns the size of the player mapped to integer values
int Player::getSize() const
{
    if (m_size == "tiny") {
        return 50;
    } else if (m_size == "normal") {
        return 80;
    } else if (m_size == "large") {
        return 120;
    } else if (m_size == "giant") {
        return 180;
    } else {
        return -1;
    }
}

//Updates the player size
void Player::setSize(const std::string &size)
{
    m_size = size;
}


//Returns the initial player position as specified in the config file
int Player::getInitialPosition() const
{
    return m_initialPosition;
}

int Player::getCurrentPosition() const
{
    return m_label->x();
}

//Takes QLabel reference, assigns it the QMovie object, and begins animation
void Player::beginPlayerAnimation(QWidget * dialog)
{
    //Assign the QLabel to the given QDialog
    m_label = new QLabel(dialog);

    int playerSize = getSize();
    m_playerAnimation->setScaledSize(QSize(playerSize, playerSize));

    //The second argument here is to account for the gap between the GIFs feet and the bottom of the image
    m_label->setGeometry(m_initialPosition, 487-playerSize + 9*playerSize/1000, 150, playerSize);
    m_label->setMovie(m_playerAnimation);
    m_playerAnimation->setSpeed(300);
    m_playerAnimation->start();
}

//Increments the player's x-coordinate by some amount
void Player::movePlayer(int amount)
{
    m_label->move(m_label->x() + amount, m_label->y());

}

//Pauses and unpauses the player animation
void Player::pause(bool paused) {
    m_playerAnimation->setPaused(paused);
}
