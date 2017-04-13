#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <zmq.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    zmq::context_t ctx(1);
    zmq::socket_t socket(ctx, ZMQ_REQ);

    cout << "Connecting to Server" << endl;
    socket.connect("tcp://localhost:5559");

    while (true)
    {
        zmq::message_t request(5);
        memcpy(request.data(), "Hello", 5);
        socket.send(request);

        this_thread::sleep_for(chrono::milliseconds(100));

        zmq::message_t rep;
        socket.recv(&rep);

        cout << string((const char*)rep.data(), rep.size()) << endl;
    }

    return 0;
}
