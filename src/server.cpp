#include "Managers/Server.hpp"

int main()
{
    Server myServer;
    myServer.setup();
    myServer.run();

    return 0;
}
