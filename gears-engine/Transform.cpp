#include "Transform.h"

Transform3D::Transform3D(
	const DirectX::XMFLOAT4X4* view,
	const DirectX::XMFLOAT4X4* persp)
	: sx(1.f), sy(1.f), sz(1.f)
	, pitch(0.f), yaw(0.f), roll(0.f)
	, px(0.f), py(0.f), pz(0.f)
	, length(0.f), height(0.f), width(0.f)
	, view_matrix(view), perspective_matrix(persp)
{
	recalculate_model_matrix();
}

Transform3D::Transform3D(
	float px, float py, float pz, 
	float sx, float sy, float sz, 
	float pitch, float yaw, float roll, 
	float length, float height, float width,
	const DirectX::XMFLOAT4X4* view,
	const DirectX::XMFLOAT4X4* persp)
	: px(px), py(py), pz(pz)
	, sx(sx), sy(sy), sz(sz)
	, pitch(pitch), yaw(yaw), roll(roll)
	, length(length), height(height), width(width)
	, view_matrix(view), perspective_matrix(persp)
{
	recalculate_model_matrix();
}

void Transform3D::set_position(float x, float y, float z)
{
	px = x;
	py = y;
	pz = z;
	recalculate_model_matrix();
}

void Transform3D::move(float dx, float dy, float dz)
{
	set_position(px + dx, py + dy, pz + dz);
	recalculate_model_matrix();
}

void Transform3D::set_scale(float x, float y, float z)
{
	sx = x;
	sy = y;
	sz = z;
	recalculate_model_matrix();
}

void Transform3D::set_rotation(float pitch, float yaw, float roll)
{
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;
	recalculate_model_matrix();
}

void Transform3D::rotate(float dpitch, float dyaw, float droll)
{
	set_rotation(pitch + dpitch, yaw + dyaw, roll + droll);
	recalculate_model_matrix();
}

void Transform3D::set_dimension(float length, float height, float width)
{
	this->length = length;
	this->height = height;
	this->width = width;
}

void Transform3D::dimension(float dlength, float dheight, float dwidth)
{
	set_dimension(length + dlength, height + dheight, width + dwidth);
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
	return DirectX::XMLoadFloat4x4(&model_matrix) *
		DirectX::XMLoadFloat4x4(view_matrix) *
		DirectX::XMLoadFloat4x4(perspective_matrix);
}

void Transform3D::recalculate_model_matrix()
{
	DirectX::XMStoreFloat4x4(&model_matrix,
		DirectX::XMMatrixScaling(
			sx, sy, sz) *
		DirectX::XMMatrixRotationRollPitchYaw(
			pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(
			px, py, pz));
}

Transform2D::Transform2D(
	const DirectX::XMFLOAT4X4* view_matrix, 
	const DirectX::XMFLOAT4X4* ortho_matrix)
	: sx(1.f), sy(1.f)
	, angle(0.f)
	, px(0.f), py(0.f)
	, length(0.f), height(0.f)
	, view_matrix(view_matrix), ortho_matrix(ortho_matrix)
{
	recalculate_model_matrix();
}

Transform2D::Transform2D(
	const DirectX::XMFLOAT4X4* view_matrix, 
	const DirectX::XMFLOAT4X4* ortho_matrix,
	float px, float py, 
	float sx, float sy, 
	float angle, 
	float length, float height)
	: px(px), py(py)
	, sx(sx), sy(sy)
	, angle(angle)
	, length(length), height(height)
	, view_matrix(view_matrix), ortho_matrix(ortho_matrix)
{
	recalculate_model_matrix();
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
		res_y -= hheight;
	}
	else if (RELPOS::BOTTOM_LEFT == (relative_pos & 0b11))
	{
		res_y -= real_height;
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
	recalculate_model_matrix();
}

void Transform2D::set_position(const Vector2f& pos, RELPOS relative_pos)
{
	set_position(pos.x, pos.y, relative_pos);
}

void Transform2D::move(float dx, float dy)
{
	set_position(px + dx, py + dy);
	recalculate_model_matrix();
}

void Transform2D::move(const Vector2f& dpos)
{
	move(dpos.x, dpos.y);
}

void Transform2D::set_scale(float x, float y)
{
	sx = x;
	sy = y;
	recalculate_model_matrix();
}

void Transform2D::set_scale(const Vector2f& scale)
{
	set_scale(scale.x, scale.y);
}

void Transform2D::set_rotation(float angle)
{
	this->angle = angle;
	recalculate_model_matrix();
}

void Transform2D::rotate(float dangle)
{
	set_rotation(angle + dangle);
	recalculate_model_matrix();
}

void Transform2D::set_dimension(float length, float height)
{
	this->length = length;
	this->height = height;
}

void Transform2D::set_dimension(const Vector2f& dimension)
{
	set_dimension(dimension.x, dimension.y);
}

void Transform2D::dimension(float dlength, float dheight)
{
	set_dimension(length + dlength, height + dheight);
}

Vector2f Transform2D::get_position(RELPOS relative_pos) const
{
	// result x and y
	float res_x = px;
	float res_y = py;

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
		res_x += hlength;
	}
	else if (RELPOS::TOP_RIGHT == (relative_pos & 0b1100))
	{
		res_x += real_length;
	}

	return { res_x, res_y };
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

Vector2f Transform2D::get_scale() const
{
	return { sx, sy };
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

float Transform2D::get_rotation() const
{
	return angle;
}

void Transform2D::get_dimension(float& length, float& height) const
{
	length = this->length;
	height = this->height;
}

Vector2f Transform2D::get_dimension() const
{
	return { length, height };
}

float Transform2D::get_length() const
{
	return length;
}

float Transform2D::get_height() const
{
	return height;
}

bool Transform2D::contains(float x, float y) const
{
	float top = py;
	float bottom = py + height * sy;
	float left = px;
	float right = px + length * sx;
	if (x >= left && x < right &&
		y >= top && y < bottom)
	{
		return true;
	}
	return false;
}

DirectX::XMMATRIX Transform2D::get_transformation_matrix() const
{
	// TODO: maybe choose another z position?

	return
		DirectX::XMLoadFloat4x4(&model_matrix) *
		DirectX::XMLoadFloat4x4(view_matrix) *
		DirectX::XMLoadFloat4x4(ortho_matrix);
}

void Transform2D::recalculate_model_matrix()
{
	union
	{
		__m128 vector;
		float m[4];
	} matrix[4];

	DirectX::XMMATRIX ortho_m = DirectX::XMLoadFloat4x4(ortho_matrix);
	matrix[0].vector = ortho_m.r[0];
	matrix[1].vector = ortho_m.r[1];

	// find out the screen width and height from the ortho matrix
	screen_half_width = 1.f / matrix[0].m[0];
	screen_half_height = 1.f / matrix[1].m[1];

	DirectX::XMStoreFloat4x4(&model_matrix,
		DirectX::XMMatrixScaling(
			sx, sy, 1.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(
			0.0f, 0.0f, angle) *
		DirectX::XMMatrixTranslation(
			px - screen_half_width, screen_half_height - py, 0.0f));
}
