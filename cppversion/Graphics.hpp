#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SFML/Graphics.hpp"
#include "Person.hpp"
#include "World.hpp"

void takeScreenshot(World &world);
//void launch_window();
sf::Color getColor(Person person);

std::vector<sf::CircleShape> getDrawing(World &world);

void launchWindow();

#endif

