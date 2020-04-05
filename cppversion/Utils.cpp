#include <vector>
#include <cmath>
#include "Utils.hpp"
#include "Person.hpp"


Position matrixVectorProduct(std::vector<std::vector<double>> matrix, Position vect)
{   
    Position ans;
    ans.x = vect.x * matrix[0][0] + vect.y * matrix[0][1];
    ans.y = vect.x * matrix[1][0] + vect.y * matrix[1][1];
    return ans;
}

Position rotateVector(Position vect, double angle) //trigonometric direction
{       
    std::vector<std::vector<double>> rotation_matrix{ {cos(angle), -sin(angle)}, {sin(angle), cos(angle)} };
    return matrixVectorProduct(rotation_matrix, vect);
}

std::vector<Person> generatePopulation(int size)
{
    std::vector<Person> population1;
    Person patient_zero = Person(CENTER, randomDirection(),
    INFECTIOUS, PERSON_MASS, IS_MOBILE);
    population1.push_back(patient_zero);
    for(int i = 0; i < size-1; i++)
    {
        population1.push_back(Person(randomPosition(), randomDirection(), SUSCEPTIBLE, PERSON_MASS, IS_MOBILE));
    }
    return population1;
}

double getNorm(Position vector)
{
    return(sqrt(pow((vector.x),2) + pow((vector.y),2)));
}

void updatePopulation()
{
    int size = population.size();
    for(int i = 0; i < size; i++)
    {
        Person &person = population[i];
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
                person.contaminatePopulation();
        }
        person.move();
    }
}


Position randomPosition()
{   
    return Position{rand() % MAP_WIDTH, rand() % MAP_HEIGHT};
    
}

Position randomDirection()
{   
    return Position{rand() % 20 - 10, rand() % 20 - 10};
}