#pragma once

#include <ge211.hxx>
#include <array>
#include <algorithm>

#include "index.hxx"

class Model
{
public:
    Model();
    static constexpr int boardwidth = 10;
    static constexpr int boardheight = 20;


    std::array<std::array<Index, boardwidth>, boardheight>
    board() const;

    void shift_down(int num);

    void add_score(int);


private:
    std::array<std::array<Index, boardwidth>, boardheight> board_;
    int score_;


};

//std::move(&board[0], &board[i], &board[n]);
    /* Representing the Board:
     * an array of arrays
     *  - coordinates?
     *  - bool if it has a block
     *  - color
     *
     *
     *
     *   Falling blocks
     *   - positions
     *   - color
     *   -
     *
     *
     *   struct index
     *   {
     *   ge211::Posn<something> coords
     *   bool occupied?
     *   ge211::Color --> is this a thing?
     *   }
     *
     *   index board[10][20];
     *
     *   for (size_t i = 0; i < 10; ++i) {
            for (size_t j = 0; j < 20; ++j) {

                board[i][j].coords = {i,j};
                board[i][j].occupied = false;
                board[i][j].color = ge211::Color::Black?;
                }
            }


     struct block
     {
     index matrix[x][y]
     midpoint
     top left?

};

     */