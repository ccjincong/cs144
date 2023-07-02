#include "reassembler.hh"

using namespace std;

void Reassembler::insert (uint64_t first_index , string data , bool is_last_substring , Writer &output) {

    if ( data.size () > output.capacity_ )  //超过长度
        return;

    if ( first_index + data.size () < push_index ) //当前data和已经writer的字符串完全重复
        return;

    
    auto it = std::lower_bound (store.begin () , store.end () , make_pair (first_index , std::string ("")));


    if ( is_last_substring )
        output.close ();


    (void) it;
    (void) first_index;
    (void) data;
    (void) is_last_substring;
    (void) output;
}

uint64_t Reassembler::bytes_pending () const {
    // Your code here.
    return {};
}
