#ifndef ABSTRACTGAMEOBJECT_HPP
#define ABSTRACTGAMEOBJECT_HPP

#include <sstream>

class AbstractGameObject
{
public:
    virtual void fromStringStream(std::stringstream *ss) = 0;
    virtual void toStringStream(std::stringstream *ss) = 0;
};
#endif //ABSTRACTGAMEOBJECT_HPP
