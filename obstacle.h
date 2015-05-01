#ifndef OBSTACLE_H
#define OBSTACLE_H


class Obstacle
{
public:
    Obstacle(int start_y, int spacing);

    int getY() const;
    int getSpacing() const;
    int getX() const;
    void setX(int x);

protected:
    int m_y;
    int m_x;
    int m_spacing;
};

#endif // OBSTACLE_H
