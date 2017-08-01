#include "Managers/GameState/State.hpp"

void GameState::State::setLogger(Logger::LoggerPtr logger)
{
    this->logger = logger;
}

int GameState::State::passDown() {
    return this->msgDown;
}

int GameState::State::passUp() {
    return this->msgUp;
}

void GameState::State::recvDown(int msg) {
    this->recvMsgDown = msg;
}

void GameState::State::recvUp(int msg) {
    this->recvMsgUp = msg;
}
