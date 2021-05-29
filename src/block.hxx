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

    bool hits_rotate();

    void update_center();

    Block next_down();

    Block next_left();

    Block next_right();

    Block next_rotate();

    Enumcolor color();

    std::vector<Index> boundbox() const;

private:

    std::vector<Index> boundbox_;
    ge211::Posn<double> center_;
    Enumcolor color_;
};