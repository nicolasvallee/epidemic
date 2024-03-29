#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include "Position.hpp"


const int MAP_HEIGHT = 1000;
const int MAP_WIDTH = 1500;
const int NB_COMMUNITIES = 9;
const int INIT_COMMUNITY_SIZE = 20;
const int NB_CYLES = 100;
enum Health{SUSCEPTIBLE, INFECTIOUS, RECOVERED, DEAD};

const int INFECTION_RADIUS = 10;
const double PROB_INFECION = 0.6;
const double DEATH_RATE = 0.0001;
const int INFECTION_DURATION = 60 * 10;

const double dt = 1.0/60.0; //seconds
const double BIG_G = 1e4;
const double pi = 3.14159;
const int WALL_MASS = 50;
const int PERSON_MASS = 1;
const double IS_MOBILE = true;
const double AVOID_PERSON_RADIUS = 100;
const double SPEED_FACTOR = 2;
const double ROTATION_AMPLITUDE = 6;
const double VISCOSITY = 0.01;

const Position POS_OUT_OF_BOUNDS = Position{-1000, -1000};
const Position DIR_OUT_OF_BOUNDS = Position{2 * MAP_HEIGHT, 2 * MAP_WIDTH};
const Position CENTER = Position{MAP_WIDTH/2, MAP_HEIGHT/2};
const Position UPPER_LEFT_MAP = Position{0,0};
const Position LOWER_RIGHT_MAP = Position{MAP_WIDTH-1, MAP_HEIGHT-1};



#endif