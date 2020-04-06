//This is for my general useful functions
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "Position.hpp"
#include "Person.hpp"



std::vector<Person> generatePopulation(int size);

void updatePopulation();

std::vector<double> matrixVectorProduct(std::vector<double> *matrix, Position vect);

Position rotateVector(Position vect, double angle); //trigonometric direction

double getNorm(Position P);

float randomUniform();

Position randomPosition();

Position randomDirection();

#endif