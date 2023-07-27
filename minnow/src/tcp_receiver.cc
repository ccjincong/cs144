#include "tcp_receiver.hh"
#include <cstdint>
#include <fstream>

using namespace std;

void TCPReceiver::receive (TCPSenderMessage message , Reassembler &reassembler , Writer &inbound_stream) {

    if ( message.SYN == true ) {
        zero_point = message.seqno;
        flag_SYN = true;
    }


    if ( flag_SYN == true ) {

        uint64_t index = message.seqno.unwrap (zero_point , reassembler.get_first_unassembled_index ()); // 当前应该插的位置

        if ( message.SYN == true ) // index 正常是要减一的。因为如果SYN和有效数据不是同时发送的话，第一个有效数据的index是1，但是reassembler
                                   // 第一个是从0开始的，
            reassembler.insert (0 , message.payload , message.FIN , inbound_stream);
        else
            reassembler.insert (index-1 , message.payload , message.FIN , inbound_stream);

        ackno = zero_point.wrap (reassembler.get_first_unassembled_index () + 1 + inbound_stream.is_closed() , zero_point); //SYN之后才会有回复，所以也需要写在判断里面
    }

    send (inbound_stream);
}

TCPReceiverMessage TCPReceiver::send (const Writer &inbound_stream) const {
    return TCPReceiverMessage{ ackno ,
                               uint16_t (min (inbound_stream.available_capacity () , (uint64_t) 65535)) };
}
