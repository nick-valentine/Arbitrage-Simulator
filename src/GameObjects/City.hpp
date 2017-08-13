#ifndef CITY_HPP
#define CITY_HPP

#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include "Globals.hpp"
#include "GameObjects/AbstractGameObject.hpp"
#include "GameObjects/Inventory.hpp"

/**
 * City Game Object.
 * The city game object is for managing trading hubs. Each city exists at a
 * point in the world and owns and maintains the information necessary to
 * facilitate a local economy.
 */
class City : public AbstractGameObject
{
public:
    City();
    City(const City &other);
    City(std::stringstream *ss);
    City(std::string name, int pos_x, int pos_y);
    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

    void setName(std::string name);
    const std::string& getName() const;

    void setPosX(int x);
    int getPosX() const;

    void setPosY(int y);
    int getPosY() const;

    Inventory *getInventory();

    /**
     * Load City Names.
     * City names will exist within a file at city_name_file_path. Load this
     * from the disk so that users can generate their own set of possible
     * names.
     */
    static void load_city_names();
    static std::vector<std::string> city_name_starts;
    static std::vector<std::string> city_name_ends;
private:
    static const std::string city_name_file_path; /**< std::string city_name_file_path 
                                                    the place on disk to find a
                                                    file full of city name
                                                    starts and ends. */

    std::string name;
    int pos_x;
    int pos_y;

    Inventory inv;
};

#endif //CITY_HPP
