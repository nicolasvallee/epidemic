#include <cstdlib>
#include "Person.hpp"
#include "Constants.hpp"
#include "Utils.hpp"


Person::Person(Position position, Position speed, Health health_state, int mass, bool mobile)
    : Point{position, speed, mass, mobile}, m_health_state{health_state}
{
}

Health Person::getHealthState() const { return m_health_state; }

void Person::setHealthState(Health state) { m_health_state =  state; }

int Person::getInfectionDuration() const { return m_infection_duration; }

void Person::addInfectionDuration() { m_infection_duration++; }

void Person::updateSpeed(const std::vector<Person> &people) 
{
    Position force{0,0};
    for(Person person : people)
    {       
        if(getDistanceTo(person) <= AVOID_PERSON_RADIUS)
        {
            Position g_force = getGravityForce(person);
            force = force - g_force;
        }
    }
    std::vector<Point> walls = getClosestWalls();
    for(Point wall : walls)
    {
        Position g_force = getGravityForce(wall);
        force = force - g_force;
    }
    
    Position perpendicular_force;
    perpendicular_force = rotateVector(getSpeed(), (double)(-2*(rand() % 2 == 0)+1) * pi/2);
    perpendicular_force = perpendicular_force * ROTATION_AMPLITUDE;
    force =  force + perpendicular_force;

    //random_force = np.array([randint(-100,100) for i in range(2)])
    //force = force + random_force
    
    //viscosity
    force = force - getSpeed() * getNorm(getSpeed()) * VISCOSITY;
    
    setSpeed(getSpeed() + force * (1/getMass()) * dt * SPEED_FACTOR);
}

bool Person::hasRecovered() const 
{
    return m_infection_duration > INFECTION_DURATION;
}

void Person::contaminate(std::vector<Person> &people)
{
    for(Person &person : people)
        if(person.m_health_state == SUSCEPTIBLE 
        && getDistanceTo(person) <= INFECTION_RADIUS)
            if(randomUniform() <= PROB_INFECION)
                person.m_health_state = INFECTIOUS;
}

bool Person::willDie() const
{
    return randomUniform() <= DEATH_RATE;
}
