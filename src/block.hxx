#pragma once

#include "index.hxx"
#include "board.hxx"

class Block
{
public:
    // Default constructor
    Block(Enumcolor = Enumcolor::black);
    // Checks to see if a block is below the bottom
    bool hits_bottom();
    // Checks to see if a block is left of the game board
    bool hits_left();
    // Checks to see if a block is to the right of the game board
    bool hits_right();
    // Returns true if any part of the block is out of bounds
    bool hits_rotate();
    // Updates the center_ to be equal to the center of the block
    void update_center();
    // Returns the state of the block after falling 1 spot down (+ y direction)
    Block next_down();
    // Returns the state of the block after moving 1 spot to the left
    Block next_left();
    // Returns the state of the block after moving 1 spot to the right
    Block next_right();
    // Returns the state of the block after being rotated 90 degrees clockwise
    Block next_rotate();
    // Returns the Enumcolor of the block
    Enumcolor color();
    // Returns a copy of boundbox_ for view access
    std::vector<Index> boundbox() const;
    // Returns collided_
    bool collided();
    // Sets collided_ to true
    void set_collided();

private:

    // Contains a vector of all the "Index"s that compose the block
    std::vector<Index> boundbox_;
    // The center of the block, around which it is rotated
    ge211::Posn<double> center_;
    // The color of the block
    Enumcolor color_;
    // Returns true if the block has collided with a block below or the
    // bottom of the grid
    bool collided_;
};