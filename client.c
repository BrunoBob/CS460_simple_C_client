#include "client.h"

int main(int argc, char* argv[]){
  if(argc != 3){
    perror("ERROR : wrong number of arguments, expected ./client IP_of_server port");
    exit(1);
  }

  char* buffer = (char*) malloc(sizeof(char));
  int client_socket;
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(addr)); //Fill the struct with zeros

  client_socket = socket(AF_INET,SOCK_STREAM, 0); //Create the socket descriptor

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(argv[1]);  //Give IP adress
  addr.sin_port = htons(atoi(argv[2])); //Give port

connect(client_socket, (struct sockaddr *) &addr, sizeof(struct sockaddr)); //connect to the server

  do{
    scanf("%c", buffer); //Ask a character to user

    send(client_socket, buffer, sizeof(char), 0); //Send the character

    *buffer = 0 ;  //Reset the buffer

    recv(client_socket, buffer, sizeof(char), 0); //Read the server message

    printf("Echo of %c\n", *buffer); //Print the recv message
    
  }while(*buffer != 'q'); //Stop when end character 'q'

  return 0;
}
