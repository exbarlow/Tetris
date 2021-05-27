#include "controller.hxx"

Controller::Controller()
        : view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

View::Dimensions
Controller::window_dimensions() const
{
    return view_.window_dimensions();
}

void // temporary
Controller::on_mouse_up(ge211::Mouse_button button, ge211::Posn<int> posn)
{
    if (button == ge211::Mouse_button::left) {
        model_.shift_down(1);
    }
}