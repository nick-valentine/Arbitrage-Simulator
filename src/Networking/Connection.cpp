#include "Networking/Connection.hpp"

Connection::Connection()
{
    this->connected = false;
}

Connection::Connection(Connection &other)
{
    this->socket = other.socket;
    this->connected = other.connected;
}

Connection &Connection::operator=(Connection &other)
{
    this->socket = other.socket;
    this->connected = other.connected;
    return *this;
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

bool Connection::connect(std::string ip, std::string port)
{
    if (this->connected) {
        this->socket.reset();
    }
    boost::asio::io_service io_service;
    try {
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(ip.c_str(), port.c_str());
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        this->socket.reset(new tcp::socket(io_service));
        boost::asio::connect(*this->socket, endpoint_iterator);
    } catch (boost::system::system_error& e) {
        return false;
    }
    this->connected = true;
    return true;
}

void Connection::bind(socket_ptr sock)
{
    this->socket.swap(sock);
    this->connected = true;
}

std::string Connection::read()
{
    if (this->connected) {
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

bool Connection::poll()
{
    try {
        boost::asio::socket_base::bytes_readable command(true);
        this->socket->io_control(command);
        std::size_t bytes_readable = command.get(); 
        return bytes_readable != 0;
    } catch (boost::system::system_error& e) {
        return false;
    }
}

bool Connection::write(std::string msg)
{
    if (this->connected) {
        boost::system::error_code ignored_error;
        boost::asio::write(
            *this->socket, 
            boost::asio::buffer(msg), 
            ignored_error
        );
        if (ignored_error) {
            return false;
        }
        return true;
    }
    return false;
}

std::string Connection::writeRead(std::string msg)
{
    std::string r = "";
    {
        std::lock_guard<std::mutex> lock(this->writeReadGuard);
        if (!this->write(msg)) {
            return r;
        }
        r = this->read();
    }
    return r;
}

void Connection::close()
{
    if (this->connected) {
        boost::system::error_code ignored_error;
        this->socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_error);
        this->socket->close();
        this->connected = false;
    }
}

Connection::socket_ptr Connection::get()
{
    return this->socket;
}

bool Connection::isConnected()
{
    return this->connected;
}
