//
// Created by lon on 2020/11/29.
//
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <mutex>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 3)
        std::cerr << "usage: client [address] [port]\n";
    char* address              = argv[1];
    int port                   = std::atoi(argv[2]);
    constexpr int thread_count = 5;


    std::mutex mutex;
    auto connectFunc = [port, address, &mutex](std::string thread_name) {
        int connfd = -1;
        struct sockaddr_in serv_addr;

        if ((connfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            std::cerr << "error, create socket failed\n";
        }


        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port   = htons(port);
        inet_pton(AF_INET,
                  address,
                  &serv_addr.sin_addr);  // address from text to binary form

        if ((connect(connfd,
                     reinterpret_cast<::sockaddr*>(&serv_addr),
                     sizeof(sockaddr))) == -1) {
            std::cerr << "connect failed\n";
        }

        std::string send_str = "hello from " + thread_name;

        auto sendMessage = [connfd, &send_str, &mutex]() {
            int n = 0;
            char recv_buf[1024];
            while (true) {
                // if(fgets)
                n = write(connfd, send_str.c_str(), send_str.size());
                if (n > 0) {
                    std::lock_guard<std::mutex> lock_guard(mutex);
                    std::cout << "write " << n << " byte; "
                              << "sent: " << send_str << '\n';
                }
                n = read(connfd, recv_buf, sizeof(recv_buf));
                if (n == 0) {
                    std::lock_guard<std::mutex> lock_guard(mutex);
                    std::cout << "terminated\n";
                    break;
                }
                if (recv_buf[0] == '\0') {
                    std::lock_guard<std::mutex> lock_guard(mutex);
                    std::cout << "recv eof, terminated\n";
                    break;
                }
                recv_buf[n] = '\0';
                {
                    std::lock_guard<std::mutex> lock_guard(mutex);
                    std::cout << recv_buf << '\n';
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        };
        sendMessage();

        close(connfd);
    };

    std::array<std::thread, thread_count> threads;
    for (int i = 0; i < thread_count; ++i) {
        threads[i] = std::thread(connectFunc, "thread" + std::to_string(i));
    }

    for (int i = 0; i < thread_count; ++i) {
        threads[i].join();
    }

    // std::cout << address << ':' << port;
    return 0;
}