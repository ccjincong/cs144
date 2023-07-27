#pragma once

#include "byte_stream.hh"

#include <string>
class Reassembler {
public:
    void insert (uint64_t first_index , std::string data , bool is_last_substring , Writer &output);

    // first_index ： 字符串第一个字符的index
    // data： 数据
    // is_last_substring： 是否是最后一个字符串
    uint64_t bytes_pending () const;


    uint64_t first_unacceptable_index (Writer &output);

    Reassembler () : store () , flag () {}

    uint64_t get_first_unassembled_index();

private:
    uint64_t first_unassembled_index = 0;//没push的第一个index
    uint64_t end_index = -1;
    uint64_t pending = 0; // 当前store里面字节总数

    uint64_t ptr = 0; //循环缓冲区起始位置
    std::vector<char> store;
    std::vector<bool> flag;

};



