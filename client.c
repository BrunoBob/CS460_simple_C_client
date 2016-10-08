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

  if(client_socket == -1){
    perror("ERROR : can't create socket");
    exit(1);
  }

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(argv[1]);  //Give IP adress
  addr.sin_port = htons(atoi(argv[2])); //Give port

  if(connect(client_socket, (struct sockaddr *) &addr, sizeof(struct sockaddr)) == -1){//connect to the server
    perror("ERROR : can't connect to the server");
    exit(1);
  }

  do{
    scanf("%c", buffer); //Ask a character to user

    if(send(client_socket, buffer, sizeof(char), 0) != 1){ //Send the character
      perror("ERROR : can't send the character");
      exit(1);
    }

    *buffer = 0 ;  //Reset the buffer

    if(recv(client_socket, buffer, sizeof(char), 0) != 1){ //Read the server message
      perror("ERROR : can't recv the character");
      exit(1);
    }

    printf("Echo of %c\n", *buffer); //Print the received message

  }while(*buffer != 'q'); //Stop when end character 'q'

  return 0;
}
