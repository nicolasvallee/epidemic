#include <cstdlib>
#include "Person.hpp"
#include "Position.hpp"
#include "Constants.hpp"
#include "Utils.hpp"


Person::Person(Position position, Health health_state)
    : Point{position}, m_health_state{health_state}
{
}

Person::Person(Position position, Position speed, Health health_state, int mass, bool mobile)
    : Point{position, speed, mass, mobile}, m_health_state{health_state}
{
}

Health Person::get_health_state(){ return m_health_state;}
void Person::set_health_state(Health state){ m_health_state =  state;}

void Person::add_infection_duration()
{
    m_infection_duration++;
}
bool Person::has_recovered()
{
    return m_infection_duration > INFECTION_DURATION;
}

void Person::update_speed()
{
    Position force{0,0};
    for(Person person : population)
    {       
            Position g_force = get_gravity_force(person);
            force = force - g_force;
    }
    std::vector<Point> walls = get_closest_walls();
    for(Point wall : walls)
    {
        Position g_force = get_gravity_force(wall);
        force = force - g_force;
    }
    
    int b = 4;
    Position perpendicular_force;
    perpendicular_force = rotate_vector(get_speed(), (-2*(random() % 2 == 0)+1) * pi/4);
    perpendicular_force = force * b;
    force =  force + perpendicular_force;

    //random_force = np.array([randint(-100,100) for i in range(2)])
    //force = force + random_force
    
    double viscosity = 0.02;
    force = force - get_speed() * viscosity;
    force = force - get_speed() * get_norm(get_speed()) * viscosity;
    set_speed(get_speed() + force * (1/get_mass()) * dt);
}



void Person::contaminate_population()
{
    for(Person person : population)
        if(person.m_health_state == SUSCEPTIBLE && get_distance_to(person) <= INFECTION_RADIUS)
            if(random()/(RAND_MAX+1) <= PROB_INFECION)
                person.m_health_state = INFECTIOUS;
}

bool Person::will_die()
{
    double p = random() / (RAND_MAX + 1);
    return p <= DEATH_RATE;
}
