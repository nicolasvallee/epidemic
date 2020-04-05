#include <iostream>
#include <vector>
#include "Constants.hpp"
#include "Person.hpp"
#include "Utils.hpp"
#include "Graphics.hpp"


std::vector<Person> population;

int main()
{
    
    std::cout << MAP_HEIGHT << '\n';
    population = generate_population(INIT_POPULATION_SIZE);
    //std::vector<std::vector<Person>> data;

    //data.push_back(population);

   // for(int i = 0; i < NB_CYLES; i++)
 //   {
  //      update_population();
 //       data.push_back(population);
  //  }
    take_screenshot();
    launch_window();
    return 0;
}

