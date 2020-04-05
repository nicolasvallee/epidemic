#ifndef POSITION_H
#define POSITION_H

struct Position{
    double x, y;

    Position operator+(Position b) const
    {
        return Position{x + b.x, y + b.y};
    }
    //ARE U SURE THE - is in the right order?
    Position operator-(Position b) const
    {
        return Position{x - b.x, y - b.y};
    }
    Position operator*(double scalar) const
    {
        return Position{scalar * x, scalar * y};
    }
    bool operator==(Position &b) const
    {
        return (x == b.x && y == b.y);
    }
    bool operator!=(const Position &b) const
    {
        return !(x == b.x && y == b.y);
    }
   
   
};
#endif