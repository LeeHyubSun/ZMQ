#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <zmq.hpp>

using namespace std;

string Msg_t2Str(zmq::message_t &msg)
{
    return string((const char*)msg.data(), msg.size());
}

// argv1: Host IP
// argv2: filter
int main (int argc, char *argv[])
{
    zmq::context_t ctx(1);
    zmq::socket_t socket(ctx, ZMQ_SUB);
    socket.connect("tcp://localhost:5560");

    string strFilter = argv[1];
    socket.setsockopt(ZMQ_SUBSCRIBE, strFilter.c_str(), strFilter.size());

    while (true)
    {
        zmq::message_t filter, recvMsg;

        socket.recv(&filter);
        socket.recv(&recvMsg);

        this_thread::sleep_for(chrono::milliseconds(100));

        cout << "Sub filter: " << Msg_t2Str(filter) << ", "
            << "Sub data: " << Msg_t2Str(recvMsg) << endl;
    }


    return 0;
}
