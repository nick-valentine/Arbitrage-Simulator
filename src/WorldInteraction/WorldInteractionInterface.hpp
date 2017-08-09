#ifndef WORLD_INTERACTION_INTERFACE
#define WORLD_INTERACTION_INTERFACE

#include "GameObjects/World.hpp"
#include "Networking/Connection.hpp"

namespace WorldInteraction
{
    class Interface
    {
    public:
        Interface();
        ~Interface();
        virtual void initLocal() = 0;
        virtual void initNetworked(Connection::ConectionPtr c);
    protected:
        Connection::ConectionPtr c;
        bool networked;
    };
}

#endif //WORLD_INTERACTION_INTERFACE
