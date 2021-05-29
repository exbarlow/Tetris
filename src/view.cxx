#include "view.hxx"

using namespace ge211;

View::View(Model const& model)
        : model_(model),
          black_sprite({grid_size, grid_size}, Color::black()),
          aqua_sprite({grid_size, grid_size}, Color::from_rgba(0, 1, 1, 1)),
          blue_sprite({grid_size, grid_size}, Color::from_rgba(0, 0, 1, 1)),
          orange_sprite({grid_size, grid_size},
                        Color::from_rgba(1, 0.5, 0, 1)),
          yellow_sprite({grid_size, grid_size},
                        Color::from_rgba(1, 1, 0, 1)),
          lime_sprite({grid_size, grid_size}, Color::from_rgba(0.2, 1, 0.2, 1)),
          purple_sprite({grid_size, grid_size},
                        Color::from_rgba(0.5, 0, 1, 1)),
          red_sprite({grid_size, grid_size}, Color::from_rgba(1, 0, 0,
                                                              1)),
          vert_sprite({1, grid_size}, Color::from_rgba(0.5, 0.5, 0.5, 1)),
          horiz_sprite({grid_size, 1}, Color::from_rgba(0.5, 0.5, 0.5, 1)),
          gameover_black_sprite({initial_window_dimensions().width * 3 / 4,
                                 initial_window_dimensions().height * 19 / 25},
                                Color::black()),
          gameover_horiz({4, initial_window_dimensions().height * 19 / 25},
                         Color::white()),
          gameover_vert({initial_window_dimensions().width *
                         3 / 4, 4}, Color::white()),
          outline_horiz({grid_size, 1}, Color::from_rgba(0.5, 0.5, 0.5, 1)),
          outline_vert({1, grid_size}, Color::from_rgba(0.5, 0.5, 0.5, 1)),
          sans45({"sans.ttf", 45}),
          sans20({"sans.ttf", 20}),
          gameover_text_sprite("GAME OVER", sans45),
          score_text_sprite("Score:", sans20),
          score_num_sprite("0", sans20),
          stored_text_sprite("Stored:", sans20),
          next_text_sprite("Next:", sans20),
          gameover_score_text_sprite("Score:", sans45),
          gameover_score_num_sprite("0", sans45)
{
}

void
View::draw_stored(Sprite_set& set)
{
    set.add_sprite(stored_text_sprite, {1 * grid_size, Board::height *
                                                       grid_size}, 4);
    switch (model_.stored().color()) {
    case Enumcolor::black:
        break;
    case Enumcolor::aqua:
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                if (row == 1) {
                    set.add_sprite(aqua_sprite,
                                   {col * grid_size + grid_size / 2,
                                    (Board::height + 1 + row)
                                    * grid_size + grid_size / 3});
                }
            }
        }
        break;
    case Enumcolor::blue:
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if ((row == 0 && col == 0) || row == 1) {
                    set.add_sprite(blue_sprite,
                                   {col * grid_size + grid_size * 3 / 4,
                                    (Board::height + 1 +
                                     row) * grid_size + grid_size / 2});
                }
            }
        }
        break;
    case Enumcolor::orange:
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if ((row == 0 && col == 2) || row == 1) {
                    set.add_sprite(orange_sprite,
                                   {col * grid_size + grid_size * 3 / 4,
                                    (Board::height + 1 +
                                     row) * grid_size + grid_size / 2});
                }
            }
        }
        break;
    case Enumcolor::yellow:
        for (int row = 0; row < 2; ++row) {
            for (int col = 0; col < 2; ++col) {
                set.add_sprite(yellow_sprite, {col * grid_size
                                               + grid_size * 4 / 3,
                                               (Board::height + row) *
                                               grid_size + grid_size * 3 / 2});
            }
        }
        break;
    case Enumcolor::lime:
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if ((row == 0 && 1 <= col) || (row == 1 && col <= 1)) {
                    set.add_sprite(lime_sprite,
                                   {col * grid_size + grid_size * 3 / 4,
                                    (Board::height + 1 + row)
                                    * grid_size + grid_size / 2});
                }

            }
        }
        break;
    case Enumcolor::purple:
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if ((row == 1) || (row == 0 && col == 1)) {
                    set.add_sprite(purple_sprite,
                                   {col * grid_size + grid_size * 3 / 4,
                                    (Board::height + 1 + row)
                                    * grid_size + grid_size / 2});
                }
            }
        }
        break;
    case Enumcolor::red:
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if ((row == 0 && col < 2) || (row == 1 && col > 0)) {
                    set.add_sprite(red_sprite,
                                   {col * grid_size + grid_size * 3 / 4,
                                    (Board::height + 1 + row)
                                    * grid_size + grid_size / 2});
                }
            }
        }
        break;

    }
}

void
View::draw_current(Sprite_set& set)
{
    for (Index ind : model_.current().boundbox()) {
        switch (ind.color()) {
        case Enumcolor::black:
            set.add_sprite(black_sprite,
                           {ind.posn().x * grid_size,
                            ind.posn().y * grid_size}, -1);
            break;
        case Enumcolor::aqua:
            set.add_sprite(aqua_sprite,
                           {ind.posn().x * grid_size,
                            ind.posn().y * grid_size}, 2);
            break;
        case Enumcolor::blue:
            set.add_sprite(blue_sprite,
                           {ind.posn().x * grid_size,
                            ind.posn().y * grid_size}, 2);
            break;
        case Enumcolor::orange:
            set.add_sprite(orange_sprite,
                           {ind.posn().x * grid_size,
                            ind.posn().y * grid_size}, 2);
            break;
        case Enumcolor::yellow:
            set.add_sprite(yellow_sprite,
                           {ind.posn().x * grid_size,
                            ind.posn().y * grid_size}, 2);
            break;
        case Enumcolor::lime:
            set.add_sprite(lime_sprite,
                           {ind.posn().x * grid_size,
                            ind.posn().y * grid_size}, 2);
            break;
        case Enumcolor::purple:
            set.add_sprite(purple_sprite,
                           {ind.posn().x * grid_size,
                            ind.posn().y * grid_size}, 2);
            break;
        case Enumcolor::red:
            set.add_sprite(red_sprite,
                           {ind.posn().x * grid_size,
                            ind.posn().y * grid_size}, 2);
            break;

        }
    }
}

void
View::draw_board(ge211::Sprite_set& set)
{
    for (size_t row = 0; row < Board::height; ++row) {
        for (size_t col = 0; col < Board::width; ++col) {
            switch (model_.board()[row][col].color()) {
            case Enumcolor::black:
                set.add_sprite(black_sprite,
                               {model_.board()[row][col].posn().x * grid_size,
                                model_.board()[row][col].posn().y * grid_size},
                               0);
                break;
            case Enumcolor::aqua:
                set.add_sprite(aqua_sprite,
                               {model_.board()[row][col].posn().x * grid_size,
                                model_.board()[row][col].posn().y * grid_size},
                               0);
                break;
            case Enumcolor::blue:
                set.add_sprite(blue_sprite,
                               {model_.board()[row][col].posn().x * grid_size,
                                model_.board()[row][col].posn().y * grid_size},
                               0);
                break;
            case Enumcolor::orange:
                set.add_sprite(orange_sprite,
                               {model_.board()[row][col].posn().x * grid_size,
                                model_.board()[row][col].posn().y * grid_size},
                               0);
                break;
            case Enumcolor::yellow:
                set.add_sprite(yellow_sprite,
                               {model_.board()[row][col].posn().x * grid_size,
                                model_.board()[row][col].posn().y * grid_size},
                               0);
                break;
            case Enumcolor::lime:
                set.add_sprite(lime_sprite,
                               {model_.board()[row][col].posn().x * grid_size,
                                model_.board()[row][col].posn().y * grid_size},
                               0);
                break;
            case Enumcolor::purple:
                set.add_sprite(purple_sprite,
                               {model_.board()[row][col].posn().x * grid_size,
                                model_.board()[row][col].posn().y * grid_size},
                               0);
                break;
            case Enumcolor::red:
                set.add_sprite(red_sprite,
                               {model_.board()[row][col].posn().x * grid_size,
                                model_.board()[row][col].posn().y * grid_size},
                               0);
                break;
            }
            set.add_sprite(horiz_sprite, {model_.board()[row][col].posn().x *
                                          grid_size,
                                          model_.board()[row][col].posn().y *
                                          grid_size}, 3);
            set.add_sprite(horiz_sprite, {model_.board()[row][col].posn().x
                                          * grid_size,
                                          (model_.board()[row][col].posn().y
                                           + 1) * grid_size}, 3);
            set.add_sprite(vert_sprite, {model_.board()[row][col].posn().x *
                                         grid_size,
                                         model_.board()[row][col].posn().y *
                                         grid_size}, 3);
            set.add_sprite(vert_sprite, {(model_.board()[row][col].posn().x
                                          + 1) * grid_size,
                                         model_.board()[row][col].posn().y *
                                         grid_size}, 3);
        }

    }
}

void
View::draw_next(Sprite_set& set)
{
    set.add_sprite(next_text_sprite, {(Board::width + 2) * grid_size, 0});
    for (int i = 0; i < 3; ++i) {
        switch (model_.up_next().at(i).color()) {
        case Enumcolor::black:
            break;
        case Enumcolor::aqua:
            for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 4; ++col) {
                    if (row == 1) {
                        set.add_sprite(aqua_sprite,
                                       {(Board::width + 1 + col) * grid_size,
                                        (row + 1) * grid_size +
                                        i * 5 * grid_size});
                    }
                }
            }
            break;
        case Enumcolor::blue:
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    if ((row == 0 && col == 0) || row == 1) {
                        set.add_sprite(blue_sprite,
                                       {(Board::width + 1 + col) * grid_size
                                        + grid_size * 1 / 3,
                                        (row + 1 + i * 5) * grid_size +
                                        grid_size * 2 / 3});
                    }
                }
            }
            break;
        case Enumcolor::orange:
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    if ((row == 0 && col == 2) || row == 1) {
                        set.add_sprite(orange_sprite,
                                       {(Board::width + 1 + col) * grid_size
                                        + grid_size * 1 / 3,
                                        (row + 1 + i * 5) * grid_size +
                                        grid_size * 2 / 3});
                    }
                }
            }
            break;
        case Enumcolor::yellow:
            for (int row = 0; row < 2; ++row) {
                for (int col = 0; col < 2; ++col) {
                    set.add_sprite(yellow_sprite,
                                   {(Board::width + 2 + col) * grid_size,
                                    (row + 1 + i * 5) * grid_size +
                                    grid_size * 2 / 3});
                }
            }
            break;
        case Enumcolor::lime:
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    if ((row == 0 && 1 <= col) || (row == 1 && col <= 1)) {
                        set.add_sprite(lime_sprite,
                                       {(Board::width + 1 + col) * grid_size
                                        + grid_size * 1 / 3,
                                        (row + 1 + i * 5) * grid_size +
                                        grid_size * 2 / 3});
                    }

                }
            }
            break;
        case Enumcolor::purple:
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    if ((row == 1) || (row == 0 && col == 1)) {
                        set.add_sprite(purple_sprite,
                                       {(Board::width + 1 + col) * grid_size
                                        + grid_size * 1 / 3,
                                        (row + 1 + i * 5) * grid_size +
                                        grid_size * 2 / 3});
                    }
                }
            }
            break;
        case Enumcolor::red:
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    if ((row == 0 && col < 2) || (row == 1 && col > 0)) {
                        set.add_sprite(red_sprite,
                                       {(Board::width + 1 + col) * grid_size
                                        + grid_size * 1 / 3,
                                        (row + 1 + i * 5) * grid_size +
                                        grid_size * 2 / 3});
                    }
                }
            }
            break;
        }
    }
}

void
View::draw_gameover(ge211::Sprite_set& set)
{
    set.add_sprite(gameover_text_sprite,
                   {initial_window_dimensions().width / 8 + grid_size * 6 / 16,
                    initial_window_dimensions().height * 3 / 25}, 11);
    set.add_sprite(gameover_black_sprite,
                   {initial_window_dimensions().width / 8,
                    initial_window_dimensions().height * 3 / 25}, 10);
    set.add_sprite(gameover_horiz,
                   {initial_window_dimensions().width / 8,
                    initial_window_dimensions().height * 3 / 25}, 12);
    set.add_sprite(gameover_vert,
                   {initial_window_dimensions().width / 8,
                    initial_window_dimensions().height * 22 / 25 - 4}, 12);
    set.add_sprite(gameover_vert,
                   {initial_window_dimensions().width / 8,
                    initial_window_dimensions().height * 3 / 25}, 12);
    set.add_sprite(gameover_horiz,
                   {initial_window_dimensions().width * 7 / 8 - 4,
                    initial_window_dimensions().height * 3 / 25}, 12);
    set.add_sprite(gameover_score_text_sprite,
                   {initial_window_dimensions().width * 3 / 8 - grid_size,
                    initial_window_dimensions().height * 11 / 25}, 11);
    set.add_sprite(gameover_score_num_sprite,
                   {initial_window_dimensions().width * 3 / 8,
                    initial_window_dimensions().height * 13 / 25}, 11);
}

void
View::draw_phantom(ge211::Sprite_set& set)
{
    for (Index i : model_.phantom().boundbox()) {
        if (i.occupied()) {
            switch (i.color()) {
            case Enumcolor::black:
                break;
            case Enumcolor::aqua:
                outline_horiz.recolor(Color::from_rgba(0, 1, 1, 1));
                outline_vert.recolor(Color::from_rgba(0, 1, 1, 1));
                break;
            case Enumcolor::blue:
                outline_horiz.recolor(Color::from_rgba(0, 0, 1, 1));
                outline_vert.recolor(Color::from_rgba(0, 0, 1, 1));
                break;
            case Enumcolor::orange:
                outline_horiz.recolor(Color::from_rgba(1, 0.5, 0, 1));
                outline_vert.recolor(Color::from_rgba(1, 0.5, 0, 1));
                break;
            case Enumcolor::yellow:
                outline_horiz.recolor(Color::from_rgba(1, 1, 0, 1));
                outline_vert.recolor(Color::from_rgba(1, 1, 0, 1));
                break;
            case Enumcolor::lime:
                outline_horiz.recolor(Color::from_rgba(0.2, 1, 0.2, 1));
                outline_vert.recolor(Color::from_rgba(0.2, 1, 0.2, 1));
                break;
            case Enumcolor::purple:
                outline_horiz.recolor(Color::from_rgba(0.5, 0, 1, 1));
                outline_vert.recolor(Color::from_rgba(0.5, 0, 1, 1));
                break;
            case Enumcolor::red:
                outline_horiz.recolor(Color::from_rgba(1, 0, 0, 1));
                outline_vert.recolor(Color::from_rgba(1, 0, 0, 1));
                break;

            }
            set.add_sprite(outline_vert, {i.posn().x * grid_size,
                                          i.posn().y * grid_size}, 4);
            set.add_sprite(outline_vert, {(i.posn().x + 1) * grid_size,
                                          i.posn().y * grid_size}, 4);
            set.add_sprite(outline_horiz, {i.posn().x * grid_size,
                                           i.posn().y * grid_size}, 4);
            set.add_sprite(outline_horiz,
                           {i.posn().x * grid_size,
                            (i.posn().y + 1) * grid_size},
                           4);
        }
    }
}

void
View::draw(Sprite_set& set)
{


    draw_stored(set);

    draw_current(set);

    draw_board(set);

    draw_next(set);

    draw_phantom(set);

    if (model_.game_over()) {
        draw_gameover(set);
    } else {
        set.add_sprite(score_text_sprite,
                       {initial_window_dimensions().width / 3,
                        (Board::height + 2) * grid_size});
        set.add_sprite(score_num_sprite,
                       {(initial_window_dimensions().width / 3)
                        + grid_size * 3,
                        (Board::height + 2) * grid_size});
    }

}

View::Dimensions
View::initial_window_dimensions() const
{
    return {grid_size * Board::width * 2 - 4 * grid_size, grid_size *
                                                          (Board::height + 5)};
}


void
View::scorestring()
{
    ge211::Text_sprite::Builder small_builder(sans20);
    ge211::Text_sprite::Builder large_builder(sans45);
    small_builder.message(to_string(model_.score()));
    large_builder.message(to_string(model_.score()));
    score_num_sprite.reconfigure(small_builder);
    gameover_score_num_sprite.reconfigure(large_builder);
}