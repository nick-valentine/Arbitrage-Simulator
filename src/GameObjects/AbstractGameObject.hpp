#ifndef ABSTRACTGAMEOBJECT_HPP
#define ABSTRACTGAMEOBJECT_HPP

#include <sstream>

/**
 * The Abstract Game Object.
 * A root interface for all game objects to follow. It includes the to and from
 * stringstream functions in order to allow for replication to and from both
 * network and the filesystem. Each game object should be responsible for this
 * replication of both itself and all children it has.
 */
class AbstractGameObject
{
public:

    /**
     * From String Stream.
     * Assume this object is the next object in the stringstream and restore
     * it's own state based on the stringstream's contents.
     *
     * @param  std::stringstream *ss
     */
    virtual void fromStringStream(std::stringstream *ss) = 0;

    /**
     * To String Stream.
     * Add this object's state into the stringstream at the current point in
     * the stream.
     *
     * @param  std::stringstream *ss
     */
    virtual void toStringStream(std::stringstream *ss) = 0;
};

#endif //ABSTRACTGAMEOBJECT_HPP
