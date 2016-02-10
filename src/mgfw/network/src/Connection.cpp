#include "../inc/Connection.h"


Connection::Connection()
{



}

Connection::Connection(string hostName, int port)
{
    portno = port;

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");

    }

    fcntl(sockfd, F_SETFL, O_NONBLOCK);


    server = gethostbyname(hostName.c_str());

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");

    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");

    }
}

void Connection::send_and_wait_resp(string msg)
{
    /* Now ask for a message from the user, this message
       * will be read by server
    */
    int n  = 0;
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);

    /* Send message to the server */
    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0) {
       perror("ERROR writing to socket");

    }

    /* Now read server response */
    bzero(buffer,256);
    n = read(sockfd, buffer, 255);

    if (n < 0) {
       perror("ERROR reading from socket");

    }

    printf("%s\n",buffer);


//    retval = send(client->acpt_fd, msgcb->data_ptr, MSGCB_DLEN(msgcb),
//                  MSG_DONTWAIT);


//    if (retval < 0) {
//        if (errno == EAGAIN) {

//        } else {

//        }
//    }

}


void Connection::onResponseReady(onDataReady callback)
{


}


std::string Connection::getResponse()
{
 std::string s(buffer);
 return s;

}
