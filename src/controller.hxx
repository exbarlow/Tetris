#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;
    View::Dimensions window_dimensions() const;

    void on_mouse_up(ge211::Mouse_button, ge211::Posn<int>) override;


private:
    Model model_;
    View view_;
};
