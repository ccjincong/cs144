#pragma once

#include "byte_stream.hh"

#include <string>
#include <unordered_map>

class UnionFind {
public:
    UnionFind () : parent () {}

    uint64_t find (uint64_t p) {
        if ( p != parent[ p ] )
            return parent[ p ] = find (parent[ p ]);
        return p;
    }

    void unite (uint64_t p , uint64_t q) {
        parent[ find (p) ] = find (q);
    }

    void update (uint64_t right) {
        for (uint64_t i = right; i > 0; i--) {
            if ( parent.count (i) != 0 )
                return;
            parent[ i ] = i;
        }
    }

private:
    std::unordered_map<uint64_t , uint64_t> parent;
};

class Reassembler {
public:
    /*
     * Insert a new substring to be reassembled into a ByteStream.
     *   `first_index`: the index of the first byte of the substring
     *   `data`: the substring itself
     *   `is_last_substring`: this substring represents the end of the stream
     *   `output`: a mutable reference to the Writer
     *
     * The Reassembler's job is to reassemble the indexed substrings (possibly out-of-order
     * and possibly overlapping) back into the original ByteStream. As soon as the Reassembler
     * learns the next byte in the stream, it should write it to the output.
     *
     * If the Reassembler learns about bytes that fit within the stream's available capacity
     * but can't yet be written (because earlier bytes remain unknown), it should store them
     * internally until the gaps are filled in.
     *
     * The Reassembler should discard any bytes that lie beyond the stream's available capacity
     * (i.e., bytes that couldn't be written even if earlier gaps get filled in).
     *
     * The Reassembler should close the stream after writing the last byte.
     */
    void insert (uint64_t first_index , std::string data , bool is_last_substring , Writer &output);

    // How many bytes are stored in the Reassembler itself?
    uint64_t bytes_pending () const;


    uint64_t first_unacceptable_index (Writer &output);

    Reassembler () : store () , uf () {}

private:
    uint64_t first_unassembled_index = 0;//没push的第一个index
    uint64_t end_index = -1;
    uint64_t pending = 0; // 当前store里面字节总数
    std::unordered_map<int , char> store;

    UnionFind uf;
};



