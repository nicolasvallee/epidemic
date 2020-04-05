#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SFML/Graphics.hpp"
#include "Person.hpp"

void takeScreenshot();
//void launch_window();
sf::Color getColor(Person person);
void getDrawing(std::vector<sf::CircleShape> &sketch);
void launchWindow();

#endif

