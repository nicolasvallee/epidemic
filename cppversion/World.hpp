#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Community.hpp"
#include "Position.hpp"

class World
{
    std::vector<Community> m_communities;
    
public:
    World(int nb_communities, int community_size);
    
    int getNumberCommunities() const;

    const std::vector<Community>& getCommunities() const;

    void update();
};

#endif