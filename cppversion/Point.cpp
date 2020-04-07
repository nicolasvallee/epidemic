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

std::vector<Position> Point::getBounds() const
{
    std::vector<Position> bounds = {UPPER_LEFT_MAP, LOWER_RIGHT_MAP};
    return bounds;
}

bool Point::isSafeToMove(Position p) const
{
    //Bounds are included : they are safe to move onto.
    //Rememeber that the origin of the screen (0,0) is at the TOP left corner
    //This implies that upper_ has a lower y coordinate than lower_ ...
    std::vector<Position> bounds = getBounds();
    Position upper_left_bound = bounds[0];
    Position lower_right_bound = bounds[1];
    bool safe = p.x >= upper_left_bound.x && p.x <= lower_right_bound.x 
            && p.y >= upper_left_bound.y && p.y <= lower_right_bound.y;

    return safe;
}

//Points must be inside when calling this function
std::vector<Point> Point::getClosestWalls() const
{
    std::vector<Point> walls;
    double x = m_position.x, y = m_position.y;
    std::vector<Position> bounds = getBounds();
    Position upper_left = bounds[0];
    Position lower_right = bounds[1];
    std::vector<Position> wall_positions;
    wall_positions.push_back({x,upper_left.y});
    wall_positions.push_back({x,lower_right.y});
    wall_positions.push_back({upper_left.x,y});
    wall_positions.push_back({lower_right.x,y});

    for(int i = 0; i < 4; i++)
        walls.push_back(Point{wall_positions[i], Position{0,0}, WALL_MASS, false});

    return(walls);
}

void Point::putBackInside()
{                         
    std::vector<Position> bounds = getBounds();
    Position upper_left = bounds[0];
    Position lower_down = bounds[1];

    if(m_position.x < upper_left.x)
        m_position.x = upper_left.x+1;
    else if(m_position.x > lower_down.x)
        m_position.x = lower_down.x-1;
    if(m_position.y < upper_left.y)
        m_position.y = upper_left.y+1;
    else if(m_position.y > lower_down.y)
        m_position.y = lower_down.y-1;

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
