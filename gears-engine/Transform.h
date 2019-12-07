#pragma once
#include <DirectXMath.h>

struct Position
{
	float x, y, z;
};

struct Rotation
{
	float pitch, yaw, roll;
};

class Transform
{
public:
	Transform() = default;
	Transform(const Transform&) = delete;
	Transform& operator=(const Transform&) = delete;
	virtual ~Transform() = default;

	virtual void set_position(const Position& pos);
	virtual void set_position(float x, float y, float z);
	virtual void set_rotation(const Rotation& rot);
	virtual void set_rotation(float pitch, float yaw, float roll);

	virtual Position get_position() const;
	virtual void get_position(float& x, float& y, float& z) const;
	virtual Rotation get_rotation() const;
	virtual void get_rotation(float& pitch, float& yaw, float& roll) const;

	virtual DirectX::XMMATRIX get_transformation_matrix();
	
protected:
	Position position;
	Rotation rotation;
};

