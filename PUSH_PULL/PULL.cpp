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

string message_copy_string(message_t &m_Msg)
{
    return string((const char*)m_Msg.data(), m_Msg.size());
}

int main (int argc, char *argv[])
{
    context_t ctx(1);
    //zmq::socket_t socket(ctx, ZMQ_PUSH);
    socket_t socket(ctx, ZMQ_PULL);
    //socket.bind("tcp://*:5555");
    socket.connect("tcp://localhost:5555");

    string strA = "aaa";
    int i = 0;
    while (true)
    {
        //strA = to_string(i++);
        //zmq::message_t sendMsg = Str2Msg_t(strA);
        //socket.send(sendMsg);

        message_t recvMsg;
        socket.recv(&recvMsg);
        cout << "recvMsg: " << message_copy_string(recvMsg) << endl;


        this_thread::sleep_for(chrono::milliseconds(100));
    }
    return 0;
}
