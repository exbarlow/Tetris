#include "model.hxx"

Model::Model()
        : score_(0),
          can_swap_(true)
{
    for (int row = 0; row < Board::height; ++row) {
        for (int col = 0; col < Board::width; ++col) {
            board_[row][col] = Index({col, row});
        }
    }

    // temporary
    for (int row = 0; row < Board::height; ++row) {
        for (int col = 0; col < Board::width; ++col) {
            if (board_[row][col].posn().y == 0) {
                board_[row][col].set_color(Enumcolor::red);
            } else if (board_[row][col].posn().y == 1 && board_[row][col]
                                                                 .posn().x %
                                                         3 == 0) {
                board_[row][col].set_color(Enumcolor::lime);
            }
        }
    }
    stored_ = Block();
    refill_block_bank();
    bank_to_next(0);
    bank_to_next(1);
    bank_to_next(2);
    next_to_current();
}

// Returns a copy of board_
std::array<std::array<Index, Board::width>, Board::height>
Model::board() const
{
    return board_;
}

// Shifts the entire board down 'num' rows
void
Model::shift_down(int num)
{
    std::move_backward(&board_[0], &board_[Board::height - num],
                       &board_[Board::height]);

    for (int row = 0; row < num; ++row) {
        for (int col = 0; col < Board::width; ++col) {
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
}

void
Model::store()
{
    if (can_swap_) {
        if (stored_.color() == Enumcolor::black) {
            stored_ = Block(current_.color());
        } else {
            Block temp = Block(current_.color());
            current_ = stored_;
            stored_ = temp;
        }
        next_to_current();
        can_swap_ = false;
    }
}