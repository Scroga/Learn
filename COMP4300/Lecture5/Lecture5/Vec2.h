#ifndef VEC2_H
#define VEC2_H

template <typename T>
class Vec2
{
public:
	T x;
	T y;

	Vec2()
		: x(0)
		, y(0)
	{}

	Vec2(T xin, T yin)
		: x(xin)
		, y(yin)
	{}

	template <typename U>
	explicit Vec2(const Vec2<U> vector)
		: x(static_cast<T>(vector.x))
		, y(static_cast<T>(vector.y))
	{}

	float dist(const Vec2& vector) const
	{
		return sqrtf((vector.x - x) * (vector.x - x) + (vector.y - y) * (vector.y - y));
	}

	/*????
	Vec2 rotate(float degree)
	{
		return Vec2(x * cos(degree) - y * sin(degree)), (x * sin(degree) + y * cos(degree));
	}
	*/

	void normalize()
	{
		
	}


	void print() const
	{
		std::cout << x << " " << y << std::endl;
	}
};
////////////////////////////////////////////////////////////
template <typename T>
Vec2<T> operator - (const Vec2<T>& right)
{
	return Vec2<T>(-right.x, -right.y);
}

////////////////////////////////////////////////////////////
template <typename T>
Vec2<T> operator + (const Vec2<T> left, const Vec2<T>& right)
{
	return Vec2<T>(left.x + right.x, left.y + right.y);
}

////////////////////////////////////////////////////////////
template <typename T>
Vec2<T> operator - (const Vec2<T> left, const Vec2<T>& right)
{
	return Vec2<T>(left.x - right.x, left.y - right.y);
}

////////////////////////////////////////////////////////////
template <typename T>
Vec2<T> operator += (Vec2<T>& left, const Vec2<T>& right)
{
	left.x += right.x;
	left.y += right.y;
	return left;
}

////////////////////////////////////////////////////////////
template <typename T>
Vec2<T> operator -= (Vec2<T>& left, const Vec2<T>& right)
{
	left.x -= right.x;
	left.y -= right.y;
	return left;
}

////////////////////////////////////////////////////////////
template <typename T>
Vec2<T> operator * (const Vec2<T>& left, T right)
{
	return Vec2<T>(right.x * left.x, right.y * left.y);
}

////////////////////////////////////////////////////////////
template <typename T>
Vec2<T> operator * (T left, const  Vec2<T>& right)
{
	return Vec2<T>(right.x * left, right.y * left);
}

////////////////////////////////////////////////////////////
template <typename T>
Vec2<T> operator *= (Vec2<T>& left, T right)
{
	left.x *= right.x;
	left.y *= right.y;
	return left;
}

////////////////////////////////////////////////////////////
template <typename T>
Vec2<T> operator / (const Vec2<T>& left, T right)
{
	return Vec2<T>(left.x / right, left.y / right);
}

////////////////////////////////////////////////////////////
template <typename T>
Vec2<T> operator /= (Vec2<T>& left, T right)
{
	left.x /= right.x;
	left.y /= right.y;
	return left;
}

////////////////////////////////////////////////////////////
template <typename T>
bool operator == (const Vec2<T>& left, const Vec2<T>& right)
{
	return (left.x == right.x) && (left.y == right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
bool operator != (const  Vec2<T>& left, const Vec2<T>& right)
{
	return (left.x != right.x) || (left.y != right.y);
}

////////////////////////////////////////////////////////////
typedef Vec2<int>			Vec2i;
typedef Vec2<unsigned int>  Vec2u;
typedef Vec2<float>			Vec2f;

#endif
