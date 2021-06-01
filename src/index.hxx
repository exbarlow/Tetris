#pragma once

#include <ge211.hxx>

#include <iostream>

#include "enumcolor.hxx"

class Index
{
public:
    // Board positions will use 'int' coordinates.
    using Position = ge211::Posn<int>;

    // Default constructor
    explicit Index(Position position = {0, 0});
    // Sets posn_ of the index to the provided position
    void set_posn(Position);
    // Sets the occupied status of the index to true
    void set_occupied();
    // Sets the color of the index to 'color'
    void set_color(Enumcolor enumcolor);
    // Returns the position of the index
    Position posn();
    // Returns the occupied status of the index
    bool occupied();
    // Returns the color of the index
    Enumcolor color();


private:
    // The position of the index
    Position posn_;

    // Indicates whether or not the index is filled
    bool occupied_;

    // Indicates the color that this should index should be colored
    Enumcolor color_;

};