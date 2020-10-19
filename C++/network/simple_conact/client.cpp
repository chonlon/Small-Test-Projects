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
    try {
        io_service service;
        //ip::tcp::acceptor acceptor(service, tcp)
        tcp::endpoint endpoint(ip::address::from_string(address.host_name), address.port);
        std::shared_ptr<tcp::socket> socket = std::shared_ptr<tcp::socket>(new tcp::socket(service));
        //socket.connect(endpoint);
        socket->async_connect(endpoint,
            [address, socket, &service](const boost::system::error_code& error) mutable {
                if (error) { return; }
                std::cout << "connect to server " << address.host_name << " : " << address.port << " successed!\n";
                //socket->async_send
                constexpr int write_buf_size = 100;
                char write_buf[write_buf_size]{ 'l', 'o', 'v', 'e' };
                for (int i = 4; i < write_buf_size; ++i) {
                    write_buf[i] = '+';
                }
                char read_buf[100]{ 0 };
                int i = 0;
                socket->async_read_some(buffer(read_buf, 100),
                    [&](const boost::system::error_code& error, std::size_t len) mutable {
                        // if (!error) {
                        
                        if (*read_buf == EOF) {
                            service.stop();
                        };
                        std::cout << read_buf;
                        // } else {
                        //     std::cout << error.message();
                        //     return;
                        // }
                    }
                );
                for (;i < 12;) {
                    ++i;
                    std::cout << "mark zero\n";
                    boost::asio::async_write(*socket, buffer(write_buf,write_buf_size),
                        [socket, read_buf](const boost::system::error_code& error, std::size_t len) mutable {
                            printf("send completed");
                            std::cout << "send completed.\n";
                        });
                    // socket->async_write_some(buffer(write_buf),
                    // );
                    std::cout << "mark one " << i << '\n';

                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }
        );
        service.run();
        std::cout << "end\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
}

int main(int argc, char** argv) {
    Address address{};
    parseCommandLine(argc, argv, address);

    connectAndSendUtilStop(address);
    return 0;
}