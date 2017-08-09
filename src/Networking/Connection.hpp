#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <sstream>
#include <stdio.h>
#include <mutex>

using boost::asio::ip::tcp;

/**
 * Connection.
 * Wrapper for boost sockets to make reading and writing easier.
 * @todo: make the error handling more uniform
 */
class Connection
{
public:
    typedef boost::shared_ptr<Connection> ConnectionPtr;
    typedef boost::shared_ptr<tcp::socket> socket_ptr;
    Connection();
    Connection(Connection &other);
    Connection &operator=(Connection &other);

    Connection(std::string ip, std::string port);
    Connection(socket_ptr sock);
    
    bool connect(std::string ip, std::string port);

    /**
     * If a connection was already made, bind this Connection class to it.
     *
     * @param  socket_ptr sock
     */
    void bind(socket_ptr sock);

    /**
     * Blocking read on this socket.
     *
     * @return  std::string
     */
    std::string read();

    /**
     * Poll to see if data is ready to be read
     *
     * @return bool
     */
    bool poll();

    /**
     * Write msg to this socket.
     *
     * @param  std::string msg
     * @return bool success
     */
    bool write(std::string msg);

    /**
     * Write and then read in a mutexed single transaction
     *
     * @param  std::string msg
     * @return std::string response
     */
    std::string writeRead(std::string msg);

    void close();

    socket_ptr get();
    bool isConnected();
private:
    bool connected;
    socket_ptr socket;
    std::mutex writeReadGuard;
    std::mutex writeGuard;
    std::mutex readGuard;
};

#endif //CONNECTION_HPP
