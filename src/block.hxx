#pragma once

#include "index.hxx"

class Block
{
public:
    void shift_block(num);
private:
    std::array<Index> boundbox_;
    Position center_;
};