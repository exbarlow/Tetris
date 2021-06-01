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
        } else if (key == ge211::Key::code(' ')) {
            model_.set_current(model_.phantom_block_score());
            model_.actual_move();
        } else if (key == ge211::Key::code('c')) {
            model_.store();
        }
    }
}

// Called every frame
void
Controller::on_frame(double dt)
{
    model_.clear_line();
    view_.scorestring();
    model_.update_phantom();
    model_.count_down();
}


