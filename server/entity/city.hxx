#include <string>
#include <odb/core.hxx>

#pragma db object
class City
{
    public:
        City(std::string name, std::string description, int pos_x, int pos_y);

        const std::string& name() const;
        const std::string& description() const;
        const int pos_x() const;
        const int pos_y() const;

    private:
        City() {}

        friend class odb::access;

        #pragma db id auto
        unsigned long id_;

        std::string name_;
        std::string description_;
        int pos_x_;
        int pos_y_;
};
