#include "../common.h"
#include "rw.hpp"

#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <memory.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <chrono>


static int acceptOrDie(uint16_t port)
{
  int listenfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  assert(listenfd >= 0);

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

void receive(const Options& opt)
{
  int sockfd = acceptOrDie(opt.port);

  struct SessionMessage sessionMessage = { 0, 0 };
  if (read_n(sockfd, &sessionMessage, sizeof(sessionMessage)) != sizeof(sessionMessage))
  {
    perror("read SessionMessage");
    exit(1);
  }

  sessionMessage.number = ntohl(sessionMessage.number);
  sessionMessage.length = ntohl(sessionMessage.length);
  printf("receive number = %d\nreceive length = %d\n",
         sessionMessage.number, sessionMessage.length);
  const int total_len = static_cast<int>(sizeof(int32_t) + sessionMessage.length);
  PayloadMessage* payload = static_cast<PayloadMessage*>(::malloc(total_len));
  assert(payload);

  for (int i = 0; i < sessionMessage.number; ++i)
  {
    payload->length = 0;
    if (read_n(sockfd, &payload->length, sizeof(payload->length)) != sizeof(payload->length))
    {
      perror("read length");
      exit(1);
    }
    payload->length = ntohl(payload->length);
    assert(payload->length == sessionMessage.length);
    if (read_n(sockfd, payload->data, payload->length) != payload->length)
    {
      perror("read payload data");
      exit(1);
    }
    int32_t ack = htonl(payload->length);
    if (write_n(sockfd, &ack, sizeof(ack)) != sizeof(ack))
    {
      perror("write ack");
      exit(1);
    }
  }
  ::free(payload);
  ::close(sockfd);
}


void transmit(const Options& opt) {
    struct sockaddr_in addr = resolveOrDie(opt.host.c_str(), opt.port);
    printf("connecting to %s:%d\n", inet_ntoa(addr.sin_addr),opt.port);

    int sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    assert(sockfd >= 0);

    int ret = ::connect(sockfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

    if(ret) {
        perror("connect");
        printf("Unable to connect %s\n", opt.host.c_str());
        ::close(sockfd);
        return;
    }

    printf("connected\n");

    auto start = std::chrono::steady_clock::now();

    struct SessionMessage sessionMessage = {0,0};
    sessionMessage.number = htonl(opt.number);
    sessionMessage.length = htonl(opt.length);
    if(write_n(sockfd, &sessionMessage, sizeof(sessionMessage)) != sizeof(sessionMessage)) {
        perror("write SessionMessage");
        exit(1);
    }

    const int total_len = static_cast<int>(sizeof(int32_t) + opt.length);
    PayloadMessage* payload = static_cast<PayloadMessage*>(::malloc(total_len));
    assert(payload);
    payload->length = htonl(opt.length);

    for(int i = 0; i < opt.length; ++i) {
        payload->data[i] = "0123456789ABCDEF"[i%16];
    }
    constexpr int k = 1024;
    double total_mb = 1.0 * opt.length * opt.number / k / k;
    printf("%.3f MiB in total\n", total_mb);

    for(int i = 0; i < opt.number; ++i) {
        int nw = write_n(sockfd, payload, total_len);
        assert(nw == total_len);

        int ack = 0; 
        int nr = read_n(sockfd, &ack, sizeof(ack));
        assert(nr == sizeof(ack));
        ack = ntohl(ack);
        assert(ack == opt.length);
    }

    ::free(payload);
    ::close(sockfd);
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0;
    printf("%.3f seconds\n%.3f MiB/s\n", elapsed, total_mb / elapsed);

}

int main(int argc, char** argv) {
    Options opt;
    if(parseCommandLine(argc, argv, &opt)) {
        if(opt.transmit) {
            transmit(opt);
        } else if(opt.receive) {
            receive(opt);
        }
    }
    return 0;
}