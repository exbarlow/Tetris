#include "model.hxx"

Model::Model()
        : score_(0)
{
    for (int row = 0; row < boardheight; ++row) {
        for (int col = 0; col < boardwidth; ++col) {
            board_[row][col] = Index({col, row});
        }
    }

    // temporary
    for (int row = 0; row < boardheight; ++row) {
        for (int col = 0; col < boardwidth; ++col) {
            if (board_[row][col].posn().y == 0) {
                board_[row][col].set_color(Enumcolor::red);
            } else if (board_[row][col].posn().y == 1 && board_[row][col]
                                                                 .posn().x %
                                                         3 == 0) {
                board_[row][col].set_color(Enumcolor::lime);
            }
        }
    }
}

// Returns a copy of board_
std::array<std::array<Index, Model::boardwidth>, Model::boardheight>
Model::board() const
{
    return board_;
}

// Shifts the entire board down 'num' rows
void
Model::shift_down(int num)
{
    std::move_backward(&board_[0], &board_[boardheight - num],
                       &board_[boardheight]);

    for (int row = 0; row < num; ++row) {
        for (int col = 0; col < boardwidth; ++col) {
            board_[row][col] = Index();
        }
    }


    for (int row = 0; row < boardheight; ++row) {
        for (int col = 0; col < boardwidth; ++col) {
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