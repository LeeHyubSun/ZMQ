#include <zmq.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace zmq;

int main ()
{
    //  Prepare our context and socket
    context_t context (1);
    socket_t socket (context, ZMQ_REQ);

    cout << "Connecting to hello world server…" << endl;
    socket.connect ("tcp://localhost:5555");

    string sendmsg;

    //  Do 10 requests, waiting each time for a response
    while(1) {
        cout << "Send Message : ";
        cin >> sendmsg;
        message_t request(sendmsg.size()); // 메세지 크기는 정할것!!
        memcpy (request.data(), sendmsg.data(), sendmsg.size());
        cout << "Sending : " << sendmsg << endl;
        socket.send (request);

        //  Get the reply.
        message_t reply;
        socket.recv (&reply);
        cout << "Receive Message : "
          << string((char*)reply.data(), reply.size())
          << endl;
    }
    return 0;
}
