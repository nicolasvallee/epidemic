#ifndef POINT_H
#define POINT_H

#include <vector>
#include "Position.hpp"

//population is given to move() and update_speed() -> is that bad ?


class Point
{

    Position m_position;
    int m_mass{1};
    bool m_mobile{true};
    Position m_speed{0,0};

public:
    Point(Position position);
    Point(Position position, Position speed, int mass, bool mobile);

    Position get_position();
    void set_position(Position pos);
    int get_mass();
    Position get_speed();
    void set_speed(Position speed);
    double get_distance_to(Point p);

    bool is_safe_to_move(Position p);

    //Points must be inside when calling this function
    std::vector<Point> get_closest_walls();

    void put_back_inside();

    virtual void update_speed();

    Position get_gravity_force(Point point);

    void move();

};

#endif