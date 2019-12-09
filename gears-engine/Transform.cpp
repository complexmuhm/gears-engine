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

void Transform3D::get_scale(float& x, float& y, float& z) const
{
	x = sx;
	y = sy;
	z = sz;
}

void Transform3D::get_rotation(float& pitch, float& yaw, float& roll) const
{
	pitch = this->pitch;
	yaw = this->yaw;
	roll = roll;
}

void Transform3D::get_dimension(float& length, float& height, float& width) const
{
	length = this->length;
	height = this->height;
	width = this->width;
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

void Transform2D::set_position(float x, float y)
{
	px = x;
	py = y;
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

void Transform2D::get_scale(float& x, float& y) const
{
	x = sx;
	y = sy;
}

void Transform2D::get_rotation(float& angle) const
{
	angle = this->angle;
}

void Transform2D::get_dimension(float& length, float& height) const
{
	length = this->length;
	height = this->height;
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
