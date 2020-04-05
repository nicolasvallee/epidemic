#include <iostream>
#include <cstdlib>
#include <vector>
#include "Constants.hpp"
#include "Person.hpp"
#include "Utils.hpp"
#include "Graphics.hpp"
#include <ctime>


std::vector<Person> population;

int main()
{
    srand(time(0));
    
    std::cout << MAP_HEIGHT << '\n';
    population = generatePopulation(INIT_POPULATION_SIZE);
    //std::vector<std::vector<Person>> data;

    //data.push_back(population);

   // for(int i = 0; i < NB_CYLES; i++)
 //   {
  //      update_population();
 //       data.push_back(population);
  //  }
    takeScreenshot();
    launchWindow();
    return 0;
}

