#pragma once
template<typename T>
struct Vector2
{
	T x, y;

	Vector2()
		: x(0), y(0)
	{}

	Vector2(T x, T y)
		: x(x), y(y)
	{}

	// NOTE: not a good idea to cast but for now ok
	template<typename S>
	explicit Vector2(const Vector2<S>& rhs)
	{
		this->x = (T)rhs.x;
		this->y = (T)rhs.y;
	}
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned int>;

template<typename T>
Vector2<T> operator-(const Vector2<T> & lhs, const Vector2<T> & rhs)
{
	return { lhs.x - rhs.x, lhs.y - rhs.y };
}
template<typename T>
Vector2<T> operator+(const Vector2<T> & lhs, const Vector2<T> & rhs)
{
	return { lhs.x + rhs.x, lhs.y + rhs.y };
}


template<typename T>
struct Vector3
{
	T x, y, z;
};

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
using Vector3u = Vector3<unsigned int>;

template<typename T>
struct Vector4
{
	T x, y, z, w;
};

using Vector4f = Vector4<float>;
using Vector4i = Vector4<int>;
using Vector4u = Vector4<unsigned int>;

