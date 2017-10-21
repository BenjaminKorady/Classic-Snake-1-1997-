#pragma once

#include <cmath>
#define DIR_RIGHT 1,  0
#define DIR_LEFT -1, 0
#define DIR_UP 0, -1
#define DIR_DOWN 0, 1
#define DIR_ZERO 0, 0

template<typename T>
class Vec2_
{
public:
	Vec2_() = default;
	Vec2_( T x_in,T y_in )
		:
		x( x_in ),
		y( y_in )
	{}
	template<typename S>
	explicit Vec2_( const Vec2_<S>& src )
		:
		x( (T)src.x ),
		y( (T)src.y )
	{}
	Vec2_ operator+( const Vec2_& rhs ) const
	{
		return Vec2_( x + rhs.x,y + rhs.y );
	}
	Vec2_& operator+=( const Vec2_& rhs )
	{
		return *this = *this + rhs;
	}
	Vec2_ operator*( T rhs ) const
	{
		return Vec2_( x * rhs,y * rhs );
	}
	Vec2_& operator*=( T rhs )
	{
		return *this = *this * rhs;
	}
	Vec2_ operator-( const Vec2_& rhs ) const
	{
		return Vec2_( x - rhs.x,y - rhs.y );
	}
	Vec2_ operator-() const {
		return Vec2_(-x, -y);
	}
	Vec2_& operator-=( const Vec2_& rhs )
	{
		return *this = *this - rhs;
	}
	bool operator==(const Vec2_& rhs) {
		return rhs.x == x && rhs.y == y;
	}
	bool operator!=(const Vec2_& rhs) {
		return !(*this == rhs);
	}
	friend bool operator==(const Vec2_& lhs, const Vec2_& rhs) {
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
	T GetLength() const
	{
		return (T)std::sqrt( GetLengthSq() );
	}
	T GetLengthSq() const
	{
		return x * x + y * y;
	}
	Vec2_& Normalize()
	{
		return *this = GetNormalized();
	}
	Vec2_ GetNormalized() const
	{
		const T len = GetLength();
		if( len != (T)0 )
		{
			return *this * ((T)1 / len);
		}
		return *this;
	}
public:
	T x;
	T y;
};


typedef Vec2_<float> Vec2;
typedef Vec2_<int> Vei2;
