#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include "Position.hpp"


const int MAP_HEIGHT = 1000;
const int MAP_WIDTH = MAP_HEIGHT;
const int NB_CYLES = 100;
enum Health{SUSCEPTIBLE, INFECTIOUS, RECOVERED, DEAD};

const int INFECTION_RADIUS = 20;
const double PROB_INFECION = 0.2;
const double DEATH_RATE = 0.001;
const int INFECTION_DURATION = 1000;
const double dt = 1/60; //seconds
const int BIG_G = 1e5;
const double pi = 3.14159;

const Position POS_OUT_OF_BOUNDS = Position{-1000, -1000};
const Position DIR_OUT_OF_BOUNDS = Position{2 * MAP_HEIGHT, 2 * MAP_WIDTH};
const Position CENTER = Position{MAP_WIDTH/2, MAP_HEIGHT/2};

//AYA
class Person; // do NOT include Person.hpp because that header already includes constants
extern std::vector<Person> population;

#endif