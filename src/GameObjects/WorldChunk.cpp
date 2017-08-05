#include "GameObjects/WorldChunk.hpp"

const std::string WorldChunk::CityMarker = "city";
const std::string WorldChunk::MapMarker = "MAP";
    
std::map<std::string, void (*)(WorldChunk *self, std::stringstream *ss)> WorldChunk::factoryMap = 
    {
        {WorldChunk::CityMarker, spawnCity}
    }; 

bool WorldChunk::configured = false;
unsigned int WorldChunk::chunk_height = 0;
unsigned int WorldChunk::chunk_width = 0;

int WorldChunk::maxY = 0;
int WorldChunk::maxX = 0;

WorldChunk::WorldChunk()
{
    if(!WorldChunk::configured) {
        this->configure();
    } 
}

WorldChunk::WorldChunk(unsigned int top, unsigned int left)
{
    if(!WorldChunk::configured) {
        this->configure();
    } 
    this->top = top * WorldChunk::chunk_height;
    this->left = left * WorldChunk::chunk_width;
}

WorldChunk::WorldChunk(std::stringstream *ss)
{
    this->fromStringStream(ss);
    if(!WorldChunk::configured) {
        this->configure();
    } 
}

void WorldChunk::setMaxYX(unsigned int y, unsigned int x)
{
    WorldChunk::maxY = y;
    WorldChunk::maxX = x;
}

void WorldChunk::configure()
{
    WorldChunk::chunk_height = ConfigLoader::getIntOption("chunk_height", 30);
    WorldChunk::chunk_width = ConfigLoader::getIntOption("chunk_width", 30);
    WorldChunk::configured = true;
}

void WorldChunk::fromStringStream(std::stringstream *ss)
{
    READ_STATE readState = object;
    std::vector<Tile> tilesToSpawn;
    std::string nextObject;
    (*ss)>>top>>left;
    while ( 
        ss->good() &&
        tilesToSpawn.size() < WorldChunk::chunk_height * WorldChunk::chunk_width 
    ) {
        if(readState == object) {
            (*ss)>>nextObject;
            if (this->factoryMap.find(nextObject) != this->factoryMap.end()) {
                this->factoryMap[nextObject](this, ss);
            } else if (nextObject == WorldChunk::MapMarker) {
                readState = map;
            }
        } else if(readState == map) {
            tilesToSpawn.push_back(Tile(ss));
        }
    }    
    this->organizeTiles(tilesToSpawn);
}

void WorldChunk::toStringStream(std::stringstream *ss)
{
    (*ss)<<top<<Globals::space_delimiter<<left<<Globals::object_delimiter; 
    for(unsigned int i = 0; i < this->cities.size(); ++i) {
        (*ss)<<WorldChunk::CityMarker<<Globals::space_delimiter;
        this->cities[i].toStringStream(ss);
    }
    (*ss)<<Globals::space_delimiter<<WorldChunk::MapMarker<<Globals::space_delimiter;
    for(unsigned int i = 0; i < this->tiles.size(); ++i) {
        for(unsigned int j = 0; j < this->tiles[i].size(); ++j) {
            this->tiles[i][j].toStringStream(ss); 
            (*ss)<<Globals::space_delimiter;
        }
    }
}

void WorldChunk::generateChunk()
{
    this->cities.clear();
    this->tiles.clear();

    for(unsigned int i = 0; i < WorldChunk::chunk_height; ++i) {
        this->tiles.push_back(std::vector<Tile>());
        for( unsigned int j = 0; j < WorldChunk::chunk_width; ++j) {
            this->tiles[i].push_back(Tile(0, 0)); 
        }
    }

}

void WorldChunk::spawnCity(WorldChunk *self, std::stringstream *ss)
{
    std::string c;
    std::string inv;
    std::getline((*ss), c, Globals::object_delimiter);
    std::getline((*ss), inv, Globals::object_delimiter);
    std::stringstream tss;
    tss.str(c + Globals::object_delimiter + inv);
    self->cities.push_back(City(&tss));
}

void WorldChunk::organizeTiles(std::vector<Tile> tiles)
{
    for(unsigned int i = 0; i < WorldChunk::chunk_height; ++i) {
        this->tiles.push_back(std::vector<Tile>());
        for( unsigned int j = 0; j < WorldChunk::chunk_width; ++j) {
            this->tiles[i].push_back(tiles[(i*WorldChunk::chunk_height) + j]);
        }
    }
}


void WorldChunk::draw(Window::window_ptr window, int playerY, int playerX)
{
    int currX, currY;
    int halfHeight = window->getHeight() / 2;
    int halfWidth = window->getWidth() / 2;
    Tile::setPallete();
    for(unsigned int i = 0; i < WorldChunk::chunk_height; ++i) {
        for(unsigned int j = 0; j < WorldChunk::chunk_width; ++j) {
            this->tiles[i][j].drawAt(
                window, 
                (top + i - playerY) + halfHeight,
                (left + j - playerX) + halfWidth,
                this->doCullTile(playerY, playerX, top + i, left + j, i, j)
            );
        }
    }    
}

City WorldChunk::getCity(int y, int x)
{
    for (int i = 0; i < this->cities.size(); ++i) {
        if (this->cities[i].getPosX() == x && this->cities[i].getPosY() == y) {
            return this->cities[i];
        }
    }
    return City();
}

bool WorldChunk::doCullTile(
    int playerY, 
    int playerX, 
    int tileY, 
    int tileX, 
    int localTileI, 
    int localTileJ
)
{
    int diffY = playerY - tileY; 
    int diffX = playerX - tileX;
    int distance = sqrt((diffY*diffY)+(diffX*diffX));
    if(distance < WorldChunk::maxViewDistance) {
        return false;
    } else {
    //    return true;
        return true;
    }
}

//@todo: implement elevation based culling
//bool WorldChunk::doCullTile(
//    int playerY, 
//    int playerX, 
//    int tileY, 
//    int tileX, 
//    int localTileI, 
//    int localTileJ
//)
//{
//    int diffY = playerY - tileY; 
//    int diffX = playerX - tileX;
//    int distance = sqrt((diffY*diffY)+(diffX*diffX));
//    if(distance < WorldChunk::maxViewDistance) {
//        if(distance == 0) {
//            //the immediate tile is always visible
//            return false;
//        }
//        int vecY = diffY / distance;
//        int vecX = diffX / distance;
//        if(vecY == 0) {
//            vecY = (diffY < 0) ? -1 : (diffY > 0) ? 1 : 0;
//        }
//        if(vecX == 0) {
//            vecX = (diffX < 0) ? -1 : (diffX > 0) ? 1 : 0;
//        }
//
//        //shoot a vector player to tile and if the elevation
//        //ever goes up, then goes down, the player can not see past it.
//        bool tileReached = false;
//        int tracerY = playerY;
//        int tracerX = playerX;
//
//        bool elevationHasGoneUp = false;
//        int elevation = 0;
//        int lastElevation = 0;
//        while(!tileReached) {
//            if(localTileI + tracerY < 0 || localTileI + tracerY > chunk_height ||
//                localTileJ + tracerX < 0 || localTileJ + tracerX > chunk_width) {
//                return true;
//            } 
//            elevation = this->tiles[localTileI + tracerY][localTileJ + tracerX].getElevation();
//
//            if(elevation > lastElevation) {
//                elevationHasGoneUp = true;
//                return true;
//            }
//            if(elevation < lastElevation && elevationHasGoneUp) {
//                //elevation has gone up and is now going down
//                return true;
//            }
//            lastElevation = elevation;
//
//
//            tracerY -= vecY;
//            tracerX -= vecX; 
//            if((playerY <= tileY && tracerY >= tileY) ||
//                (playerY >= tileY && tracerY <= tileY)) {
//                if((playerX <= tileX && tracerX >= tileX) ||
//                    (playerX >= tileX && tracerX <= tileX)) {
//
//                    tileReached = true;
//                }
//            }
//        }
//        return false;
//    } else {
//        return true;
//    }
//}

unsigned int WorldChunk::getChunkWidth()
{
    return WorldChunk::chunk_width;
}

unsigned int WorldChunk::getChunkHeight()
{
    return WorldChunk::chunk_height;
}

