#ifndef PERSON_H
#define PERSON_H

#include "Point.hpp"
#include "Constants.hpp"

class Person: public Point
{
    Health m_health_state = SUSCEPTIBLE; 
    int a = MAP_WIDTH;
    int m_infection_duration = 0;
    
public:
    Person(Position position, Health health_state);
    Person(Position position, Position speed, Health health_state, int mass, bool mobile);
    Health get_health_state();
    void set_health_state(Health state);

    void add_infection_duration();
    bool has_recovered();
    void update_speed();
    void contaminate_population();

    bool will_die();

};

#endif