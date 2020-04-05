#ifndef POINT_H
#define POINT_H

#include <vector>
#include "Position.hpp"

//population is given to move() and update_speed() -> is that bad ?


class Point
{

    Position m_position;
    Position m_speed;
    int m_mass;
    bool m_mobile;

public:
    Point(Position position, Position speed = Position{0,0}, int mass=1, bool mobile=true);

    Position getPosition();
    void setPosition(Position pos);
    int getMass();
    Position getSpeed();
    void setSpeed(Position speed);
    double getDistanceTo(Point p);

    bool isSafeToMove(Position p);

    //Points must be inside when calling this function
    std::vector<Point> getClosestWalls();

    void putBackInside();

    virtual void updateSpeed();

    Position getGravityForce(Point point);

    void move();

};

#endif