#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Community.hpp"

class World
{
    std::vector<Community> m_communities;

public:
    World(int nb_communities, int community_size);
    
    const std::vector<Community>& getCommunities() const;

    void update();
};

#endif