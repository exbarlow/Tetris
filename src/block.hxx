#pragma once

#include "index.hxx"
#include "board.hxx"

class Block
{
public:
    Block(Enumcolor = Enumcolor::black);
    bool hits_bottom();
    bool hits_left();
    bool hits_right();
    void update_center();
    void shift_left();
    void shift_right();
    Block next_down();
    Block next_rotate();
    Enumcolor color();

private:
    std::vector<Index> boundbox_;
    ge211::Posn<double> center_;
    Enumcolor color_;
};