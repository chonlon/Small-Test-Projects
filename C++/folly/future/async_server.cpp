#include <folly/executors/ThreadedExecutor.h>
#include <folly/futures/Future.h>

#include <asio/ip/address.hpp>
#include <asio.hpp>
#include <iostream>

using asio::ip::tcp;
using std::string;
using std::cout;
using std::endl;

string read(tcp::socket& socket) {
    asio::streambuf buf;
    asio::read_until(socket, buf, "\n");
    string data = asio::buffer_cast<const char*>(
    buf.data());
    return data;
}

void send(tcp::socket&  socket,
          const string& message) {
    const string msg = message + "\n";
    asio::write(socket, asio::buffer(message));
}

int main() {
    asio::io_service io_service;
    //listen for new connection
    tcp::acceptor acceptor(io_service,
                           tcp::endpoint(
                           tcp::v4(),
                           1234));
    //socket creation 
    tcp::socket socket(io_service);
    //waiting for connection
    acceptor.accept(socket);
    //read operation
    string message = read(socket);

    cout << message << endl;
    //write operation
    send(socket, "Hello From Server!");
    cout <<
        "Servent sent Hello message to Client!" <<
        endl;
    return 0;
}
