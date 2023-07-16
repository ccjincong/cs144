#include "tcp_receiver.hh"
#include <cstdint>

using namespace std;

void TCPReceiver::receive (TCPSenderMessage message , Reassembler &reassembler , Writer &inbound_stream) {

    if ( message.SYN == true ) {
        zero_point = message.seqno;
        flag = true;
    }

    if ( flag == true ) {

        reassembler.insert (message.seqno.unwrap (zero_point , reassembler.get_first_unassembled_index ()) ,
                            message.payload , message.FIN , inbound_stream);

        ackno = zero_point.wrap (reassembler.get_first_unassembled_index () + flag + message.FIN , zero_point);
    }

    send (inbound_stream);
}

TCPReceiverMessage TCPReceiver::send (const Writer &inbound_stream) const {
    return TCPReceiverMessage{ ackno ,
                               uint16_t (min (inbound_stream.available_capacity () , (uint64_t) 65535)) };
}
