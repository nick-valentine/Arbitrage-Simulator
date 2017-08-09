#ifndef WORLD_INTERACTION_MOVE_PLAYER_HPP
#define WORLD_INTERACTION_MOVE_PLAYER_HPP

#include "WorldInteractionInterface/WorldInteractionInterface.hpp"

namespace WorldInteraction
{
    class MovePlayer : public Interface
    {
    public:
        void initLocal();
        void initNetworked(Connection::ConnectionPtr c);
        void go(World *world, int who, int y, int x);
    private:
        void goLocal(World *world, int who, int y, int x);
        void goNetworked(World *world, int who, int y, int x);
    };
}

#endif //WORLD_INTERACTION_MOVE_PLAYER_HPP
