#include <chrono>
#include <iostream>
#include <thread>
#include <zmq.hpp>

using namespace std;

int main (int argc, char *argv[])
{
    zmq::context_t ctx(1);
    zmq::socket_t frontend(ctx, ZMQ_XSUB);
    zmq::socket_t backend(ctx, ZMQ_XPUB);

    frontend.bind("tcp://*:5559");
    backend.bind("tcp://*:5560");

    zmq::proxy((void *)frontend, (void *)backend, nullptr);
    // zmq::pollitem_t items[] = {
    //     { frontend, 0, ZMQ_POLLIN, 0 },
    //     { backend, 0, ZMQ_POLLIN, 0}
    // };

    return 0;
}
