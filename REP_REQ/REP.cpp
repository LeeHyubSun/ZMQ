#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)    Sleep(n)
#endif

using namespace std;
using namespace zmq;

int main () {
    //  Prepare our context and socket
    context_t context (1);
    socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    string revmsg;

    while (true) {
        message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        cout << "Receive Message : "
          << string((char *)request.data(), request.size())
          << endl;

        //  Do some 'work'
        sleep(1);

        //  Send reply back to client
        message_t reply(2);
        
        memcpy (reply.data(), "OK", 2);
        socket.send (reply);
    }
    return 0;
}
