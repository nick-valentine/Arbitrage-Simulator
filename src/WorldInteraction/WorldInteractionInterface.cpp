#include "WorldInteraction/WorldInteractionInterface.hpp"

initNetworked(Connection::ConnectionPtr c)
{
    this->c = c;
    this->networked = true;
}
