#include <vector>
#include "World.hpp"
#include <iostream>
class Community;

World::World(int nb_communities, int community_size)
{
    int square = 0;
    while(square * square < nb_communities)
        square++;
    int n_columns = square-1;
    int n_lines = square-1;
    if(n_columns * n_lines  < nb_communities)
    {
        n_columns++;
    }
    if(n_columns * n_lines < nb_communities)
            n_lines++;
    int width = MAP_WIDTH / n_columns;
    int height = MAP_HEIGHT / n_lines;
    std::vector<Position> community_bounds[2];

    for(int l = 0; l < n_lines; l++)
    {     
        if(l * n_columns  >= nb_communities)
            break;
        for(int c = 0; c < n_columns; c++)
        {   
            if(l * n_columns + c >= nb_communities)
                break;
            //upper left 
            community_bounds[0].push_back(Position{width * c, height * l}); 
            //lower right
            community_bounds[1].push_back(Position{width * (c+1) - 0,
                                                   height * (l+1) - 0});
        }
    }
    // This is to avoid REALLOCATIONS, that would change the address 
    // of communities !!! 
    // I could also use lists, they apparently don't reallocate elements
    m_communities.reserve(nb_communities);

    for(int i = 0; i < nb_communities; i++)
    {
        Community new_community{community_size, community_bounds[0][i], 
                                                community_bounds[1][i]};
        m_communities.push_back(new_community);
        m_communities[i].initializePeopleCommunities();
    }
}

int World::getNumberCommunities() const { return m_communities.size();}

const std::vector<Community>& World::getCommunities() const
{
    return m_communities;
}

void World::update()
{
    for(int i = 0; i < getNumberCommunities(); i++)
    {
        m_communities[i].update();
    }
}