#include <arpa/inet.h>
#include <netinet/in.h>


#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <memory.h>

constexpr int PORT = 22222;

static int acceptOrDie(uint16_t port)
{
    int listenfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    int yes = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)))
    {
        perror("setsockopt");
        exit(1);
    }

    struct sockaddr_in addr;
    memset(&addr, sizeof(addr), 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(listenfd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)))
    {
        perror("bind");
        exit(1);
    }

    if (listen(listenfd, 5))
    {
        perror("listen");
        exit(1);
    }

    struct sockaddr_in peer_addr;
    memset(&peer_addr, sizeof(peer_addr), 0);
    socklen_t addrlen = 0;
    int sockfd = ::accept(listenfd, reinterpret_cast<struct sockaddr*>(&peer_addr), &addrlen);
    if (sockfd < 0)
    {
        perror("accept");
        exit(1);
    }
    ::close(listenfd);
    return sockfd;
}

int read_foo(int sockfd)
{
    char buf[40];
    return static_cast<int>(::read(sockfd, buf, sizeof(buf) - 1));
}

int main()
{
    int sockfd = acceptOrDie(PORT);
    int count = 0;

    while(count < 100) {
        if(read_foo(sockfd)) ++count;
    }
    
    ::close(sockfd);
}
