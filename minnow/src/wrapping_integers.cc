#include "wrapping_integers.hh"
#include <fstream>
#include <iostream>

using namespace std;

Wrap32 Wrap32::wrap (uint64_t n , Wrap32 zero_point) {

    return Wrap32{ (zero_point + (uint32_t) n) };
}

uint64_t Wrap32::unwrap (Wrap32 zero_point , uint64_t checkpoint) const {
    // Your code here.
    uint32_t len = raw_value_ - zero_point.raw_value_;
    uint32_t checkpoint_32 = checkpoint;  // 直接截取后面的

    uint64_t seno = checkpoint - checkpoint_32 + len;

    if ( checkpoint_32 > len && checkpoint_32 - len > uint32_t (1 << 31))
        seno += (1ull << 32);

    if ( checkpoint_32 < len && len - checkpoint_32 > uint32_t (1 << 31) && seno > (1ull << 32))
        seno -= (1ull << 32);

    return seno;

}
