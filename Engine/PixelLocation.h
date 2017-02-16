/**
    Handles locations and co-ordinate geometry of the board

    @author Benjamin Korady
    @version 1.0    11/02/2017
*/

#pragma once


class PixelLocation {
public:
	PixelLocation();
	PixelLocation(int x, int y);
	friend bool operator==(const PixelLocation& lhs, const PixelLocation& rhs);
    friend bool operator!=(const PixelLocation& lhs, const PixelLocation& rhs);
	friend PixelLocation operator+(const PixelLocation& lhs, const PixelLocation& rhs);
    friend PixelLocation operator*(const PixelLocation& lhs, const int& rhs);
    friend PixelLocation operator*(const int& lhs, const PixelLocation& rhs);
	int x;
	int y;
};

