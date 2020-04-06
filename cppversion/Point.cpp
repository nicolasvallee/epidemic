#include <iostream>
#include <vector> 
#include <cmath>
#include "Point.hpp"
#include "Constants.hpp"
#include "Utils.hpp"

Point::Point(Position position, Position speed, int mass, bool mobile)
    :m_position{position}, m_speed{speed}, m_mass{mass}, m_mobile{mobile}
{
}


Position Point::getPosition() const { return m_position;}

void Point::setPosition(Position pos)
{
    if(m_mobile == true)
    {
        m_position = pos;
    }
}
int Point::getMass() const {return m_mass;}

Position Point::getSpeed() const{ return m_speed; }

void  Point::setSpeed(Position speed){ m_speed = speed; }


double Point::getDistanceTo(Point p) const
{
    Position difference = m_position - p.m_position;
    return getNorm(difference);
}

bool Point::isSafeToMove(Position p) const
{
    return (p.x >= 0 && p.x < MAP_WIDTH && p.y >= 0 && p.y < MAP_HEIGHT);
}

//Points must be inside when calling this function
std::vector<Point> Point::getClosestWalls() const
{
    std::vector<Point> walls;
    double x = m_position.x, y = m_position.y;
    std::vector<Position> positions{{x,0}, {x,MAP_HEIGHT-1}, {0,y}, {MAP_WIDTH-1,y}};
    for(int i = 0; i < 4; i++)
    {    
        walls.push_back(Point{positions[i], Position{0,0}, WALL_MASS, false});
    }
    return(walls);
}

void Point::putBackInside()
{                                        
    int px = m_position.x;
    int py = m_position.y;
    int x = px, y = py;

    if(px < 0)
        x = 0;
    else if(px > MAP_WIDTH-1)
        x = MAP_WIDTH - 1;
    if(py < 0)
        y = 0;
    else if(py > MAP_HEIGHT-1)
        y = MAP_HEIGHT - 1;

    m_position = Position{(double)x, (double)y};
}

Position Point::getGravityForce(Point point) const
{
    double dist = getDistanceTo(point);
    Position force;
    force = (point.m_position - m_position) * BIG_G * m_mass * point.m_mass * (1/pow((dist+0.1), 3));
    return force;
}


void Point::move()
{
    if(m_mobile == true)
    {  
        Position new_position = m_position;
        Position dpos = Position{m_speed.x * dt, m_speed.y * dt};
        new_position = new_position + dpos;

        if(isSafeToMove(new_position))
            m_position = new_position;
        else
            putBackInside();
        
    }
}
