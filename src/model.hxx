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

    void shift_down(size_t num);

    void add_score(int);

    void refill_block_bank();

    void bank_to_next(size_t);

    void next_to_current();

    void store();

    std::array<Block,3> up_next() const;

    Block current() const;

    Block stored() const;

    void shift_right();

    void shift_left();

    bool collides_down();

    bool collides_left();

    bool collides_right();

    bool collides_rotate();

    int lowest_occupied(Block block);

    void actual_move();

    void rotate();

    bool game_over() const;

    void clear_line();

    int score() const;



private:
    std::array<std::array<Index, Board::width>, Board::height> board_;
    int score_;
    std::vector<Block> block_bank_;
    std::array<Block,3> up_next_;
    Block current_;
    Block stored_;
    bool can_swap_;
    bool game_over_;
    bool collided_;


};
