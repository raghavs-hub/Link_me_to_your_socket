#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int sockfd_sender, sockfd_receiver;

int main() {
  std::string sent_msg = "Hello there";
  char recieved_msg[1000];
  sockfd_sender = socket(PF_INET, SOCK_DGRAM, 0);
  sockfd_receiver = socket(PF_INET, SOCK_DGRAM, 0);

  if (sockfd_receiver == -1 || sockfd_sender == -1) {
    std::cout << "sockfd error" << std::endl;
  }

  struct sockaddr_in send_addr;
  send_addr.sin_family = AF_INET;
  send_addr.sin_port = htons(SEND_PORT);
  send_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
  memset(&(send_addr.sin_zero), '\0', 8);

  bind(sockfd_sender, (struct sockaddr *)&send_addr, sizeof(struct sockaddr));

  struct sockaddr_in receive_addr;
  receive_addr.sin_family = AF_INET;
  receive_addr.sin_port = htons(RECEIVE_PORT);
  receive_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(&(receive_addr.sin_zero), '\0', 8);

  bind(sockfd_receiver, (struct sockaddr *)&receive_addr,
       sizeof(struct sockaddr));

  int x = sendto(sockfd_sender, sent_msg.data(), sent_msg.size(), 0,
                 (struct sockaddr *)&receive_addr, sizeof(struct sockaddr));

  int l = recvfrom(sockfd_receiver, recieved_msg, 1000, 0, nullptr, nullptr);

  close(sockfd_receiver);
  close(sockfd_sender);
  // std::cout.write(recieved_msg,l);
  std::cout << sent_msg;
  return 0;
}
