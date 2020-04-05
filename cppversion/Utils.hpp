//This is for my general useful functions
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "Position.hpp"
#include "Person.hpp"

std::vector<double> matrix_vector_product(std::vector<double> *matrix, Position vect);

Position rotate_vector(Position vect, double angle); //trigonometric direction

std::vector<Person> generate_population(int size);

double get_norm(Position P);

void update_population();

Position random_position();

Position random_direction();

#endif