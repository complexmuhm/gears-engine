#pragma once
#include <DirectXMath.h>

class Transform3D
{
public:
	Transform3D();
	Transform3D(const Transform3D&) = delete;
	Transform3D& operator=(const Transform3D&) = delete;
	virtual ~Transform3D() = default;

	virtual void set_position(float x, float y, float z);
	virtual void move(float dx, float dy, float dz);
	virtual void set_scale(float x, float y, float z);
	virtual void set_rotation(float pitch, float yaw, float roll);
	virtual void rotate(float dpitch, float dyaw, float droll);

	virtual void get_position(float& x, float& y, float& z) const;
	virtual void get_scale(float& x, float& y, float& z) const;
	virtual void get_rotation(float& pitch, float& yaw, float& roll) const;

	virtual DirectX::XMMATRIX get_transformation_matrix() const;
	
protected:
	// s ... Scale
	float sx, sy, sz;
	// ... yeah
	float pitch, yaw, roll;
	// p ... Position
	float px, py, pz;
};

class Transform2D
{
public:
	Transform2D();
	Transform2D(const Transform2D&) = delete;
	Transform2D& operator=(const Transform2D&) = delete;
	virtual ~Transform2D() = default;

	virtual void set_position(float x, float y);
	virtual void move(float dx, float dy);
	virtual void set_scale(float x, float y);
	virtual void set_rotation(float angle);
	virtual void rotate(float dangle);

	virtual void get_position(float& x, float& y) const;
	virtual void get_scale(float& x, float& y) const;
	virtual void get_rotation(float& angle) const;

	virtual DirectX::XMMATRIX get_transformation_matrix() const;
	
protected:
	// s ... Scale
	float sx, sy;
	// ... yeah
	float angle;
	// p ... Position
	float px, py;

};
