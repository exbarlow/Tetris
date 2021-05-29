#pragma once

#include "model.hxx"

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// Determines the size that each index will take up
    static int const grid_size = 24;

    /// Constructs a view that knows about the given model.
    explicit View(Model const& model);

    /// Draws onto the screen
    void draw(ge211::Sprite_set& set);

    Dimensions initial_window_dimensions() const;

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
    ge211::Font const sans72;
    ge211::Font const sans20;
    ge211::Font const sans10;
    ge211::Text_sprite const temp_game_over_sprite;
    ge211::Text_sprite const score_text_sprite;
    ge211::Text_sprite score_num_sprite;


};
