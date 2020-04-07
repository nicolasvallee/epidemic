#include <vector>
#include "World.hpp"

class Community;

World::World(int nb_communities, int community_size)
{
    for(int i = 0; i < nb_communities; i++)
    {
        m_communities.push_back(Community(community_size));
    }
}

const std::vector<Community>& World::getCommunities() const
{
    return m_communities;
}

void World::update()
{
    for(Community &community : m_communities)
        community.update();
}