//refer to http://www.binarytides.com/socket-programming-c-linux-tutorial/
#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write

int main(int argc, char *argv[])
{
    int socket_desc, new_socket, c;
    struct sockaddr_in server, client;
    char message[100];

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8889);

    //server function: bind, listen , accept

    //Bind

    /*
    int bind(int sockfd, struct sockaddr *my_addr, int addrlen);
    return: 0 if ok, -1 on error

    associate the server's socket address with the socket descriptor
    question: 
    why we don't need the bind operation for the client? 
    what is the socket address for the client?
    */

    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    puts("bind done");

    //Listen

    /*
    server are passive entities that wait for connection requests from the client
    a server call the listen to label that descriptor will be used by a server instead of the client

    listen function convert sockfd from active socket to a listening socket that can recieve the requests from the clients

    the backlog parameters is sth realte to the detail of TCP/IP , we set it to a default value here

    int listen (int sockfd, int backlog)
    return 0 if ok -1 on error
    
    */

    listen(socket_desc, 1024);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    /*
    int accept(int listenfd, struct sockaddr* addr, int *addrlen)
    return: nonnegative connected descriptor if ok, -1 on error

    The accept function waits for a connection request from a client to arrive on the listening descriptor listenfd
    then fill in the clients's socket address in addr, 
    and return a connected descriptor that can be used to communicate with client using I/O funciton


    IO multiplexing
    block -> select -> poll -> epoll ?
    
    */
    int i = 0;

    // variables for getting the src addr
    socklen_t len;
    struct sockaddr_storage srcaddr;
    char ipstr[INET6_ADDRSTRLEN];
    int srcPort;
    while (1)
    {
        new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);

        len = sizeof srcaddr;
        getpeername(new_socket, (struct sockaddr *)&srcaddr, &len);

        // deal with both IPv4 and IPv6:
        if (srcaddr.ss_family == AF_INET)
        {
            struct sockaddr_in *s = (struct sockaddr_in *)&srcaddr;
            srcPort = ntohs(s->sin_port);
            inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
        }
        else
        { // AF_INET6
            struct sockaddr_in6 *s = (struct sockaddr_in6 *)&srcaddr;
            srcPort = ntohs(s->sin6_port);
            inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
        }

        printf("Src IP address: (%s)\n", ipstr);
        printf("Src port      : (%d)\n", srcPort);

        if (new_socket < 0)
        {
            perror("accept failed");
            return 1;
        }

        puts("Connection accepted");

        //Reply to the client

        i++;
        sprintf(message, "Hello Client , I have received your connection %d times\n", i);

        printf("processing numer (%d) request\n", i);

        // write the data to the socket and these data will return back to client
        write(new_socket, message, strlen(message));

        //shutdown(new_socket);
        close(new_socket);

        //control the behaviours of server
        if (i == 5)
        {
            break;
        }
    }

    return 0;
}