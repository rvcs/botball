// Created on Sun December 28 2014

//#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
//#include <socket.hpp>
#include <iostream>

using namespace std;

int doit(int argc, char * argv[]);

int main(int argc, char *argv[])
{
  int result = doit(argc, argv);
  
  return result;
}

char buf[2048];
size_t buf_len = sizeof(buf);

int doit(int argc, char * argv[])
{
  short port = 8402;
  char const * log_host_ip = "192.168.11.117";
  if (argc > 1) {
    log_host_ip = argv[1];
  }
  if (argc > 2) {
    port = atoi(argv[2]);
  }
  cout << "Logging to: " << log_host_ip << ":" << port << endl;

  struct sockaddr_in myaddr, log_host_addr;

  memset(&myaddr, 0, sizeof(myaddr));
  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myaddr.sin_port = htons(0);

  memset(&log_host_addr, 0, sizeof(log_host_addr));
  log_host_addr.sin_family = AF_INET;
  log_host_addr.sin_port = htons(port);
  inet_pton(AF_INET, log_host_ip, &log_host_addr.sin_addr);

  int fd = 0;
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    return 3;
  }
  if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
      close(fd);
    return 4;
  }
  if (connect(fd, (struct sockaddr *)&log_host_addr, sizeof(log_host_addr)) < 0) {
    close(fd);
     return 5;
  }
  
  int num_sent = 0;
  unsigned char const * pbuf = NULL;

  do {

    if (fgets(buf, buf_len, stdin) == NULL) { break; }

    pbuf = (unsigned char const *)buf;
    num_sent = send(fd, (char const *)pbuf, strlen((char const *)pbuf), 0);
//    cout << "num sent:" << num_sent << endl;
  } while(1);
  
  char const * msg = "--END--\n";
  pbuf = (unsigned char const *)msg;
  send(fd, (char const *)pbuf, strlen((char const *)pbuf), 0);

  close(fd);
  return 0;
}
