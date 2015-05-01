#ifndef OBSTACLE_H
#define OBSTACLE_H


class Obstacle
{
public:
    Obstacle();
    int setStartY(int start_y);
    int getStartY() const;

    int setHeight(int height);
    int getHeight() const;

    int setWidth(int width);
    int getWidth() const;

    int setSpacing(int spacing);
    int getSpacing() const;

protected:
    int m_start_y;
    int m_height;
    int m_width;
    int m_spacing;
};

#endif // OBSTACLE_H
