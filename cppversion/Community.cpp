#include "Community.hpp"
#include "Utils.hpp"



Community::Community(int size)
{
    Person patient_zero = Person(CENTER, randomDirection(),
    INFECTIOUS, PERSON_MASS, IS_MOBILE);
    m_people.push_back(patient_zero);

    for(int i = 0; i < size-1; i++)
        m_people.push_back(Person(randomPosition(), randomDirection(),
        SUSCEPTIBLE, PERSON_MASS, IS_MOBILE));
    
}

int Community::getSize() const {return m_people.size();}

std::vector<Person>& Community::getPeople() {return m_people;}

const std::vector<Person>& Community::getPeopleConst() const {return m_people;}

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
