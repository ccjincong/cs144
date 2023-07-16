#pragma once

#include "reassembler.hh"
#include "tcp_receiver_message.hh"
#include "tcp_sender_message.hh"
#include <optional>

class TCPReceiver {
public:
    /*
     * The TCPReceiver receives TCPSenderMessages, inserting their payload into the Reassembler
     * at the correct stream index.
     */
    void receive (TCPSenderMessage message , Reassembler &reassembler , Writer &inbound_stream);

    /* The TCPReceiver sends TCPReceiverMessages back to the TCPSender. */
    TCPReceiverMessage send (const Writer &inbound_stream) const;

private:
    Wrap32 zero_point{ 0 };
    std::optional<Wrap32> ackno {};
    bool flag = false;
};
