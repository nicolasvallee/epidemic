#include <iostream>
#include "Graphics.hpp"
#include "Constants.hpp"
#include "Person.hpp"


void take_screenshot()
{
    sf::RenderTexture screen;
    screen.create(MAP_WIDTH, MAP_HEIGHT);
    screen.clear(sf::Color::White);

    std::vector<sf::CircleShape> circles;
    draw(circles);
    for(sf::CircleShape circle : circles)
        screen.draw(circle);
    screen.display();

    sf::Texture boudi = screen.getTexture();

    sf::Image screenshot = boudi.copyToImage();
    //std::string name = get_file_name();
    screenshot.saveToFile("TEST.png");
}

sf::Color get_color(Person person)
{
    sf::Color color;
    Health state = person.get_health_state();
    if(state == SUSCEPTIBLE)
        color = sf::Color::Black;
    else if(state == INFECTIOUS)
        color = sf::Color::Red;
    else if(state == RECOVERED)
        color = sf::Color::Green;
    else if(state == DEAD)
        color = sf::Color::Yellow;
    return color;
}

void draw(std::vector<sf::CircleShape> &sketch)
{
    int size = population.size();
    for(int i = 0; i < size; i++)
    {
        Person person = population[i];
        Position pos = person.get_position();
        sf::Color color = get_color(person);
        sf::CircleShape circle;
        circle.setFillColor(color);
        circle.setRadius(3);
        circle.setPosition({pos.x,pos.y});
        sketch.push_back(circle);
    }
}