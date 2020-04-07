#ifndef PERSON_H
#define PERSON_H

#include "Point.hpp"
#include "Constants.hpp"

class Person;

class Community
{
    std::vector<Person> m_people;

    Position m_upper_left_bound;
    Position m_lower_right_bound;

public:
   // Community();
    Community(int size, Position upper_left_bound = UPPER_LEFT_MAP,
                Position lower_right_bound = LOWER_RIGHT_MAP);
        
    void initializePeopleCommunities();

    int getSize() const;

    std::vector<Person>& getPeople(); //has to be a non-const method for the moment

    const std::vector<Person>& getPeopleConst() const;  //not pretty

    std::vector<Position> getBounds() const;

    Position getCenter() const;

    void update();


};


class Person: public Point
{
    Health m_health_state = SUSCEPTIBLE;
    int m_infection_duration = 0;
    Community *m_community = nullptr;
    bool travelling = false;
    Position destination;
    
public:
    Person(Position position, Position speed=Position{0,0},
    Health health_state=SUSCEPTIBLE,
    int mass=1, bool mobile=true);
    
    Health getHealthState() const;

    void setHealthState(Health state);

    int getInfectionDuration() const;

    Community* getCommunity();

    void setCommunity(Community *community);

    std::vector<Position> getBounds() const;

    void addInfectionDuration();

    bool hasRecovered() const;

    void updateSpeed(const std::vector<Person> &people);

    void contaminate(std::vector<Person> &people);

    bool willDie() const;

};

#endif