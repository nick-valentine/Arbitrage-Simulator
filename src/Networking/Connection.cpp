#include "Networking/Connection.hpp"

Connection::Connection()
{
    this->connected = false;
}

Connection::Connection(std::string ip, std::string port)
{
    this->connect(ip, port);
}

Connection::Connection(socket_ptr sock)
{
    this->socket = sock;
    this->connected = true;
}

void Connection::connect(std::string ip, std::string port)
{
        if (connected) {
            delete &this->socket;
        }
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(ip.c_str(), port.c_str());
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        this->socket.reset(new tcp::socket(io_service));
        boost::asio::connect(*this->socket, endpoint_iterator);
}

std::string Connection::read()
{
    if (connected) {
        boost::system::error_code error;
        boost::asio::streambuf sb;
        std::size_t len = boost::asio::read_until(
            *this->socket, 
            sb, 
            "\n",
            error
        );
        std::string buff;
        buff.resize(len);
        sb.sgetn(&buff[0], buff.size());

        if (error) {
            throw boost::system::system_error(error);
        }

        return buff;
    } else {
        return "";
    }
}

bool Connection::write(std::string msg)
{
    if (connected) {
        boost::system::error_code ignored_error;
        boost::asio::write(
            *this->socket, 
            boost::asio::buffer(msg), 
            ignored_error
        );
    }
}
