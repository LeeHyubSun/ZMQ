#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <zmq.hpp>

using namespace std;
using namespace zmq;

message_t string_copy_message(string s_Msg)
{
    message_t MSG(s_Msg.size());
    memcpy(MSG.data(), s_Msg.data(), s_Msg.size());

    return MSG;
}

int main(int argc, char *argv[])
{
    context_t ctx(1);
    socket_t socket(ctx, ZMQ_PUB);

    socket.bind("tcp://*:5555");
    string strFilter1 = "flt1";
    string strFilter2 = "flt2";

    string strMsg1 = "";
    string strMsg2 = "";
    int i = 0;
    int j = 1;

    while (true)
    {
        strMsg1 = to_string(i);
        strMsg2 = to_string(j);

        message_t filter1 = string_copy_message(strFilter1);
        message_t sendMsg1 = string_copy_message(strMsg1);
        message_t filter2 = string_copy_message(strFilter2);
        message_t sendMsg2 = string_copy_message(strMsg2);

        socket.send(filter1, ZMQ_SNDMORE);
        socket.send(sendMsg1);
        socket.send(filter2, ZMQ_SNDMORE);
        socket.send(sendMsg2);

        i = i+2;
        j = j+2;
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}
