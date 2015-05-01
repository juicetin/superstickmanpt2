#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>
#include <QPixmap>
#include <QPainter>

class Background
{
public:
    Background(std::string imagePath, int scrollSpeed);
    ~Background();

    const std::string& getImagePath() const;
    void setImagePath(const std::string& imagePath);

    const int& getScrollSpeed() const;
    void setScrollSpeed(int scrollSpeed);

    void renderBackground(bool updateFlag, QPainter &painter, bool animated) const;

protected:
    std::string m_imagePath;
    int m_scrollSpeed;

    mutable int m_position;
    int m_height;
    int m_width;

    QPixmap * m_backgroundImage;
};

#endif // BACKGROUND_H
