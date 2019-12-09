#pragma once
#include <DirectXMath.h>

class Transform3D
{
public:
	Transform3D();

	virtual void set_position(float x, float y, float z);
	virtual void move(float dx, float dy, float dz);
	virtual void set_scale(float x, float y, float z);
	virtual void set_rotation(float pitch, float yaw, float roll);
	virtual void rotate(float dpitch, float dyaw, float droll);
	virtual void set_dimension(float length, float height, float width);
	virtual void dimension(float dlength, float dheight, float dwidth);

	virtual void get_position(float& x, float& y, float& z) const;
	virtual void get_scale(float& x, float& y, float& z) const;
	virtual void get_rotation(float& pitch, float& yaw, float& roll) const;
	virtual void get_dimension(float& length, float& height, float& width) const;

	virtual DirectX::XMMATRIX get_transformation_matrix() const;
	
protected:
	// s ... Scale
	float sx, sy, sz;
	// ... yeah
	float pitch, yaw, roll;
	// p ... Position
	float px, py, pz;
	// ... yeah
	float length, height, width;
};

class Transform2D
{
public:
	Transform2D();

	virtual void set_position(float x, float y);
	virtual void move(float dx, float dy);
	virtual void set_scale(float x, float y);
	virtual void set_rotation(float angle);
	virtual void rotate(float dangle);
	virtual void set_dimension(float length, float height);
	virtual void dimension(float dlength, float dheight);

	virtual void get_position(float& x, float& y) const;
	virtual void get_scale(float& x, float& y) const;
	virtual void get_rotation(float& angle) const;
	virtual void get_dimension(float& length, float& height) const;

	virtual DirectX::XMMATRIX get_transformation_matrix() const;
	
protected:
	// s ... Scale
	float sx, sy;
	// ... yeah
	float angle;
	// p ... Position
	float px, py;
	// ... yeah
	float length, height;

};
