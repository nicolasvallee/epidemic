#ifndef PERSON_H
#define PERSON_H

#include "Point.hpp"
#include "Constants.hpp"

class Population;

class Person: public Point
{
    Health m_health_state = SUSCEPTIBLE;
    int m_infection_duration = 0;
    
public:
    Person(Position position, Position speed=Position{0,0},
    Health health_state=SUSCEPTIBLE,
    int mass=1, bool mobile=true);

    Health getHealthState() const;

    void setHealthState(Health state);

    int getInfectionDuration() const;

    void addInfectionDuration();

    bool hasRecovered() const;

    void updateSpeed(const std::vector<Person> &people);

    void contaminate(std::vector<Person> &people);

    bool willDie() const;

};

#endif