#include <stdexcept>
#include <iostream>
#include "byte_stream.hh"
#include <cstring>
#include <fstream>

using namespace std;

ByteStream::ByteStream (uint64_t capacity) : buffer () , capacity_ (capacity) {
}

void Writer::push (string data) {

    uint64_t push_size = min (available_capacity () , data.size ());
    for (uint64_t i = 0; i < push_size; i++)
        buffer.push_back (data[ i ]);

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
    return std::string_view (&(buffer.front ()) , 1);
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
    for (uint64_t i = 0; i < len; i++)
        buffer.pop_front ();
}

uint64_t Reader::bytes_buffered () const {
    return buffer_len;
}

uint64_t Reader::bytes_popped () const {
    return total_pop;
}
