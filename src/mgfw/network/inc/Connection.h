
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>
#include <unistd.h>


using namespace std;

typedef void (*onDataReady)(bool isReady);

/*proof-of-work for syncronous basic networking */
class Connection
{



public:
    Connection();
    Connection(string hostName, int port);
    void send_and_wait_resp(string msg); /*in the future will spawn separate thread for listening or a non-blocking mechanism */
    void onResponseReady(onDataReady callback); /* in the future data will be passed as param */
    string getResponse();
private:
    char buffer[256];
    int sockfd;
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

};
