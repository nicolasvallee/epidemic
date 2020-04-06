#ifndef POPULATION_H
#define POPULATION_H
#include <vector>
#include "Person.hpp"

class Person;

class Population
{
    std::vector<Person> m_people;
public:
    Population(int size);
    int getSize() const;
    std::vector<Person>& getPeople();
    void update();


};
#endif