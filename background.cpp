#include "background.h"
#include <iostream>

//Constructs background object and Pixmap for representing background image
Background::Background(std::string imagePath, int scrollSpeed)
    : m_imagePath(imagePath),
      m_scrollSpeed(scrollSpeed)
{
    m_backgroundImage = new QPixmap(m_imagePath.c_str());
    m_height = m_backgroundImage->height();
    m_width = m_backgroundImage->width();
    m_position = 0;
}

Background::~Background()
{
    delete m_backgroundImage;
}

//Returns the image path
const std::string& Background::getImagePath() const
{
    return m_imagePath;
}

//Sets the image path
void Background::setImagePath(const std::string &imagePath)
{
    m_imagePath = imagePath;
}

//Returns the scroll speed
const int& Background::getScrollSpeed() const
{
    return m_scrollSpeed;
}

//Sets the scroll speed
void Background::setScrollSpeed(int scrollSpeed)
{
    m_scrollSpeed = scrollSpeed;
}

//Takes QPainter reference to draw the background image.
//Tiles two separate image to scroll seamlessly.
void Background::renderBackground(bool updateFlag, QPainter &painter, bool animated) const
{
    if (animated && updateFlag)
    {
        m_position -= m_scrollSpeed;
        if (m_position + m_width <= 0)
        {
            m_position += m_width;
        }
    }

    painter.drawPixmap(m_position, 0, *m_backgroundImage);
    painter.drawPixmap(m_position + m_width, 0, *m_backgroundImage);
}
