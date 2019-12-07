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
	Transform();
	Transform(const Transform&) = delete;
	Transform& operator=(const Transform&) = delete;
	virtual ~Transform() = default;

	virtual void set_position(float x, float y, float z);
	virtual void set_scale(float x, float y, float z);
	virtual void set_rotation(float pitch, float yaw, float roll);

	virtual void get_position(float& x, float& y, float& z) const;
	virtual void get_scale(float& x, float& y, float& z) const;
	virtual void get_rotation(float& pitch, float& yaw, float& roll) const;

	virtual DirectX::XMMATRIX get_transformation_matrix();
	
protected:
	// s ... Scale
	float sx, sy, sz;
	// ... yeah
	float pitch, yaw, roll;
	// p ... Position
	float px, py, pz;
};

