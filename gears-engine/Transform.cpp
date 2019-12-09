#include "Transform.h"

Transform3D::Transform3D()
	: sx(1.f), sy(1.f), sz(1.f)
	, pitch(0.f), yaw(0.f), roll(0.f)
	, px(0.f), py(0.f), pz(0.f)
	, length(0.f), height(0.f), width(0.f)
{
}

void Transform3D::set_position(float x, float y, float z)
{
	px = x;
	py = y;
	pz = z;
}

void Transform3D::move(float dx, float dy, float dz)
{
	px += dx;
	py += dy;
	pz += dz;
}

void Transform3D::set_scale(float x, float y, float z)
{
	sx = x;
	sy = y;
	sz = z;
}

void Transform3D::set_rotation(float pitch, float yaw, float roll)
{
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;
}

void Transform3D::rotate(float dpitch, float dyaw, float droll)
{
	pitch += dpitch;
	yaw += dyaw;
	roll += droll;
}

void Transform3D::set_dimension(float length, float height, float width)
{
	this->length = length;
	this->height = height;
	this->width = width;
}

void Transform3D::dimension(float dlength, float dheight, float dwidth)
{
	length += dlength;
	height += dheight;
	width += dwidth;
}

void Transform3D::get_position(float& x, float& y, float& z) const
{
	x = px;
	y = py;
	z = pz;
}

float Transform3D::get_position_x() const
{
	return px;
}

float Transform3D::get_position_y() const
{
	return py;
}

float Transform3D::get_position_z() const
{
	return pz;
}

void Transform3D::get_scale(float& x, float& y, float& z) const
{
	x = sx;
	y = sy;
	z = sz;
}

float Transform3D::get_scale_x() const
{
	return sx;
}

float Transform3D::get_scale_y() const
{
	return sy;
}

float Transform3D::get_scale_z() const
{
	return sz;
}

void Transform3D::get_rotation(float& pitch, float& yaw, float& roll) const
{
	pitch = this->pitch;
	yaw = this->yaw;
	roll = roll;
}

float Transform3D::get_pitch() const
{
	return pitch;
}

float Transform3D::get_yaw() const
{
	return yaw;
}

float Transform3D::get_roll() const
{
	return roll;
}

void Transform3D::get_dimension(float& length, float& height, float& width) const
{
	length = this->length;
	height = this->height;
	width = this->width;
}

float Transform3D::get_length() const
{
	return length;
}

float Transform3D::get_height() const
{
	return height;
}

float Transform3D::get_width() const
{
	return width;
}

DirectX::XMMATRIX Transform3D::get_transformation_matrix() const
{
	return
		DirectX::XMMatrixScaling(
			sx, sy, sz) *
		DirectX::XMMatrixRotationRollPitchYaw(
			pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(
			px, py, pz);
}

Transform2D::Transform2D()
	: sx(1.f), sy(1.f)
	, angle(0.f)
	, px(0.f), py(0.f)
	, length(0.f), height(0.f)
{
}

void Transform2D::set_position(float x, float y, RELPOS relative_pos)
{
	// result x and y
	float res_x = x;
	float res_y = y;

	float real_length = length * sx;
	float real_height = height * sy;

	// Modify res_x and y to match the wanted translation
	if (RELPOS::TOP_LEFT == (relative_pos & 0b11))
	{
	}
	else if (RELPOS::CENTER_LEFT == (relative_pos & 0b11))
	{
		float hheight = real_height / 2.f;
		res_y += hheight;
	}
	else if (RELPOS::BOTTOM_LEFT == (relative_pos & 0b11))
	{
		res_y += real_height;
	}

	if (RELPOS::TOP_LEFT == (relative_pos & 0b1100))
	{
	}
	else if (RELPOS::TOP_CENTER == (relative_pos & 0b1100))
	{
		float hlength = real_length / 2.0f;
		res_x -= hlength;
	}
	else if (RELPOS::TOP_RIGHT == (relative_pos & 0b1100))
	{
		res_x -= real_length;
	}
	px = res_x;
	py = res_y;
}

void Transform2D::move(float dx, float dy)
{
	px += dx;
	py += dy;
}

void Transform2D::set_scale(float x, float y)
{
	sx = x;
	sy = y;
}

void Transform2D::set_rotation(float angle)
{
	this->angle = angle;
}

void Transform2D::rotate(float dangle)
{
	angle += dangle;
}

void Transform2D::set_dimension(float length, float height)
{
	this->length = length;
	this->height = height;
}

void Transform2D::dimension(float dlength, float dheight)
{
	length += dlength;
	height += dheight;
}

void Transform2D::get_position(float& x, float& y) const
{
	x = px;
	y = py;
}

float Transform2D::get_position_x() const
{
	return px;
}

float Transform2D::get_position_y() const
{
	return py;
}

void Transform2D::get_scale(float& x, float& y) const
{
	x = sx;
	y = sy;
}

float Transform2D::get_scale_x() const
{
	return sx;
}

float Transform2D::get_scale_y() const
{
	return sy;
}

void Transform2D::get_rotation(float& angle) const
{
	angle = this->angle;
}

float Transform2D::get_angle() const
{
	return angle;
}

void Transform2D::get_dimension(float& length, float& height) const
{
	length = this->length;
	height = this->height;
}

float Transform2D::get_length() const
{
	return length;
}

float Transform2D::get_height() const
{
	return height;
}

DirectX::XMMATRIX Transform2D::get_transformation_matrix() const
{
	// TODO: maybe choose another z position?

	return
		DirectX::XMMatrixScaling(
			sx, sy, 1.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(
			0.0f, 0.0f, angle) *
		DirectX::XMMatrixTranslation(
			px, py, 0.0f);
}
