#include <stdexcept>
#include <iostream>
#include "byte_stream.hh"
#include <cstring>

using namespace std;

ByteStream::ByteStream (uint64_t capacity) : capacity_ (capacity) , buffer () {
}

void Writer::push (string data) {
    uint64_t push_size = min (available_capacity () , data.size ());
    if ( push_size == 0 )
        return;
    if ( push_size == data.size ())
        buffer.push_back (data);
    else {
        buffer.push_back (data.erase (push_size));
    }

    total_push += push_size;
    buffer_len += push_size;
}

void Writer::close () {
    closed = true;
}

void Writer::set_error () {
    error = true;
}

bool Writer::is_closed () const {
    return closed;
}

uint64_t Writer::available_capacity () const {
    return capacity_ - buffer_len;
}

uint64_t Writer::bytes_pushed () const {
    return total_push;
}


string_view Reader::peek () const {
    return std::string_view (&((buffer.front ())[ 0 ]) , 1);
}

bool Reader::is_finished () const {
    return closed == true && buffer_len == 0;
}

bool Reader::has_error () const {
    return error;
}

void Reader::pop (uint64_t len) {
    total_pop += len;
    buffer_len -= len;
    while (len > 0) {
        string front = buffer.front ();
        if ( front.size () <= len ) {
            len -= front.size ();
            buffer.pop_front ();
        } else {
            buffer.front().erase (0 , len);;
            len = 0;
        }
    }
}

uint64_t Reader::bytes_buffered () const {
    return buffer_len;
}

uint64_t Reader::bytes_popped () const {
    return total_pop;
}
