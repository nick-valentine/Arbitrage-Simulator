#ifndef GAMESTATE_STATE_HPP
#define GAMESTATE_STATE_HPP

#include "Context.hpp"
#include "Services/Logger/Logger.hpp"
#include "Services/Logger/NullLogger.hpp"
#include "Services/WorldInteraction/WorldInteractionInterface.hpp"

namespace GameState
{
    class State
    {
    public:
        virtual void init() = 0;
        virtual void setLogger(Logger::LoggerPtr logger);
        virtual void update(WorldInteractionInterface *worldProxy, Context *ctx) = 0;
        virtual void render(WorldInteractionInterface *worldProxy, Window::window_ptr window) = 0;
        virtual State *nextState() = 0;
        virtual void clearNextState() = 0;
        virtual bool shouldClose() = 0;
        virtual int passDown();
        virtual int passUp();
        virtual void recvDown(int msg);
        virtual void recvUp(int msg);
    protected:
        Logger::LoggerPtr logger;
        int msgDown;
        int msgUp;
        int recvMsgDown;
        int recvMsgUp;
    };
}

#endif //GAMESTATE_STATE_HPP
