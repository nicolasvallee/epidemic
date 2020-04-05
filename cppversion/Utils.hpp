//This is for my general useful functions
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "Position.hpp"
#include "Person.hpp"

std::vector<double> matrixVectorProduct(std::vector<double> *matrix, Position vect);

Position rotateVector(Position vect, double angle); //trigonometric direction

std::vector<Person> generatePopulation(int size);

double getNorm(Position P);

void updatePopulation();

Position randomPosition();

Position randomDirection();

#endif