/* A simple server in the internet domain using TCP
 * Answer the questions below in your writeup
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    /* 1. What is argc and *argv[]?
     argc and argv[] are ways for the main() function to interact and get commands from
     the command line. argc contains the amount of arguments are being passes while
     *argv[] is an array of pointers to the arguments being passed.
     */
    int sockfd, newsockfd, portno;
    /* 2. What is a UNIX file descriptor and file descriptor table?
     A file descriptor is a single integer that contains information to identify an
     open file. A file descriptor table is just a collection of these file descriptor
     so that the operating system can access this information.
     */
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    /* 3. What is a struct? What's the structure of sockaddr_in?
     A stuct is a data type that is a collection of other data types. Its essentially
     a big block of smaller nuggest of information. A struct commonly has data types such as
     strings or ints but it can also be a collection of other structs or classes. Here, 
     serv_addr and cli_addr are just instances of the struct sockaddr_in. Together the 
     struct stores internet addresses.
     */
    
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* 4. What are the input parameters and return value of socket()
     AF_INET tells the socket what address family to talk to. Here, AF_INET tells the socket to use IPv4.
     sock stream tells the function the socket type being used. Here, it is telling the function that the
     TCP protocol is being used. Finally, 0 tells the socket function to use the default protocol for 
     SOCK_STREAM. The return value of socket() is just a file descriptor.
     */
    
    if (sockfd < 0) 
       error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    /* 5. What are the input parameters of bind() and listen()?
     The first input parameter of bind() is sockfd. It is a socket descriptor which tells the function the socket’s endpoint.
     Next is (struct sockaddr *) &serv_addr, it is a pointer that has the server's address information. Last is sizeof(serv_addr) 
     it represents the size of sockaddr. listen() has two input parameters. The first is sockfd, a socket descriptor that tells
     the function that this is a passive socket so it receives connection requests. Lastly, we have backlog. It contains the 
     largest number of connections that can possibly be waiting for the socket.
     */
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    while(1) {
        /* 6.  Why use while(1)? Based on the code below, what problems might occur if there are multiple simultaneous connections to handle?
        The while loop to make sure the program always iterates through the while loop to make sure it it always ready to
	recieve new addresses. The issue is with this is if it is running through the while loop accepting one new address,
	an even newer address could be missed. 
        */
        
	char buffer[256];
        newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
	/* 7. Research how the command fork() works. How can it be applied here to better handle multiple connections?
         The fork() command is a way to create a new process in Unix-like operating systems by copying the current one.
         The new process is called a "child process" and it's a complete copy of the "parent process," including its program,
         memory, and information about what it's doing. The child process runs on its own and can do different things from the
         parent process. The fork() command returns a special number to let the parent and child know who's who. The child
         process can then change what it's running using the exec() command. It can be used to handle multiple client connections
         in a TCP client-server system simultaneously. The server creates a child process for each incoming connection, allowing
         the parent process to keep listening for new connections. This way, multiple clients can be served efficiently without
         blocking other clients. 
         */
        
	if (newsockfd < 0) 
             error("ERROR on accept");
	bzero(buffer,256);
        
	n = read(newsockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        printf("Here is the message: %s\n",buffer);
        n = write(newsockfd,"I got your message",18);
        if (n < 0) 
            error("ERROR writing to socket");
        close(newsockfd);
    }
    close(sockfd);
    return 0; 
}
  
/* This program makes several system calls such as 'bind', and 'listen.' What exactly is a system call?
    A system call is just a way for the user to request some sort of service that is ran by the operating system.
    These inlcude read(), write(), fork(), etc.
 */
