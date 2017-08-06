#include "EventNotifier.hpp"

void Notifier::addListener(std::string name, Listener *l)
{
    if (this->listeners.find(name) == this->listeners.end()) {
        this->listeners[name] = std::vector<Listener*>();
    }
    this->listeners[name].push_back(l);
}

void Notifier::notify(std::string name, int value)
{
    auto it = this->listeners.find(name);
    if (it != this->listeners.end()) {
        for (unsigned int i = 0; i < (*it).second.size(); ++i) {
            (*it).second[i]->act(value);
        }
    }
}
