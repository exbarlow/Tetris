#pragma once

#include <ge211.hxx>

#include <iostream>

#include "enumcolor.hxx"

class Index
{
public:
    /// Board positions will use 'int' coordinates.
    using Position = ge211::Posn<int>;

    /// Default constructor
    explicit Index(Position position = {0,0});

    void set_posn(Position);

    void set_occupied();

    void set_unoccupied();

    void set_color(Enumcolor enumcolor);

    Position posn();

    bool occupied();

    Enumcolor color();


private:
    // The position of the index
    Position posn_;

    // Indicates whether or not the index is filled
    bool occupied_;

    // Indicates the color that this should index should be colored
    Enumcolor color_;

};