#include "model.hxx"
#include <catch.hxx>

struct Test_access
{
    Model& model;

    void set_current(Block block)
    {
        model.current_ = block;
    }

    void fill_board(int x, int y, Enumcolor color)
    {
        model.board_[y][x].set_occupied();
        model.board_[y][x].set_color(color);
    }

    Index board_index(int x, int y)
    {
        return model.board_[y][x];
    }

    bool can_swap()
    {
        return model.can_swap_;
    }

    void yes_we_can_swap()
    {
        model.can_swap_ = true;
    }

};

// This test case shows that Model::shift_left() and Model::shift_right()
// will move the current block left and right as long as there is nothing
// blocking the block (such as the edge of the board) from doing so.
TEST_CASE("Current Left Right")
{
    Model m;
    Test_access t {m};

    t.set_current(Block(Enumcolor::aqua));
    m.actual_move();
    m.actual_move();

    // Checks that after constructing a 4x1 aqua colored piece and moving it
    // down twice, the expected indices are occupied, the correct color, and
    // in their expected positions
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == i - 1);
            CHECK(m.current().boundbox().at(i).posn().y == 1);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }

    m.rotate();

    // Checks that the positions are as expected after rotating 90 degrees
    // clockwise once
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == 5);
            CHECK(m.current().boundbox().at(i).posn().y == i - 4);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }

    m.shift_left();

    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == 4);
            CHECK(m.current().boundbox().at(i).posn().y == i - 4);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }

    m.shift_right(); //5 <-- (x coordinate of the occupied row)
    m.shift_right(); //6
    m.shift_right(); //7
    m.shift_right(); //8
    m.shift_right(); //9
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == 9);
            CHECK(m.current().boundbox().at(i).posn().y == i - 4);
        } else if (i < 4) {
            // Shows that the boundbox can move outside the boundaries (from
            // 0-9 in the x direction, not customizable) so
            // long as it is not occupied
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
            CHECK(m.current().boundbox().at(i).posn().x == 10);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }
    m.shift_right();

    // Checks that the boundbox of current_ will not move if the occupied
    // indices would move outside the playable board range.
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == 9);
            CHECK(m.current().boundbox().at(i).posn().y == i - 4);
        } else if (i < 4) {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
            CHECK(m.current().boundbox().at(i).posn().x == 10);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }

    // Places a fixed red block directly to the left of the current block
    t.fill_board(8, 0, Enumcolor::red);

    m.shift_left();
    // Checks that the boundbox of current_ will not move if the occupied
    // indices would move on top of occupied indices in the board
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == 9);
            CHECK(m.current().boundbox().at(i).posn().y == i - 4);
        } else if (i < 4) {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
            CHECK(m.current().boundbox().at(i).posn().x == 10);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }
}

// Checks that rotational behavior is as expected
TEST_CASE("Rotate")
{
    Model m;
    Test_access t {m};

    t.set_current(Block(Enumcolor::aqua));
    m.actual_move();
    m.actual_move();

    // Checks that after constructing a 4x1 aqua colored piece and moving it
    // down twice, the expected indices are occupied, the correct color, and
    // in their expected positions
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == i - 1);
            CHECK(m.current().boundbox().at(i).posn().y == 1);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }

    m.rotate();

    // Checks that the positions are as expected after rotating 90 degrees
    // clockwise once
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == 5);
            CHECK(m.current().boundbox().at(i).posn().y == i - 4);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }

    m.rotate();

    // Checks that the positions are as expected after rotating 90 degrees
    // clockwise twice
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == 10 - i);
            CHECK(m.current().boundbox().at(i).posn().y == 2);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }

    m.rotate();

    // Checks that the positions are as expected after rotating 90 degrees
    // clockwise three times
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == 4);
            CHECK(m.current().boundbox().at(i).posn().y == 7 - i);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }

    m.rotate();

    // Checks that the positions are as expected after rotating back to the
    // initial state
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == i - 1);
            CHECK(m.current().boundbox().at(i).posn().y == 1);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }

    // Moves the block to a vertical position up against the right boundary
    m.rotate();
    m.shift_right();
    m.shift_right();
    m.shift_right();
    m.shift_right();

    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == 9);
            CHECK(m.current().boundbox().at(i).posn().y == i - 4);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }

    m.rotate();
    // Checks that the block will not rotate if doing so would put an
    // occupied index outside the boundaries
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == 9);
            CHECK(m.current().boundbox().at(i).posn().y == i - 4);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }

    // Resets the aqua (4x1) block and places a fixed red block in the board
    // in a location that an index would rotate to
    t.set_current(Enumcolor::aqua);
    m.actual_move();
    m.actual_move();
    t.fill_board(5, 3, Enumcolor::red);

    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == i - 1);
            CHECK(m.current().boundbox().at(i).posn().y == 1);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }

    m.rotate();

    // Checks that the block will not rotate if it would cause an overlap on
    // the board
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == i - 1);
            CHECK(m.current().boundbox().at(i).posn().y == 1);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }
}

// Tests that the phantom-related model functions work correctly and
// simulates quick-dropping a piece
TEST_CASE("quick drop")
{
    Model m;
    Test_access t {m};

    t.set_current(Enumcolor::aqua);
    m.actual_move();
    m.actual_move();

    // Checks that the position is as expected
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == i - 1);
            CHECK(m.current().boundbox().at(i).posn().y == 1);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }


    m.update_phantom();
    CHECK(m.score() == 0);

    // Checks that the phantom block is the correct position (at the bottom
    // of the grid)
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.phantom().boundbox().at(i).occupied());
            CHECK(m.phantom().boundbox().at(i).color() ==
                  Enumcolor::aqua);
            CHECK(m.phantom().boundbox().at(i).posn().x == i - 1);
            CHECK(m.phantom().boundbox().at(i).posn().y == 19);
        } else {
            CHECK_FALSE(m.phantom().boundbox().at(i).occupied());
            CHECK(m.phantom().boundbox().at(i).color() ==
                  Enumcolor::black);
        }
    }


    // This is the code called when space is pressed
    t.set_current(m.phantom_block_score());
    m.actual_move();
    m.actual_move();

    // Checks that fixed blocks have been placed in the spot where the
    // phantom was
    for (int i = 3; i < 7; ++i) {
        CHECK(t.board_index(i, 19).occupied());
        CHECK(t.board_index(i, 19).color() == Enumcolor::aqua);
    }

    CHECK(m.score() == 36);

    // Creates a new block
    t.set_current(Enumcolor::aqua);
    m.actual_move();
    m.actual_move();

    // Checks that the position is as expected
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::aqua);
            CHECK(m.current().boundbox().at(i).posn().x == i - 1);
            CHECK(m.current().boundbox().at(i).posn().y == 1);
        } else {
            CHECK_FALSE(m.current().boundbox().at(i).occupied());
            CHECK(m.current().boundbox().at(i).color() == Enumcolor::black);
        }
    }


    m.update_phantom();
    CHECK(m.score() == 36);

    // Checks that the phantom block is in the correct position (right above
    // the block placed earlier)
    for (int i = 0; i < 15; ++i) {
        if (4 <= i && i <= 7) {
            CHECK(m.phantom().boundbox().at(i).occupied());
            CHECK(m.phantom().boundbox().at(i).color() ==
                  Enumcolor::aqua);
            CHECK(m.phantom().boundbox().at(i).posn().x == i - 1);
            CHECK(m.phantom().boundbox().at(i).posn().y == 18);
        } else {
            CHECK_FALSE(m.phantom().boundbox().at(i).occupied());
            CHECK(m.phantom().boundbox().at(i).color() ==
                  Enumcolor::black);
        }
    }


    // This is the code called when space is pressed
    t.set_current(m.phantom_block_score());
    m.actual_move();
    m.actual_move();

    // Checks that fixed blocks have been placed in the spot where the
    // phantom was
    for (int i = 3; i < 7; ++i) {
        CHECK(t.board_index(i, 18).occupied());
        CHECK(t.board_index(i, 18).color() == Enumcolor::aqua);
    }

    CHECK(m.score() == 70);

}

TEST_CASE("Line clearing")
{
    Model m;
    Test_access t {m};

    t.fill_board(4, 19, Enumcolor::red);
    t.fill_board(4, 17, Enumcolor::lime);

    for (int i = 0; i < 10; ++i) {
        t.fill_board(i, 18, Enumcolor::blue);
    }

    for (int i = 0; i < 10; ++i) {
        CHECK(t.board_index(i, 18).occupied());
        CHECK(t.board_index(i, 18).color() == Enumcolor::blue);
    }

    CHECK(t.board_index(4, 19).occupied());
    CHECK(t.board_index(4, 19).color() == Enumcolor::red);

    CHECK(t.board_index(4, 17).occupied());
    CHECK(t.board_index(4, 17).color() == Enumcolor::lime);

    CHECK(m.score() == 0);

    m.clear_line();
    // Checks that m.clear_line() clears a full line, adds 100 points, and shifts
    // down all lines above that line
    for (int i = 0; i < 10; ++i) {
        if (i != 4) {
            CHECK_FALSE(t.board_index(i, 18).occupied());
            CHECK(t.board_index(i, 18).color() == Enumcolor::black);
        }
    }
    // This little block doesn't move!
    CHECK(t.board_index(4, 19).occupied());
    CHECK(t.board_index(4, 19).color() == Enumcolor::red);

    // This little block fell down a line!
    CHECK(t.board_index(4, 18).occupied());
    CHECK(t.board_index(4, 18).color() == Enumcolor::lime);

    CHECK(m.score() == 100);

    m.clear_line();
    // Checks that m.clear_line() does nothing if there is no line that can be
    // cleared
    for (int i = 0; i < 10; ++i) {
        if (i != 4) {
            CHECK_FALSE(t.board_index(i, 18).occupied());
            CHECK(t.board_index(i, 18).color() == Enumcolor::black);
        }
    }
    CHECK(t.board_index(4, 19).occupied());
    CHECK(t.board_index(4, 19).color() == Enumcolor::red);

    CHECK(t.board_index(4, 18).occupied());
    CHECK(t.board_index(4, 18).color() == Enumcolor::lime);

    CHECK(m.score() == 100);

}

TEST_CASE("store a block")
{
    Model m;
    Test_access t {m};

    // This is the default stored block -- it is an empty block (contains
    // only the position {0,0} -- will not be swapped with the block in play
    CHECK(m.stored().color() == Enumcolor::black);
    CHECK(t.can_swap());
    t.set_current(Enumcolor::aqua);

    m.store();

    CHECK(m.stored().color() == Enumcolor::aqua);
    CHECK_FALSE(t.can_swap());
    CHECK_FALSE(m.current().color() == Enumcolor::black);

    t.set_current(Enumcolor::red);

    m.store();
    // Checks that while can_swap_ is negative, store() does nothing
    CHECK(m.stored().color() == Enumcolor::aqua);
    CHECK_FALSE(m.stored().color() == Enumcolor::red);
    CHECK_FALSE(t.can_swap());

    t.yes_we_can_swap(); // sets can_swap to true (this will happen when a
    // block falls to the bottom and is locked in).

    CHECK(t.can_swap());

    t.set_current(Enumcolor::yellow);

    m.store();

    // Checks that when the stored block is not black, the blocks are swapped
    // (stored_ and current_ are swapped).
    CHECK(m.stored().color() == Enumcolor::yellow);
    CHECK(m.current().color() == Enumcolor::aqua);
    CHECK_FALSE(t.can_swap());

}

TEST_CASE("obstruct = game over")
{
    Model m;
    Test_access t {m};

    t.set_current(Enumcolor::blue);
    t.fill_board(5, 0, Enumcolor::red);

    CHECK_FALSE(m.game_over());

    m.actual_move();

    // Checks that if a falling block is obstructed before coming into the
    // visible grid the game ends :(
    CHECK(m.game_over());
}