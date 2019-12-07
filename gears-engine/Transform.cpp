#include "Transform.h"

void Transform::set_position(const Position& pos)
{
	position = pos;
}

void Transform::set_position(float x, float y, float z)
{
	position = { x, y, z };
}

void Transform::set_rotation(const Rotation& rot)
{
	rotation = rot;
}

void Transform::set_rotation(float pitch, float yaw, float roll)
{
	rotation = { pitch, yaw, roll };
}

Position Transform::get_position() const
{
	return position;
}

void Transform::get_position(float& x, float& y, float& z) const
{
	x = position.x;
	y = position.y;
	z = position.z;
}

Rotation Transform::get_rotation() const
{
	return rotation;
}

void Transform::get_rotation(float& pitch, float& yaw, float& roll) const
{
	pitch = rotation.pitch;
	yaw = rotation.yaw;
	roll = rotation.roll;
}

DirectX::XMMATRIX Transform::get_transformation_matrix()
{
	return 
		DirectX::XMMatrixRotationRollPitchYaw(
			rotation.pitch, rotation.yaw, rotation.roll) *
		DirectX::XMMatrixTranslation(
			position.x, position.y, position.z);
}
