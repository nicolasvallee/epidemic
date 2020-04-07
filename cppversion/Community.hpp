#ifndef COMMUNITY_H
#define COMMUNITY_H
#include <vector>
#include "Person.hpp"

class Person;

class Community
{
    std::vector<Person> m_people;
public:
   // Community();
    Community(int size);

    int getSize() const;

    std::vector<Person>& getPeople(); //has to be a non-const method for the moment
    const std::vector<Person>& getPeopleConst() const;  //not pretty
    void update();


};
#endif