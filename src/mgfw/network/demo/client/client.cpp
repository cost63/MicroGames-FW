#include <mgfw/Connection.h>
#include <iostream>
#include <string>

using namespace std;

Connection* gConn = NULL;

void OnDataReadyCbk(bool isReady)
{

    cout << "got " << gConn->getResponse() << endl;
}

int main()
{

    std::string test("ping pong");
    gConn = new Connection("localhost", 1337);

    if(gConn != NULL)
    {
        gConn->onResponseReady(OnDataReadyCbk);
        gConn->send_and_wait_resp(test);

    }

}
