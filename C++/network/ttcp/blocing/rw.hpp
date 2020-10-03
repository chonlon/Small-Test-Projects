#pragma once
#include <unistd.h>

int write_n(int sockfd, void* buf, int length) {
    int written = 0;
    while(written < length) {
        ssize_t nw = ::write(sockfd, static_cast<char*>(buf) + written, length - written);
        if(nw > 0) {
            written += static_cast<int>(nw);
        } else if(nw == 0) {
            break;
        } else if (errno != EINTR) {
            perror("write");
            break;
        }
    }
    return written;
}

int read_n(int sockfd, void* buf, int length)
{
  int nread = 0;
  while (nread < length)
  {
    ssize_t nr = ::read(sockfd, static_cast<char*>(buf) + nread, length - nread);
    if (nr > 0)
    {
      nread += static_cast<int>(nr);
    }
    else if (nr == 0)
    {
      break;  // EOF
    }
    else if (errno != EINTR)
    {
      perror("read");
      break;
    }
  }
  return nread;
}
