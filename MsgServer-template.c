#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include <netinet/in.h> 
#include<unistd.h>
#include <time.h>


#define DEFAULT_STRLEN 30000
#define SERVER_PORT  8080

const char *products[1000] = { "My Product 1", "My Product 2", "My Product 3", "My Product 4"};

void db_handle_client(int clientfd);

void error(const char *msg){
    
    printf("Error: %s\n",msg);
    exit(1);
}


int main(void)
{
    /* Create Socket*/    
        
    /* Bind socket with IP address and Port*/
    
    /* Listen for incoming connections */
    
    // Step 1 - create a socket
    int socketfd;
    socketfd=socket(AF_INET,SOCK_STREAM,0);
    if(socketfd<0){
        error("Error creating socket");
    }
    printf("Socket Created\n");
        

    //Step 2 - bind socket to an address
    //define IP and Port
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr= INADDR_ANY;
    serveraddr.sin_port=htons(8080);
        
    printf("Address created\n");
    //bind address to socket
    int br;
    br = bind(socketfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(br<0){
        error("Error Binding");
    }
    printf("Bind successful\n");
            
    
    //Step 3 - listen for connection requests
    if(listen(socketfd,5)<0){
        error("Litening error");
    }
    printf("Success listening\n");
    
    
  /* Accept */
   while(1){
       struct sockaddr_in clientaddr;
       int clienlen = sizeof(clientaddr);
       int clientfd = accept(socketfd,(struct sockaddr*)&clientaddr,(socklen_t*)&clienlen);
   
      /* Handle client */
        db_handle_client(clientfd);
        }
    return 0;
}




void db_handle_client(int clientfd)
{
    char outmsg[DEFAULT_STRLEN];
    char inmsg[DEFAULT_STRLEN];
    
    if(clientfd < 0) {
        printf("Error: Failed to accept client connection\n"); 
        return;
    }
     /* Read request message from client and print the message*/
    char incoming[2000]; //ex
    ssize_t r = recv(clientfd, incoming, 2000, 0);
    if(r <= 0) {
    printf("Error receiving message");
    close(clientfd);
    exit(0);
    }
    // Do something with receiving message
    printf("Received message: %s", incoming);
    char *token[2];
    
    char delim[] = " /";
    char *ptr = strtok(incoming, delim);
    for(int i = 0; i < 2; i++){
        token[i] = ptr;
        ptr = strtok(NULL, delim);
    }
    printf("METHOD: %s\n",token[0]);
    printf("ROUTE: %s\n",token[1]);
    
    printf("Test list: %s\n",products[0]);
    
    
    if(strcmp(token[0],"GET")==0 && strcmp(token[1],"0")==0){
        char date[100];
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(date, sizeof(date)-1, "%d %m %Y %H:%M", t);
        char header[]="HTTP/1.1 200 OK\nContent-Type: text/html; charset=ISO-8859-1\nContent-length:";
        char msg[DEFAULT_STRLEN];
        strcpy(msg,products[0]);
        snprintf(outmsg,sizeof(outmsg), "%s%lu\n\n\%s\n",header,strlen(msg)+1,msg);
        ssize_t r1 = send(clientfd, outmsg, strlen(outmsg), 0);
    }else if(strcmp(token[0],"GET")==0 && strcmp(token[1],"1")==0){
        char date[100];
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(date, sizeof(date)-1, "%d %m %Y %H:%M", t);
        char header[]="HTTP/1.1 200 OK\nContent-Type: text/html; charset=ISO-8859-1\nContent-length:";
        char msg[DEFAULT_STRLEN];
        strcpy(msg,products[1]);
        snprintf(outmsg,sizeof(outmsg), "%s%lu\n\n\%s\n",header,strlen(msg)+1,msg);
        ssize_t r1 = send(clientfd, outmsg, strlen(outmsg), 0);
    }else if(strcmp(token[0],"GET")==0 && strcmp(token[1],"2")==0){
        char date[100];
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(date, sizeof(date)-1, "%d %m %Y %H:%M", t);
        char header[]="HTTP/1.1 200 OK\nContent-Type: text/html; charset=ISO-8859-1\nContent-length:";
        char msg[DEFAULT_STRLEN];
        strcpy(msg,products[2]);
        snprintf(outmsg,sizeof(outmsg), "%s%lu\n\n\%s\n",header,strlen(msg)+1,msg);
        ssize_t r1 = send(clientfd, outmsg, strlen(outmsg), 0);
    }else if(strcmp(token[0],"GET")==0 && strcmp(token[1],"3")==0){
        char date[100];
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(date, sizeof(date)-1, "%d %m %Y %H:%M", t);
        char header[]="HTTP/1.1 200 OK\nContent-Type: text/html; charset=ISO-8859-1\nContent-length:";
        char msg[DEFAULT_STRLEN];
        strcpy(msg,products[3]);
        snprintf(outmsg,sizeof(outmsg), "%s%lu\n\n\%s\n",header,strlen(msg)+1,msg);
        ssize_t r1 = send(clientfd, outmsg, strlen(outmsg), 0);
    }else if(strcmp(token[0],"POST")==0 && strcmp(token[1],"HTTP")!=0){
        char date[100];
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(date, sizeof(date)-1, "%d %m %Y %H:%M", t);
        char header[]="HTTP/1.1 200 OK\nContent-Type: text/html; charset=ISO-8859-1\nContent-length:";
        char msg[DEFAULT_STRLEN];
        strcpy(products,token[1]);
        snprintf(outmsg,sizeof(outmsg), "%s%lu\n\n\%s\n",header,strlen(msg)+1,msg);
        ssize_t r1 = send(clientfd, outmsg, strlen(outmsg), 0);
    }else if(strcmp(token[0],"PUT")==0 && strcmp(token[1],"HTTP")!=0){
        char content[] = "Hello from server";
        char date[100];
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(date, sizeof(date)-1, "%d %m %Y %H:%M", t);
        snprintf(outmsg,sizeof(outmsg), "HTTP/1.1 200 OK\nDate:%s\nContent-Type: text/html; charset=ISO-8859-1\nContent-length: %lu\n\n\%s\n",date,sizeof(products[3]),products[3]);
        ssize_t r1 = send(clientfd, outmsg, strlen(outmsg), 0);
    }else if(strcmp(token[0],"DELETE")==0 && strcmp(token[1],"HTTP")!=0){
        char content[] = "Hello from server";
        char date[100];
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(date, sizeof(date)-1, "%d %m %Y %H:%M", t);
        snprintf(outmsg,sizeof(outmsg), "HTTP/1.1 200 OK\nDate:%s\nContent-Type: text/html; charset=ISO-8859-1\nContent-length: %lu\n\n\%s\n",date,sizeof(products[3]),products[3]);
        ssize_t r1 = send(clientfd, outmsg, strlen(outmsg), 0);
    }else{
        char content[] = "Bad Request";
        char date[100];
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(date, sizeof(date)-1, "%d %m %Y %H:%M", t);
        snprintf(outmsg,sizeof(outmsg), "HTTP/1.1 404 Bad Request\nDate:%s\nContent-Type: text/html; charset=ISO-8859-1\nContent-length: %lu\n\n%s\n",date,sizeof(content),content);
        ssize_t r1 = send(clientfd, outmsg, strlen(outmsg), 0);
    }

    
    if(r < 0) {
    printf("Error sending message");
    close(clientfd);
    exit(0);
    }
    
    shutdown(clientfd,SHUT_RDWR);
}
