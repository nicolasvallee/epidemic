#include <iostream>
#include "Graphics.hpp"
#include "Utils.hpp"
#include "Constants.hpp"
#include "Person.hpp"


void take_screenshot()
{
    std::cout << "in graphics " << MAP_HEIGHT << '\n';
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
    sf::Color color{sf::Color::Blue};
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

void launch_window()
{

    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH, MAP_HEIGHT), "M");
    bool is_dragging = false;
    //Position old_pos;
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::F10)
                    take_screenshot();
            }
            else if(event.type == sf::Event::MouseWheelScrolled)
            {
                //pixels_per_unit *= pow(2,event.mouseWheelScroll.delta);
                //K_MAX *= pow(1.5,event.mouseWheelScroll.delta);
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
              //  is_dragging = true;
               // old_pos = {event.mouseButton.x, event.mouseButton.y};
            }
            else if(event.type == sf::Event::MouseButtonReleased)
                 is_dragging = false;
            else if(event.type == sf::Event::MouseMoved && is_dragging)
            {
             //   real_origin.x += (old_pos.x - event.mouseMove.x) / pixels_per_unit;
              //  real_origin.y += (event.mouseMove.y - old_pos.y) / pixels_per_unit;
            //    old_pos.x = event.mouseMove.x;
            //    old_pos.y = event.mouseMove.y;

            }
            else if (event.type == sf::Event::Closed)
                window.close();
        }

        update_population();
        window.clear(sf::Color::White);
        std::vector<sf::CircleShape> circles;
        draw(circles);
        for(sf::CircleShape circle : circles)
            window.draw(circle);

        window.display();
    }
    window.close();
}