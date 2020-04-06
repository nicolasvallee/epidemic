#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SFML/Graphics.hpp"
#include "Person.hpp"
#include "Population.hpp"

void takeScreenshot(Population &population);
//void launch_window();
sf::Color getColor(Person person);
std::vector<sf::CircleShape> getDrawing(Population &population);
void launchWindow();

#endif

