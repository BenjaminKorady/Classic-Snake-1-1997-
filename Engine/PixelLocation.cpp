#include "PixelLocation.h"

/**
    Creates a default location object with coordinates 0,0
*/
PixelLocation::PixelLocation()
	:
	x(0), y(0)
{
}

/**
    Creates a location object with coordinate input x and y

    @param x x-coordinate
    @param y y-coordinate
*/
PixelLocation::PixelLocation(int x, int y)
	:
	x(x), y(y)
{

}


bool operator==(const PixelLocation & lhs, const PixelLocation & rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const PixelLocation & lhs, const PixelLocation & rhs)
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

PixelLocation operator+(const PixelLocation & lhs, const PixelLocation & rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}


PixelLocation operator*(const PixelLocation & lhs, const int & rhs)
{
    return { lhs.x * rhs, lhs.y * rhs };

}

PixelLocation operator*(const int & lhs, const PixelLocation & rhs)
{
    return { rhs.x * lhs, rhs.y * lhs };
}
