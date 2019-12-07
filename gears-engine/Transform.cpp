#include "Transform.h"

Transform::Transform()
	: sx(1.f), sy(1.f), sz(1.f)
	, pitch(0.f), yaw(0.f), roll(0.f)
	, px(0.f), py(0.f), pz(0.f)
{
}

void Transform::set_position(float x, float y, float z)
{
	px = x;
	py = y;
	pz = z;
}

void Transform::set_scale(float x, float y, float z)
{
	sx = x;
	sy = y;
	sz = z;
}

void Transform::set_rotation(float pitch, float yaw, float roll)
{
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;
}

void Transform::get_position(float& x, float& y, float& z) const
{
	x = px;
	y = py;
	z = pz;
}

void Transform::get_scale(float& x, float& y, float& z) const
{
	x = sx;
	y = sy;
	z = sz;
}

void Transform::get_rotation(float& pitch, float& yaw, float& roll) const
{
	pitch = this->pitch;
	yaw = this->yaw;
	roll = roll;
}

DirectX::XMMATRIX Transform::get_transformation_matrix()
{
	return
		DirectX::XMMatrixScaling(
			sx, sy, sz) *
		DirectX::XMMatrixRotationRollPitchYaw(
			pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(
			px, py, pz);
}
