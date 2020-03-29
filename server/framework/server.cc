
#include "server.h"
#include <arpa/inet.h> 
#include <errno.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <algorithm>
#include "server.h"

#define MAXLINE 1024
#define PORT 5000

namespace framework {

void BaseServer::RegisterHandler(const std::string& path, const BaseHandlerInterface* handler) {
  handlers[path] = handler;
}

bool BaseServer::Start() const {
  int listenfd, connfd, udpfd, nready, maxfdp1; 
  char buffer[MAXLINE]; 
  pid_t childpid; 
  fd_set rset; 
  ssize_t n; 
  socklen_t len; 
  const int on = 1; 
  struct sockaddr_in cliaddr, servaddr; 
  void sig_chld(int); 

  /* create listening TCP socket */
  listenfd = socket(AF_INET, SOCK_STREAM, 0); 
  bzero(&servaddr, sizeof(servaddr)); 
  servaddr.sin_family = AF_INET; 
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
  servaddr.sin_port = htons(PORT); 

  // binding server addr structure to listenfd 
  bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
  listen(listenfd, 10); 

  /* create UDP socket */
  udpfd = socket(AF_INET, SOCK_DGRAM, 0); 
  // binding server addr structure to udp sockfd 
  bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 

  // clear the descriptor set 
  FD_ZERO(&rset); 

  // get maxfd 
  maxfdp1 = std::max(listenfd, udpfd) + 1; 
  while (true) { 
    // set listenfd and udpfd in readset 
    FD_SET(listenfd, &rset); 
    FD_SET(udpfd, &rset); 

    // select the ready descriptor 
    nready = select(maxfdp1, &rset, NULL, NULL, NULL); 

    // if tcp socket is readable then handle 
    // it by accepting the connection 
    if (FD_ISSET(listenfd, &rset)) { 
      len = sizeof(cliaddr);
      connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len); 
      if ((childpid = fork()) == 0) { 
        close(listenfd); 
        bzero(buffer, sizeof(buffer)); 
        printf("Req recd: "); 
        read(connfd, buffer, sizeof(buffer));
        puts(buffer); 
        const BaseHandlerInterface* handler = handlers.at("path");
        const std::string& response = handler->BaseHandle(std::string(buffer));
        write(connfd, response.c_str(), response.length()); 
        close(connfd); 
        exit(0); 
      } 
      close(connfd); 
    }
  } 
  return true;
} 
}  // namespace framework

