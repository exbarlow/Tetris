#include "index.hxx"

using namespace ge211;
using Position = Posn<int>;

// Initiates Index as black, unoccupied, with the provided position
Index::Index(Position position)
        : posn_(position),
          occupied_(false),
          color_(Enumcolor::black)
{ }

// Sets posn_ of the index to the provided position
void
Index::set_posn(Position position)
{
    posn_ = position;
}

// Sets the occupied status of the index to true
void
Index::set_occupied()
{
    occupied_ = true;
}

// Sets the color of the index to 'color'
void
Index::set_color(Enumcolor enumcolor)
{
    color_ = enumcolor;
}

// Returns the position of the index
Position
Index::posn()
{
    return posn_;
}

// Returns the occupied status of the index
bool
Index::occupied()
{
    return occupied_;
}

// Returns the color of the index
Enumcolor
Index::color()
{
    return color_;
}





