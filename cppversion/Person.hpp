#ifndef PERSON_H
#define PERSON_H

#include "Point.hpp"
#include "Constants.hpp"

class Person: public Point
{
    Health m_health_state = SUSCEPTIBLE;
    int m_infection_duration = 0;
    
public:
    Person(Position position, Position speed=Position{0,0}, Health health_state=SUSCEPTIBLE,
    int mass=1, bool mobile=true);

    Health getHealthState();
    void setHealthState(Health state);
    int getInfectionDuration();

    void addInfectionDuration();
    bool hasRecovered();
    void updateSpeed();
    void contaminatePopulation();
    bool willDie();

};

#endif