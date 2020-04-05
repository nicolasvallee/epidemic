#include <vector>
#include <cmath>
#include "Utils.hpp"
#include "Person.hpp"


Position matrix_vector_product(std::vector<std::vector<double>> matrix, Position vect)
{   
    Position ans;
    ans.x = vect.x * matrix[0][0] + vect.y * matrix[0][1];
    ans.y = vect.x * matrix[1][0] + vect.y * matrix[1][1];
    return ans;
}

Position rotate_vector(Position vect, double angle) //trigonometric direction
{       
    std::vector<std::vector<double>> rotation_matrix{ {cos(angle), -sin(angle)}, {sin(angle), cos(angle)} };
    return matrix_vector_product(rotation_matrix, vect);
}

std::vector<Person> generate_population(int size)
{
    std::vector<Person> population1;
    Person patient_zero = Person(CENTER, INFECTIOUS);
    population1.push_back(patient_zero);
    for(int i = 0; i < size-1; i++)
    {
        population1.push_back(Person(random_position(), SUSCEPTIBLE));
    }
    return population1;
}

double get_norm(Position P)
{
    return(sqrt(pow((P.x),2) + pow((P.y),2)));
}

void update_population()
{
    for(Person person : population)
    {
        if(person.get_health_state() == DEAD)
            continue;
        if(person.get_health_state() == INFECTIOUS)
        {
            if(person.will_die())
            {
                person.set_health_state(DEAD);
                continue;
            }
            
            person.add_infection_duration();
            if(person.has_recovered())
                person.set_health_state(RECOVERED);
            else
                person.contaminate_population();
        }
        person.move();
    }
}


Position random_position()
{   
    return Position{random() % MAP_WIDTH, random() % MAP_HEIGHT};
    
}

Position random_direction()
{   
    return Position{random() % 20 - 10, random() % 20 - 10};
}