//This is for my general useful functions
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "Position.hpp"
#include "Person.hpp"



std::vector<Person> generateCommunity(int size);

void updateCommunity();

std::vector<double> matrixVectorProduct(std::vector<double> *matrix, Position vect);

Position rotateVector(Position vect, double angle); //trigonometric direction

double getNorm(Position P);

float randomUniform();

Position randomPosition(Position upper_left_bound = UPPER_LEFT_MAP,
                        Position lower_left_bound = LOWER_RIGHT_MAP);

Position randomDirection();


#endif