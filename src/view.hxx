#pragma once

#include "model.hxx"

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Determines the size that each index will take up
    static int const grid_size = 24;

    /// Constructs a view that knows about the given model.
    explicit View(Model const& model);

    // Draws the stored block
    void draw_stored(ge211::Sprite_set& set);

    // Draws the current (falling) block
    void draw_current(ge211::Sprite_set& set);

    // Draws the current board state
    void draw_board(ge211::Sprite_set& set);

    // Draws the next 3 blocks that will fall
    void draw_next(ge211::Sprite_set& set);

    // Draws the game over screen
    void draw_gameover(ge211::Sprite_set& set);

    void draw_phantom(ge211::Sprite_set& set);

    /// Draws onto the screen
    void draw(ge211::Sprite_set& set);

    Dimensions initial_window_dimensions() const;

    // Converts current score into a string to be displayed
    void scorestring();


private:
    Model const& model_;

    ge211::Rectangle_sprite const black_sprite;
    ge211::Rectangle_sprite const aqua_sprite;
    ge211::Rectangle_sprite const blue_sprite;
    ge211::Rectangle_sprite const orange_sprite;
    ge211::Rectangle_sprite const yellow_sprite;
    ge211::Rectangle_sprite const lime_sprite;
    ge211::Rectangle_sprite const purple_sprite;
    ge211::Rectangle_sprite const red_sprite;
    ge211::Rectangle_sprite const vert_sprite;
    ge211::Rectangle_sprite const horiz_sprite;
    ge211::Rectangle_sprite const gameover_black_sprite;
    ge211::Rectangle_sprite const gameover_horiz;
    ge211::Rectangle_sprite const gameover_vert;
    ge211::Rectangle_sprite outline_horiz;
    ge211::Rectangle_sprite outline_vert;
    ge211::Font const sans45;
    ge211::Font const sans20;
    ge211::Text_sprite const gameover_text_sprite;
    ge211::Text_sprite const score_text_sprite;
    ge211::Text_sprite score_num_sprite;
    ge211::Text_sprite const stored_text_sprite;
    ge211::Text_sprite const next_text_sprite;
    ge211::Text_sprite const gameover_score_text_sprite;
    ge211::Text_sprite gameover_score_num_sprite;

};
