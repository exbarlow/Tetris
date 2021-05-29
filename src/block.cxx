#include "block.hxx"

// Constructor, constructs each block placing them at the top of the board
// (rounded to the left).
Block::Block(Enumcolor enumcolor)
        : center_(0, 0)
{
    switch (enumcolor) {
    case Enumcolor::black:
        color_ = Enumcolor::black;
        break;
    case Enumcolor::aqua:
        for (int j = 0; j < 4; ++j) {
            for (int i = (Board::width - 4) / 2; i < Board::width -
                                                     (Board::width -
                                                      4) / 2; ++i) {
                boundbox_.push_back(Index({i, j - 2}));
            }
        }
        for (size_t ind = 4; ind < 8; ++ind) {
            boundbox_[ind].set_occupied();
            boundbox_[ind].set_color(Enumcolor::aqua);
        }
        update_center();
        color_ = Enumcolor::aqua;
        break;
    case Enumcolor::blue:
        for (int j = 0; j < 3; ++j) {
            for (int i = (Board::width - 3) / 2; i < Board::width -
                                                     1 -
                                                     (Board::width -
                                                      4) /
                                                     2; ++i) {
                boundbox_.push_back(Index({i, j - 2}));
            }
        }
        boundbox_[0].set_occupied();
        boundbox_[0].set_color(Enumcolor::blue);
        for (size_t ind = 3; ind < 6; ++ind) {
            boundbox_[ind].set_occupied();
            boundbox_[ind].set_color(Enumcolor::blue);
        }
        update_center();
        color_ = Enumcolor::blue;
        break;
    case Enumcolor::orange:
        for (int j = 0; j < 3; ++j) {
            for (int i = (Board::width - 3) / 2; i < Board::width -
                                                     1 -
                                                     (Board::width -
                                                      4) /
                                                     2; ++i) {
                boundbox_.push_back(Index({i, j - 2}));
            }
        }
        boundbox_[2].set_occupied();
        boundbox_[2].set_color(Enumcolor::orange);
        for (size_t ind = 3; ind < 6; ++ind) {
            boundbox_[ind].set_occupied();
            boundbox_[ind].set_color(Enumcolor::orange);
        }
        update_center();
        color_ = Enumcolor::orange;
        break;
    case Enumcolor::yellow:
        for (int j = 0; j < 2; ++j) {
            for (int i = (Board::width - 2) / 2; i < Board::width -
                                                     (Board::width -
                                                      2) / 2; ++i) {
                boundbox_.push_back(Index({i, j - 2}));
            }
        }
        for (size_t ind = 0; ind < 4; ++ind) {
            boundbox_[ind].set_occupied();
            boundbox_[ind].set_color(Enumcolor::yellow);
        }
        update_center();
        color_ = Enumcolor::yellow;
        break;
    case Enumcolor::lime:
        for (int j = 0; j < 3; ++j) {
            for (int i = (Board::width - 3) / 2; i < Board::width -
                                                     1 -
                                                     (Board::width -
                                                      4) /
                                                     2; ++i) {
                boundbox_.push_back(Index({i, j - 2}));
            }
        }
        for (size_t ind = 1; ind < 5; ++ind) {
            boundbox_[ind].set_occupied();
            boundbox_[ind].set_color(Enumcolor::lime);
        }
        update_center();
        color_ = Enumcolor::lime;
        break;
    case Enumcolor::purple:
        for (int j = 0; j < 3; ++j) {
            for (int i = (Board::width - 3) / 2; i < Board::width -
                                                     1 -
                                                     (Board::width -
                                                      4) /
                                                     2; ++i) {
                boundbox_.push_back(Index({i, j - 2}));
            }
        }
        boundbox_[1].set_occupied();
        boundbox_[1].set_color(Enumcolor::purple);
        for (size_t ind = 3; ind < 6; ++ind) {
            boundbox_[ind].set_occupied();
            boundbox_[ind].set_color(Enumcolor::purple);
        }
        update_center();
        color_ = Enumcolor::purple;
        break;
    case Enumcolor::red:
        for (int j = 0; j < 3; ++j) {
            for (int i = (Board::width - 3) / 2; i < Board::width -
                                                     1 -
                                                     (Board::width -
                                                      4) /
                                                     2; ++i) {
                boundbox_.push_back(Index({i, j - 2}));
            }
        }
        boundbox_[0].set_occupied();
        boundbox_[0].set_color(Enumcolor::red);
        boundbox_[1].set_occupied();
        boundbox_[1].set_color(Enumcolor::red);
        boundbox_[4].set_occupied();
        boundbox_[4].set_color(Enumcolor::red);
        boundbox_[5].set_occupied();
        boundbox_[5].set_color(Enumcolor::red);
        update_center();
        color_ = Enumcolor::red;
        break;
    }
}

// Checks to see if a block is below the bottom
bool
Block::hits_bottom()
{
    for (Index i : boundbox_) {
        if (i.occupied()) {
            ge211::Posn<int> block_below = {i.posn().x, i.posn().y + 1};
            if (block_below.y >= Board::height) {
                return true;
            }
        }

    }
    return false;
}

// Checks to see if a block is left of the game board
bool
Block::hits_left()
{
    for (Index i : boundbox_) {
        if (i.occupied()) {
            ge211::Posn<int> block_left = {i.posn().x - 1, i.posn().y};
            if (block_left.x < 0) {
                return true;
            }
        }
    }
    return false;
}

// Checks to see if a block is to the right of the game board
bool
Block::hits_right()
{
    for (Index i : boundbox_) {
        if (i.occupied()) {
            ge211::Posn<int> block_right = {i.posn().x + 1, i.posn().y};
            if (block_right.x >= Board::width) {
                return true;
            }
        }
    }
    return false;
}

// Returns true if any part of the block is out of bounds
bool
Block::hits_rotate()
{
    for (Index i: boundbox_) {
        if (i.occupied()) {
            if (i.posn().x < 0 ||
                i.posn().x >= Board::width ||
                i.posn().y >= Board::height) {
                return true;
            }
        }
    }
    return false;
}

// Updates the center_ to be equal to the center of the block
void
Block::update_center()
{
    double size = 0;
    double x = 0;
    double y = 0;

    for (Index i : boundbox_) {
        ++size;
        x += i.posn().x;
        y += i.posn().y;
    }

    center_ = {x / size, y / size};
}

// Returns the state of the block after falling 1 spot down (+ y direction)
Block
Block::next_down()
{
    Block result(*this);

    for (Index& i : result.boundbox_) {
        i.set_posn({i.posn().x, i.posn().y + 1});
    }
    result.update_center();

    return result;

}

// Returns the state of the block after moving 1 spot to the left
Block
Block::next_left()
{
    Block result(*this);

    for (Index& i : result.boundbox_) {
        i.set_posn({i.posn().x - 1, i.posn().y});
    }
    result.update_center();

    return result;
}

// Returns the state of the block after moving 1 spot to the right
Block
Block::next_right()
{
    Block result(*this);

    for (Index& i : result.boundbox_) {
        i.set_posn({i.posn().x + 1, i.posn().y});
    }
    result.update_center();

    return result;
}

// Returns the state of the block after being rotated 90 degrees clockwise
Block
Block::next_rotate()
{
    Block to_rotate(*this);

    std::vector<ge211::Posn<double>> temp;

    for (Index& i : to_rotate.boundbox_) {
        temp.push_back(static_cast<ge211::Posn<double>>(i.posn()));
    }

    for (ge211::Posn<double>& posn : temp) {
        posn.x -= to_rotate.center_.x;
        posn.y -= to_rotate.center_.y;
    }

    for (ge211::Posn<double>& posn : temp) {
        double tempx = posn.x;
        posn.x = posn.y * -1;
        posn.y = tempx;
    }

    for (ge211::Posn<double>& posn : temp) {
        posn.x += to_rotate.center_.x;
        posn.y += to_rotate.center_.y;
    }

    for (size_t i = 0; i < to_rotate.boundbox_.size(); ++i) {
        to_rotate.boundbox_.at(i).set_posn({static_cast<int>(temp.at(i).x),
                                            static_cast<int>(temp.at(i).y)});
    }
    return to_rotate;
}

// Returns the Enumcolor of the block
Enumcolor
Block::color()
{
    return color_;
}

// Returns a copy of boundbox_ for view access
std::vector<Index>
Block::boundbox() const
{
    return boundbox_;
}


