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
          sans72({"sans.ttf", 72}),
          sans20({"sans.ttf", 20}),
          sans10({"sans.ttf", 10}),
          temp_game_over_sprite("Game over", sans72),
          score_text_sprite("Score:", sans20),
          score_num_sprite("0", sans20)
{ }

void
View::draw(Sprite_set& set)
{
    set.add_sprite(score_text_sprite, {initial_window_dimensions().width / 4,
                                       (Board::height + 2) * grid_size});
    set.add_sprite(score_num_sprite, {(initial_window_dimensions().width / 4)
                                      + grid_size * 3,
                                      (Board::height + 2) * grid_size});
    if (model_.game_over()) {
        set.add_sprite(temp_game_over_sprite, {0, 0}, 5);
    }
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

    for (Index ind : model_.current().boundbox()) {
        switch (ind.color()) {
        case Enumcolor::black:
            set.add_sprite(black_sprite,
                           {ind.posn().x * grid_size,
                            ind.posn().y * grid_size}, 0);
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

View::Dimensions
View::initial_window_dimensions() const
{
    return {grid_size * Board::width * 2, grid_size * (Board::height + 6)};
}


void
View::scorestring()
{
    ge211::Text_sprite::Builder builder(sans20);
    builder.message(to_string(model_.score()));
    score_num_sprite.reconfigure(builder);
}