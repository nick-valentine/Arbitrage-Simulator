#ifndef TILE_HPP
#define TILE_HPP

class Tile : public AbstractGameObject
{
public:
    Tile();
    Tile(std::istringstream *iss);
    void fromStringStream(std::istringstream *iss);
    void toStringStream(std::ostringstream *oss);


private:
    // @todo: add colors etc.
    typedef struct TileType
    {
        char tile;

        TypeType(char tile) : tile(tile) {}
    };

    static const TileType[4] = 
    {
        {'.'}, //plains
        {'M'}, //mountains
        {'O'}, //water
        {'s'} //swamps
    }

    int myType;
};

#endif //TILE_HPP
