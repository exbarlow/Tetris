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

    // Returns a copy of board_
    std::array<std::array<Index, Board::width>, Board::height>
    board() const;
    // Shifts the entire board down 'num' rows
    void shift_down(size_t num);
    // Adds 'num' to the current score
    void add_score(int num);
    // Refills block_bank with one block of each type (except black)
    void refill_block_bank();
    // If block_bank_ is empty, refills it. Otherwise, pulls a random block from
    // block_bank_ into the last spot in up_next_
    void bank_to_next(size_t);
    // Moves the first index of up_next_ to current_, then calls
    // Model::bank_to_next()
    void next_to_current();
    // Stores a block if it is allowed; if a block is already stored it will swap
    // them
    void store();
    // Returns a copy of up_next_ for view access
    std::array<Block, 3> up_next() const;
    // Returns a copy of current_ for view access
    Block current() const;
    // Returns a copy of stored_ for view access
    Block stored() const;
    // Shifts current_ one block to the right if possible
    void shift_right();
    // Shifts current_ one block to the left if possible
    void shift_left();
    // Checks to see if a block collides_down with placed blocks or the bottom
    bool collides_down(Block block);
    // Checks to see if current_ will collide on the left if it moves left
    bool collides_left();
    // Checks to see if current_ will collide on the right if it moves right
    bool collides_right();
    // Checks to see if current_ will collide if it is rotated
    bool collides_rotate();
    // Returns the lowest (most positive) y coordinate of 'block'
    int lowest_occupied(Block block);
    // If game is not over, either moves the block down or, if it collides_down,
    // either sets the game over (if board has reached the top) or sets the block
    // in place and puts a new block in to play
    void actual_move(Block& block);
    // Calls actual_move() on current_
    void actual_move();
    // Rotates the block 90 degrees clockwise if possible
    void rotate();
    // Returns true if the game is over
    bool game_over() const;
    // Clears a line if it is full
    void clear_line();
    // Returns the score
    int score() const;
    // Returns a phantom block at the position that current will fall if left
    // untouched, and adds 2* the number of places that the block has moved to
    // the score
    Block phantom_block_score();
    // Returns a phantom block at the position that current will fall if left
    // untouched
    Block phantom_block_noscore();
    // Sets phantom_ to be the phantom block generated by phantom_block_noscore()
    void update_phantom();
    // Returns the phantom block
    Block phantom() const;
    // Assigns 'block' to current
    void set_current(Block block);
    // Counts down coundown_
    void count_down();

#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif

private:
    // The board, each value is an Index
    std::array<std::array<Index, Board::width>, Board::height> board_;
    // The score
    int score_;
    // A vector of blocks that initially contains one of each type of
    // tetronimo, is slowly depleted then replenished
    std::vector<Block> block_bank_;
    // The next three blocks, is replenished by pulling randomly from
    // block_bank_
    std::array<Block, 3> up_next_;
    // The current (falling) tetronimo
    Block current_;
    // The stored block
    Block stored_;
    // True when a block can be stored, false when not
    bool can_swap_;
    // True when the game is over
    bool game_over_;
    // A block that represents the current block's landing position
    Block phantom_;
    // A number that counts down, serves as speed/difficulty control
    int countdown_;

};
