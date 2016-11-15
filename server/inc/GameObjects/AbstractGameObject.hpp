#ifndef ABSTRACTGAMEOBJECT_HPP
#define ABSTRACTGAMEOBJECT_HPP

#include <sstream>

class AbstractGameObject
{
public:
    virtual void fromStringStream(std::istringstream *iss) = 0;
    virtual void toStringStream(std::ostringstream *oss) = 0;
}

#endif //ABSTRACTGAMEOBJECT_HPP
