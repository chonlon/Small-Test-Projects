#include <boost/asio.hpp>
#include <boost/program_options.hpp>

#include <iostream>
#include <string>
#include <memory>


struct Address {
    uint16_t port;
    std::string host_name;
};

void parseCommandLine(int argc, char** argv, Address& address) {
    namespace po = boost::program_options;
    po::options_description desc("client options");
    desc.add_options()
        ("help,h", "Help")
        ("port,p", po::value<u_int16_t>(&address.port)->default_value(22222), "server port")
        ("hostaddress,a", po::value<std::string>(&address.host_name), "server address");

    po::variables_map vmap;
    po::store(po::parse_command_line(argc, argv, desc), vmap);
    po::notify(vmap);

    if (vmap.count("help")) {
        std::cout << desc << std::endl;
    }
}

void connectAndSendUtilStop(const Address& address) {
    using namespace boost::asio;
    using boost::asio::ip::tcp;
    try{
        io_service service;
        //ip::tcp::acceptor acceptor(service, tcp)
        tcp::endpoint endpoint(ip::address::from_string(address.host_name), address.port);
        std::shared_ptr<tcp::socket> socket = std::shared_ptr<tcp::socket>(new tcp::socket(service));
        //socket.connect(endpoint);
        socket->async_connect(endpoint,
            [address, socket](const boost::system::error_code& error) {
                if (error) { return; }
                std::cout << "connect to server " << address.host_name << ":" << address.port << "successed!\n";
                //socket->async_send
                for (;;) {
                    socket->async_write_some(buffer("some text\n"),
                        [](const boost::system::error_code& error, size_t len) {
                            if (!error) {
                                std::cout << "send completed.\n";
                            }
                        }
                    );
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
        );
        service.run();
    } catch (std::exception& e) {
        std::cout << e.what();
    }
}

int main(int argc, char** argv) {
    Address address{};
    parseCommandLine(argc, argv, address);

    connectAndSendUtilStop(address);
    return 0;
}