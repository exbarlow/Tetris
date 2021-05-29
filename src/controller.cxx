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
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void // temporary
Controller::on_mouse_up(ge211::Mouse_button button, ge211::Posn<int> posn)
{
    if (button == ge211::Mouse_button::left) {
        model_.actual_move();
    } else if (button == ge211::Mouse_button::right) {
        model_.store();
    }
}

// Interprets button presses
void
Controller::on_key(ge211::Key key)
{
    if (!model_.game_over()) {
        if (key == ge211::Key::left()) {
            model_.shift_left();
        } else if (key == ge211::Key::right()) {
            model_.shift_right();
        } else if (key == ge211::Key::down()) {
            model_.actual_move();
            model_.add_score(1);
        } else if (key == ge211::Key::up()) {
            model_.rotate();
        }

    }
}

void
Controller::on_frame(double dt)
{
    model_.clear_line();
    view_.scorestring();
    //model_.actual_move();
}
