#include "block.hxx"


void
Block::shift_down()
{
    for (Index iter : boundbox_) {
        iter.set_posn({iter.posn().x, iter.posn().y + 1});
    }
}
