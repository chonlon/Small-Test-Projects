#include "sylar.h"
#include "iomanager.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
//#include <netinet/in.h>

auto g_logger = SYLAR_LOG_NAME("root");

int sock = 0;
void test_fiber() {
    SYLAR_LOG_INFO(g_logger) << "test_fiber sock=" << sock;

    //sleep(3);

    //close(sock);
    //sylar::IOManager::GetThis()->cancelAll(sock);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sock, F_SETFL, O_NONBLOCK);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "125.39.52.26", &addr.sin_addr.s_addr);

    if(!connect(sock, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr))) {
    } else if(errno == EINPROGRESS) {
        SYLAR_LOG_INFO(g_logger) << "add event errno=" << errno << " " << strerror(errno);
        sylar::IOManager::GetThis()->addEvent(sock, sylar::IOManager::READ, [](){
          SYLAR_LOG_INFO(g_logger) << "read callback";
        });
        sylar::IOManager::GetThis()->addEvent(sock, sylar::IOManager::WRITE, [](){
          SYLAR_LOG_INFO(g_logger) << "write callback";
          //close(sock);
          sylar::IOManager::GetThis()->cancelEvent(sock, sylar::IOManager::READ);
          close(sock);
        });
    } else {
        SYLAR_LOG_INFO(g_logger) << "else " << errno << " " << strerror(errno);
    }

}

void test1() {
    sylar::IOManager io_manager;
    io_manager.schedule(&test_fiber);
//    short port = 80;
//    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
//    //setsockopt()
//    fcntl(sock_fd, F_SETFL, O_NONBLOCK);
//
//    ::sockaddr_in sock_addr;
//    memset(&sock_addr, 0 , sizeof(sockaddr_in));
//    sock_addr.sin_family =  AF_INET;
//    sock_addr.sin_port = htons(port);
//    sock_addr.sin_addr.s_addr = inet_pton(AF_INET, "125.39.52.26", &sock_addr.sin_addr.s_addr);
//
//    connect(sock_fd, reinterpret_cast<const sockaddr*>(&sock_addr), sizeof(sock_addr));
//
//    io_manager.addEvent(sock_fd, sylar::IOManager::READ, [](){
//       SYLAR_LOG_INFO(g_logger) << "connected";
//    });
//    io_manager.addEvent(sock_fd, sylar::IOManager::WRITE, [](){
//       SYLAR_LOG_INFO(g_logger) << "connected";
//    });


}

int main(int argc, char** argv) {
    test1();
    return 0;
}

