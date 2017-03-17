#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <sstream>
#include <stdio.h>

using boost::asio::ip::tcp;

class Connection
{
public:
    typedef boost::shared_ptr<tcp::socket> socket_ptr;
    Connection();
    Connection(std::string ip, std::string port);
    Connection(socket_ptr sock);
    
    void connect(std::string ip, std::string port);
    void bind(socket_ptr sock);

    std::string read();
    bool write(std::string msg);

    socket_ptr get();
    bool isConnected();
private:
    bool connected;
    socket_ptr socket;
};

#endif //CONNECTION_HPP
