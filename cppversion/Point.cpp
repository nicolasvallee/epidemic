#include <iostream>
#include <vector> 
#include <cmath>
#include "Point.hpp"
#include "Position.hpp"
#include "Constants.hpp"
#include "Utils.hpp"

Point::Point(Position position, Position speed, int mass, bool mobile)
    :m_position{position}, m_speed{speed}, m_mass{mass}, m_mobile{mobile}
{
}


Position Point::get_position(){ return m_position;}
void Point::set_position(Position pos)
{
    if(m_mobile == true)
    {
        m_position = pos;
    }
}
int Point::get_mass(){return m_mass;}

Position Point::get_speed(){ return m_speed; }
void  Point::set_speed(Position speed){ m_speed = speed; }


double Point::get_distance_to(Point p)
{
    Position difference = m_position - p.m_position;

    return get_norm(difference);
}

bool Point::is_safe_to_move(Position p)
{
    return (p.x >= 0 && p.x < MAP_HEIGHT && p.y >= 0 && p.y < MAP_WIDTH);
}

//Points must be inside when calling this function
std::vector<Point> Point::get_closest_walls()
{
    std::vector<Point> walls;
    int x = m_position.x, y = m_position.y;
    std::vector<Position> positions{{x,0}, {x,MAP_HEIGHT-1}, {0,y}, {MAP_WIDTH-1,y}};
    for(int i = 0; i < 4; i++)
    {    
        walls.push_back(Point{positions[i], Position{0,0}, WALL_MASS, false});
    }
    return(walls);
}

void Point::put_back_inside()
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

    m_position = Position{x, y};
}

void Point::update_speed()
{    
    std::cout << "the INSIDE of this function should NOOOOT be called" << '\n';
}

Position Point::get_gravity_force(Point point)
{
    double dist = get_distance_to(point);
    Position force;
    force = (point.m_position - m_position) * BIG_G * m_mass * point.m_mass * (1/pow((dist+1), 3));
    return force;
}


void Point::move()
{
    if(m_mobile == true)
    {  
        Position new_position = m_position;
    
        update_speed();
        Position dpos = Position{m_speed.x * dt, m_speed.y * dt};
        new_position = new_position + dpos;
    
        if(is_safe_to_move(new_position))
            m_position = new_position;
        else
            put_back_inside();
        
    }
}
