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
          vert_sprite({1, grid_size}, Color::from_rgba(0.5,0.5,0.5,1)),
          horiz_sprite({grid_size, 1}, Color::from_rgba(0.5,0.5,0.5,1))
{ }

void
View::draw(Sprite_set& set)
{
    for (size_t row = 0; row < model_.boardheight; ++row) {
        for (size_t col = 0; col < model_.boardwidth; ++col) {
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
                                          grid_size}, 1);
            set.add_sprite(horiz_sprite, {model_.board()[row][col].posn().x
                                          * grid_size,
                                          (model_.board()[row][col].posn().y
                                           + 1) * grid_size}, 1);
            set.add_sprite(vert_sprite, {model_.board()[row][col].posn().x *
                                         grid_size,
                                         model_.board()[row][col].posn().y *
                                         grid_size}, 1);
            set.add_sprite(vert_sprite, {(model_.board()[row][col].posn().x
                                          + 1) * grid_size,
                                         model_.board()[row][col].posn().y *
                                         grid_size}, 1);
        }

    }
}

View::Dimensions
View::window_dimensions() const
{
    return {grid_size * model_.boardwidth, grid_size * model_.boardheight};
}
