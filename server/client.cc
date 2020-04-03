// TCP Client program 
#include <string.h>
#include <netinet/in.h> 
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
#include "fake_types.pb.h"
#include "framework/network.pb.h"

#define PORT 5000 
#define MAXLINE 1024 

using ::framework::Packet;

int main() 
{ 
  int sockfd; 
  char buffer[MAXLINE]; 
  struct sockaddr_in servaddr; 

  int n, len; 
  // Creating socket file descriptor 
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
    printf("socket creation failed"); 
    exit(0); 
  } 

  memset(&servaddr, 0, sizeof(servaddr)); 

  // Filling server information 
  servaddr.sin_family = AF_INET; 
  servaddr.sin_port = htons(PORT); 
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

  if (connect(sockfd, (struct sockaddr*)&servaddr, 
              sizeof(servaddr)) < 0) { 
    printf("\n Error : Connect Failed \n"); 
  } 

  memset(buffer, 0, sizeof(buffer));
  example::FakeRequest req;
  req.set_value("fakerequest");
  const std::string& request = req.SerializeAsString();
  
  Packet packet;
  packet.set_payload(request);
  packet.mutable_header()->set_path("rpc2");
  const std::string& packet_str = packet.SerializeAsString();
  write(sockfd, packet_str.c_str(), packet_str.length());
  printf("Response recv: "); 
  read(sockfd, buffer, sizeof(buffer)); 
  puts(buffer); 
  close(sockfd); 
} 

