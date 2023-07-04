#include "reassembler.hh"
#include <fstream>

using namespace std;

void Reassembler::insert (uint64_t first_index , string data , bool is_last_substring , Writer &output) {

    //uf.update (first_unacceptable_index (output));

    if ( is_last_substring == true )
        end_index = first_index + data.size ();

    uint64_t l = std::max (first_unassembled_index , first_index); // 左边界
    uint64_t r = std::min (first_unacceptable_index (output) , first_index + data.size ()); //右边界

    for (uint64_t i = l; i < r; i++) {
        if ( store.count (i) == 0 ) {
            store[ i ] = data[ i - first_index ];
            pending++;
        }


    }

    std::string assemble_str = "";
    while (store.count (first_unassembled_index) == 1) {
        assemble_str += store[ first_unassembled_index ];
        store.erase (first_unassembled_index);
        first_unassembled_index++;
    }

    if ( assemble_str.size () > 0 ) {
        output.push (assemble_str);
        pending -= assemble_str.size ();
    }

    if ( first_unassembled_index == end_index )
        output.close ();
}


uint64_t Reassembler::bytes_pending () const {
    return pending;
}


uint64_t Reassembler::first_unacceptable_index (Writer &output) {
    return first_unassembled_index + output.available_capacity ();
}

