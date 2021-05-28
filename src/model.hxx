#pragma once

#include <ge211.hxx>
#include <array>
#include <algorithm>

#include "index.hxx"
#include "block.hxx"
#include "board.hxx"


class Model
{
public:
    Model();



    std::array<std::array<Index, Board::width>, Board::height>
    board() const;

    void shift_down(int num);

    void add_score(int);

    void refill_block_bank();

    void bank_to_next(size_t);

    void next_to_current();

    void store();


private:
    std::array<std::array<Index, Board::width>, Board::height> board_;
    int score_;
    std::vector<Block> block_bank_;
    std::array<Block,3> up_next_;
    Block current_;
    Block stored_;
    bool can_swap_;


};
