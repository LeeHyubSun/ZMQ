#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <zmq.hpp>

using namespace std;

zmq::message_t Str2Msg_t(const string &strMsg)
{
    zmq::message_t zmqMsg(strMsg.size());
    memcpy(zmqMsg.data(), strMsg.data(), strMsg.size());

    return zmqMsg;
}

int main(int argc, char *argv[])
{
    zmq::context_t ctx(1);
    zmq::socket_t socket(ctx, ZMQ_PUB);

    socket.connect("tcp://localhost:5559");
    string strFilter1 = "flt1";
    string strFilter2 = "flt2";
    string strMsg1 = "";
    string strMsg2 = "";

    int i = 1;
    int j = 1;
    while (true)
    {
        strMsg1 = to_string(i*2);
        strMsg2 = to_string((j*2)+1);

        zmq::message_t filter1 = Str2Msg_t(strFilter1);
        zmq::message_t sendMsg1 = Str2Msg_t(strMsg1);
        zmq::message_t filter2 = Str2Msg_t(strFilter2);
        zmq::message_t sendMsg2 = Str2Msg_t(strMsg2);

        socket.send(filter1, ZMQ_SNDMORE);
        socket.send(sendMsg1);
        socket.send(filter2, ZMQ_SNDMORE);
        socket.send(sendMsg2);

        this_thread::sleep_for(chrono::milliseconds(100));

        i++;
        j++;
    }

    return 0;
}
