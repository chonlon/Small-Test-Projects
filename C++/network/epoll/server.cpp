//
// Created by lon on 2020/11/29.
//


#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 2)
        std::cerr << "usage: server [port]\n";
    int port                   = std::atoi(argv[1]);
    int listen_fd = -1;


    struct sockaddr_in serv_addr{}, client_addr{};
    struct epoll_event ep_event;
    struct epoll_event ep_events[1000];
    int ep_fd = epoll_create(5000);

    size_t socklen = sizeof(struct sockaddr_in);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = ::htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd == -1) std::cerr << "cannot create socket\n";
    if (fcntl(listen_fd, F_SETFL, O_NONBLOCK) == -1) {
        std::cerr << "fcntl failed\n";
    }

    ep_event.data.fd = listen_fd;
    ep_event.events = EPOLLIN;
    epoll_ctl(ep_fd, EPOLL_CTL_ADD, listen_fd, &ep_event);


    bind(listen_fd, reinterpret_cast<sockaddr*>(&serv_addr), socklen);
    listen(listen_fd, 500);

    int conn_fd = -1;
    int client_fd = -1;
    socklen_t client_len = 0;
    char buf[1024]{};
    while (true) {
        int nfds = epoll_wait(ep_fd, ep_events, 1000, -1);
        for(int i = 0; i < nfds; ++i) {
            if(ep_events[i].data.fd == listen_fd) {
                while((conn_fd = accept(listen_fd, reinterpret_cast<sockaddr*>(&client_addr), &client_len)) > 0) {
                    ::fcntl(conn_fd, F_SETFL, O_NONBLOCK);
                    char *str = inet_ntoa(client_addr.sin_addr);
                    std::cout << "connect from " << str;
                    ep_event.data.fd = conn_fd;
                    ep_event.events = EPOLLIN;// | EPOLLOUT;
                    epoll_ctl(ep_fd, EPOLL_CTL_ADD, conn_fd, &ep_event);
                }
            } else if(ep_events[i].events & EPOLLIN) {
                if((client_fd = ep_events[i].data.fd) < 0)
                    continue;

                int len_read = 0;
                int n = 0;
                while((len_read = read(client_fd, buf + n, sizeof(buf))) > 0) {
                    n += len_read;
                }

                if(len_read == -1 && errno != EAGAIN) {
                    std::cerr << "error read :" << strerror(errno) << '\n';
                    close(client_fd);
                    ep_events[i].data.fd = -1;
                }

                if(len_read == 0) {
                    std::cout << "recv 0 bytes, close socket" << client_fd  << '\n';
                    continue;
                } else {
                    std::cout << "recv: " << buf << '\n';
                }

                ep_event.data.fd = client_fd;
                ep_event.events = EPOLLOUT;
                epoll_ctl(ep_fd, EPOLL_CTL_MOD, client_fd, &ep_event);
            } else if(ep_events[i].events & EPOLLOUT) {
                client_fd = ep_events[i].data.fd;
                const char* send_msg = "hello from server";
                if((write(client_fd, send_msg, ::strlen(send_msg))) <0)
                    std::cerr << "write error\n";
                else
                    std::cout <<"write: " << send_msg  << " to client\n";

                ep_event.data.fd = client_fd;
                ep_event.events = EPOLLIN;
                epoll_ctl(ep_fd, EPOLL_CTL_MOD, client_fd, &ep_event);
            }
        }
    }

    // std::cout << address << ':' << port;
    return 0;
}
