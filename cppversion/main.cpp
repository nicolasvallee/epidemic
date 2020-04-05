#include <iostream>
#include <vector>
#include "Constants.hpp"
#include "Person.hpp"
#include "Utils.hpp"
#include "Graphics.hpp"



int main()
{
    population = generate_population(10);
    std::cout << MAP_HEIGHT << '\n';
    //std::vector<std::vector<Person>> data;

    //data.push_back(population);

   // for(int i = 0; i < NB_CYLES; i++)
 //   {
  //      update_population();
 //       data.push_back(population);
  //  }
    take_screenshot();

    return 0;
}

