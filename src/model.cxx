#include "model.hxx"

Model::Model()
        : score_(0),
          can_swap_(true),
          game_over_(false),
          countdown_(250)
{
    for (int row = 0; row < Board::height; ++row) {
        for (int col = 0; col < Board::width; ++col) {
            board_[row][col] = Index({col, row});
        }
    }

    stored_ = Block();
    refill_block_bank();
    bank_to_next(0);
    bank_to_next(1);
    bank_to_next(2);
    next_to_current();
    actual_move();
    actual_move();
    update_phantom();
}

// Returns a copy of board_
std::array<std::array<Index, Board::width>, Board::height>
Model::board() const
{
    return board_;
}

// Shifts the entire board down 'num' rows
void
Model::shift_down(size_t num)
{
    std::copy_backward(&board_[0], &board_[num],
                       &board_[num + 1]);

    for (size_t row = 0; row < Board::height - 1 - num; ++row) {
        for (size_t col = 0; col < Board::width; ++col) {
            board_[row][col] = Index();
        }
    }

    for (int row = 0; row < Board::height; ++row) {
        for (int col = 0; col < Board::width; ++col) {
            board_[row][col].set_posn({col, row});
        }
    }

}

// Adds 'num' to the current score
void
Model::add_score(int num)
{
    score_ += num;
}

// Refills block_bank with one block of each type (except black)
void
Model::refill_block_bank()
{
    block_bank_.push_back(Block(Enumcolor::aqua));
    block_bank_.push_back(Block(Enumcolor::blue));
    block_bank_.push_back(Block(Enumcolor::orange));
    block_bank_.push_back(Block(Enumcolor::yellow));
    block_bank_.push_back(Block(Enumcolor::lime));
    block_bank_.push_back(Block(Enumcolor::purple));
    block_bank_.push_back(Block(Enumcolor::red));
}

// If block_bank_ is empty, refills it. Otherwise, pulls a random block from
// block_bank_ into the last spot in up_next_
void
Model::bank_to_next(size_t ind)
{
    if (block_bank_.empty()) {
        refill_block_bank();
    }
    int picker = rand() % block_bank_.size();
    Block picked = block_bank_.at(picker);
    up_next_.at(ind) = picked;
    block_bank_.at(picker) = block_bank_.back();
    block_bank_.pop_back();
}

// Moves the first index of up_next_ to current_, then calls
// Model::bank_to_next()
void
Model::next_to_current()
{
    current_ = up_next_.at(0);
    up_next_.at(0) = up_next_.at(1);
    up_next_.at(1) = up_next_.at(2);
    bank_to_next(2);
    current_.set_collided();
}

// Stores a block if it is allowed; if a block is already stored it will swap
// them
void
Model::store()
{
    if (can_swap_) {
        if (stored_.color() == Enumcolor::black) {
            stored_ = Block(current_.color());
            next_to_current();
        } else {
            Enumcolor color = current_.color();
            current_ = Block(stored_.color());
            stored_ = Block(color);
            actual_move();
            actual_move();
        }
        can_swap_ = false;
    }
}

// Returns a copy of up_next_ for view access
std::array<Block, 3>
Model::up_next() const
{
    return up_next_;
}

// Returns a copy of current_ for view access
Block
Model::current() const
{
    return current_;
}

// Returns a copy of stored_ for view access
Block
Model::stored() const
{
    return stored_;
}

// Shifts current_ one block to the right if possible
void
Model::shift_right()
{
    if (!game_over_) {
        Block spec_block = current_.next_right();
        if (!collides_right()) {
            current_ = spec_block;
        }
    }
}

// Shifts current_ one block to the left if possible
void
Model::shift_left()
{
    if (!game_over_) {
        Block spec_block = current_.next_left();
        if (!collides_left()) {
            current_ = spec_block;
        }
    }
}

// Checks to see if a block collides_down with placed blocks or the bottom
bool
Model::collides_down(Block block)
{
    if (block.hits_bottom()) {
        return true;
    }

    Block spec_block = block.next_down();
    for (Index i : spec_block.boundbox()) {
        if (i.occupied()) {
            for (size_t row = 0; row < Board::height; ++row) {
                for (size_t col = 0; col < Board::width; ++col) {
                    if (i.posn() == board_[row][col].posn()) {
                        if (board_[row][col].occupied()) {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

// Checks to see if current_ will collide on the left if it moves left
bool
Model::collides_left()
{
    if (current_.hits_left()) {
        return true;
    }

    Block spec_block_left = current_.next_left();
    for (Index i : spec_block_left.boundbox()) {
        if (i.occupied()) {
            for (size_t row = 0; row < Board::height; ++row) {
                for (size_t col = 0; col < Board::width; ++col) {
                    if (i.posn() == board_[row][col].posn()) {
                        if (board_[row][col].occupied()) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Checks to see if current_ will collide on the right if it moves right
bool
Model::collides_right()
{
    if (current_.hits_right()) {
        return true;
    }
    Block spec_block_right = current_.next_right();
    for (Index i : spec_block_right.boundbox()) {
        if (i.occupied()) {
            for (size_t row = 0; row < Board::height; ++row) {
                for (size_t col = 0; col < Board::width; ++col) {
                    if (i.posn() == board_[row][col].posn()) {
                        if (board_[row][col].occupied()) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Checks to see if current_ will collide if it is rotated
bool
Model::collides_rotate()
{
    Block spec_block_rotate = current_.next_rotate();
    if (spec_block_rotate.hits_rotate()) {
        return true;
    }

    for (Index i : spec_block_rotate.boundbox()) {
        if (i.occupied()) {
            for (size_t row = 0; row < Board::height; ++row) {
                for (size_t col = 0; col < Board::width; ++col) {
                    if (i.posn() == board_[row][col].posn()) {
                        if (board_[row][col].occupied()) {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

// Returns the lowest (most positive) y coordinate of 'block'
int
Model::lowest_occupied(Block block)
{
    int result = -2;
    for (Index i : block.boundbox()) {
        if (i.occupied()) {
            if (i.posn().y > -2) {
                result = i.posn().y;
            }
        }
    }
    return result;
}

// If game is not over, either moves the block down or, if it collides_down,
// either sets the game over (if board has reached the top) or sets the block
// in place and puts a new block in to play
void
Model::actual_move(Block& block)
{
    if (!game_over_) {
        Block spec_block = block.next_down();
        if (!collides_down(block)) {
            block = spec_block;
        } else if (lowest_occupied(block) < 0) {
            game_over_ = true;
        } else if (!block.collided()) {
            block.set_collided();
        } else {
            for (Index i : block.boundbox()) {
                if (i.occupied()) {
                    for (size_t row = 0; row < Board::height; ++row) {
                        for (size_t col = 0; col < Board::width; ++col) {
                            if (i.posn() == board_[row][col].posn()) {
                                board_[row][col].set_occupied();
                                board_[row][col].set_color(i.color());
                            }
                        }
                    }
                }
            }
            can_swap_ = true;
            next_to_current();
        }
    }
}

// Calls actual_move() on current_
void
Model::actual_move()
{
    actual_move(current_);
}


// Rotates the block 90 degrees clockwise if possible
void
Model::rotate()
{
    if (!game_over_) {
        Block spec_block = current_.next_rotate();
        if (!collides_rotate()) {
            current_ = spec_block;
        }
    }
}

// Returns true if the game is over
bool
Model::game_over() const
{
    return game_over_;
}

// Clears a line if it is full
void
Model::clear_line()
{
    for (size_t row = 0; row < Board::height; ++row) {
        bool full = true;
        for (size_t col = 0; col < Board::width; ++col) {
            if (!board_[row][col].occupied()) {
                full = false;
            }
        }
        if (full) {
            shift_down(row);
            add_score(100);
        }

    }
}

// Returns the score
int
Model::score() const
{
    return score_;
}


// Returns a phantom block at the position that current will fall if left
// untouched, and adds 2* the number of places that the block has moved to
// the score
Block
Model::phantom_block_score()
{


    Block phantom_block = current_;
    if (lowest_occupied(phantom_block) >= 0) {
        while (!collides_down(phantom_block)) {
            actual_move(phantom_block);
            add_score(2);
        }
    }

    return phantom_block;
}


// Returns a phantom block at the position that current will fall if left
// untouched
Block
Model::phantom_block_noscore()
{
    Block phantom_block = current_;
    if (lowest_occupied(phantom_block) >= 0) {
        while (!collides_down(phantom_block)) {
            actual_move(phantom_block);
        }
    }
    return phantom_block;
}

// Sets phantom_ to be the phantom block generated by phantom_block_noscore()
void
Model::update_phantom()
{
    phantom_ = phantom_block_noscore();
}

// Returns the phantom block
Block
Model::phantom() const
{
    return phantom_;
}

// Assigns 'block' to current
void
Model::set_current(Block block)
{
    current_ = block;
}

// Counts down coundown_
void
Model::count_down()
{
    if (countdown_ > 0) {
        countdown_ -= 1;
    } else if (countdown_ == 0) {
        actual_move();
        if (score_ > 5000) {
            countdown_ = 6;
        } else if (score_ > 4000) {
            countdown_ = 8;
        } else if (score_ > 3000) {
            countdown_ = 10;
        } else if (score_ > 2000) {
            countdown_ = 14;
        } else if (score_ > 1000) {
            countdown_ = 16;
        } else if (score_ > 500) {
            countdown_ = 22;
        } else if (score_ > 100) {
            countdown_ = 26;
        } else if (score_ >= 0) {
            countdown_ = 30;
        }
    }

}


