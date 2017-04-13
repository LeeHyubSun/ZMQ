#include <iostream>
#include <string>
#include <zmq.hpp>

using namespace std;
using namespace zmq;


// argv1: Host IP
// argv2: filter
int main (int argc, char *argv[])
{
    context_t ctx(1);
    socket_t socket(ctx, ZMQ_SUB);
    socket.connect("tcp://localhost:5555");

    string strFilter = "flt2";
    socket.setsockopt(ZMQ_SUBSCRIBE, strFilter.c_str(), strFilter.size());

    while (true)
    {
        message_t filter, recvMsg;

        socket.recv(&filter);
        socket.recv(&recvMsg);

        //this_thread::sleep_for(chrono::milliseconds(100));

        cout << "Sub filter: " << string((char*)filter.data(), filter.size()) << ", "
            << "Sub data: " << string((char*)recvMsg.data(), recvMsg.size()) << endl;
    }


    return 0;
}
