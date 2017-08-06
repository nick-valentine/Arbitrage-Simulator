#ifndef EVENTNOTIFIER_HPP
#define EVENTNOTIFIER_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>

class Listener
{
public:
    virtual void act(int i){std::cout<<i<<" Notified";};
};

class Notifier
{
public:
    void notify(std::string name, int value);
    void addListener(std::string name, Listener *l);
private:
    std::map< std::string, std::vector<Listener*> > listeners;
};


#endif //EVENTNOTIFIER_HPP
