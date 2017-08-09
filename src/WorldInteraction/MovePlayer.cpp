#include "WorldInteraction/MovePlayer.hpp"

void WorldInteraction::MovePlayer::initLocal()
{

}

void WorldInteraction::MovePlayer::initNetworked(Connection::ConnectionPtr c)
{
    WorldInteractionInterface::initNetworked(c);
}

void go(World *world, int who, int y, int x)
{
    if (this->networked) {
        this->goNetworked(world, who, y, x);
        return;
    } 
    this->goLocal(world, who, y, x);
    return;
}

void goLocal(World *world, int who, int y, int x)
{

}

void goNetworked(World *world, int who, int y, int x)
{

}
