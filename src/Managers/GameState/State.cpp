#include "Managers/GameState/State.hpp"

void State::setLogger(Logger::LoggerPtr logger)
{
    this->logger = logger;
}

int State::passDown() {
    return this->msgDown;
}

int State::passUp() {
    return this->msgUp;
}

void State::recvDown(int msg) {
    this->recvMsgDown = msg;
}

void State::recvUp(int msg) {
    this->recvMsgUp = msg;
}
