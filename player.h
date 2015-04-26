#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <QLabel>
#include <QMovie>

//Handles player variables and animation
class Player
{
public:
    Player(std::string imagePath, std::string size, int initialPosition);
    ~Player();

    std::string getImagePath() const;
    void setImagePath(const std::string& imagePath);

    int getSize() const;
    void setSize(const std::string& size);

    int getInitialPosition() const;
    int getCurrentPosition() const;

    void beginPlayerAnimation(QWidget * dialog);
    void movePlayer(int amount);
    void pause(bool paused);

protected:
    std::string m_imagePath;
    std::string m_size;
    int m_initialPosition;

    QMovie * m_playerAnimation;
    QLabel * m_label;

};

#endif // PLAYER_H
