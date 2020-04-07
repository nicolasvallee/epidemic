#include "Community.hpp"
#include "Utils.hpp"
#include <iostream>


Community::Community(int size, Position upper_left_bound, Position lower_left_bound)
    :m_upper_left_bound{upper_left_bound}, m_lower_right_bound{lower_left_bound}
{

    //The people's communities should not be set here
    //Because when world push_backs this community
    //It makes a copy of the community, so the THIS pointer changes !!!
    Position center = getCenter();

    Person patient_zero = Person(center, randomDirection(),
    INFECTIOUS, PERSON_MASS, IS_MOBILE);
    m_people.push_back(patient_zero);
    for(int i = 0; i < size-1; i++)
    {
        Person person{randomPosition(upper_left_bound, lower_left_bound), randomDirection(),
        SUSCEPTIBLE, PERSON_MASS, IS_MOBILE};
        m_people.push_back(person);
    }
    
}

void Community::initializePeopleCommunities()
{
    for(Person &person : m_people)
    {
        person.setCommunity(this);
    }
}

int Community::getSize() const {return m_people.size();}

std::vector<Person>& Community::getPeople() {return m_people;}

const std::vector<Person>& Community::getPeopleConst() const {return m_people;}

std::vector<Position> Community::getBounds() const
{
    std::vector<Position> bounds = {m_upper_left_bound, m_lower_right_bound};
    return bounds; 
}

Position Community::getCenter() const
{
    return (m_upper_left_bound + m_lower_right_bound) * (0.5);
}

void Community::update()
{
    int size = getSize();
    for(int i = 0; i < size; i++)
    {
        Person &person = m_people[i];
        if(person.getHealthState() == DEAD)
            continue;
        if(person.getHealthState() == INFECTIOUS)
        {
            if(person.willDie())
            {
                person.setHealthState(DEAD);
                continue;
            }
            
            person.addInfectionDuration();
            if(person.hasRecovered())
                person.setHealthState(RECOVERED);
            else
                person.contaminate(getPeople());
        }
        person.move();
        person.updateSpeed(getPeople());
    }
}
