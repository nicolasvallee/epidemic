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

double getNorm(Position vector)
{
    return(sqrt(pow((vector.x),2) + pow((vector.y),2)));
}

float randomUniform()
{
    return rand() / (RAND_MAX + 1.0);
}

Position randomPosition(Position upper_left_bound, Position lower_left_bound)
{   
    int width = (lower_left_bound - upper_left_bound).x;
    int height = (lower_left_bound - upper_left_bound).y;
    Position randPos = Position{(double)(rand() % width),
                                 (double)(rand() % height)};
                                 
    return upper_left_bound + randPos;    
}

Position randomDirection()
{   
    return Position{(double)(rand() % 20 - 10),
                    (double)(rand() % 20 - 10)};
}