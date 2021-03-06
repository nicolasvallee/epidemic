#include <iostream>
#include "World.hpp"
#include "Graphics.hpp"
#include "Utils.hpp"
#include "Constants.hpp"
#include "Person.hpp"
#include "Community.hpp"


void takeScreenshot(World &world)
{
    std::cout << "in graphics " << MAP_HEIGHT << '\n';
    sf::RenderTexture screen;
    screen.create(MAP_WIDTH, MAP_HEIGHT);
    screen.clear(sf::Color::White);

    std::vector<sf::CircleShape> circles = getDrawing(world);
    for(sf::CircleShape circle : circles)
        screen.draw(circle);
    screen.display();

    sf::Texture boudi = screen.getTexture();

    sf::Image screenshot = boudi.copyToImage();
    //std::string name = get_file_name();
    screenshot.saveToFile("TEST.png");
}

sf::Color getColor(Person person)
{
    sf::Color color{sf::Color::Blue};
    Health state = person.getHealthState();
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

std::vector<sf::CircleShape> getDrawing(World &world)
{
    std::vector<sf::CircleShape> sketch;
    const std::vector<Community>& communities = world.getCommunities();
    for(const Community &community : communities)
    {
        const std::vector<Person>& people = community.getPeopleConst();
        for(const Person &person : people)
        {
            Position pos = person.getPosition();
            int duration = person.getInfectionDuration();
            bool newly_infected = (person.getHealthState() == INFECTIOUS 
                                && duration >= 1 && duration <= 20);
            if(newly_infected)
            {
                sf::CircleShape alert_circle;
                alert_circle.setRadius(7);
                alert_circle.setOutlineThickness(3);
                alert_circle.setPosition({(float)pos.x-3, (float)pos.y-3});
                alert_circle.setOutlineColor(sf::Color::Red);
                sketch.push_back(alert_circle);
            }

            sf::Color color = getColor(person);
            sf::CircleShape circle;
            circle.setFillColor(color);
            circle.setRadius(4);
            circle.setPosition({(float)pos.x,(float)pos.y});
            sketch.push_back(circle);
        }
    }
    return sketch;
}

void launchWindow()
{

    World world(NB_COMMUNITIES, INIT_COMMUNITY_SIZE);
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH, MAP_HEIGHT), "M");
    //window.setVerticalSyncEnabled(true);    
    window.setFramerateLimit(60);
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
                    takeScreenshot(world);
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

        world.update();
        window.clear(sf::Color::White);
        std::vector<sf::CircleShape> circles = getDrawing(world);
        for(sf::CircleShape circle : circles)
            window.draw(circle);

        window.display();
    }
    window.close();
}