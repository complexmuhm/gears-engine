#pragma once
#include <DirectXMath.h>

class Transform3D
{
public:
	enum RELPOS 
	{
		// first two bits check TOP, CENTER, BOTTOM
		// next two bits check the next LEFT, CENTER, RIGHT
		// next two bits check FRONT, CENTER, BACK
		TOP_LEFT_FRONT			= 0b00000000,
		TOP_LEFT_CENTER			= 0b00010000,
		TOP_LEFT_BACK			= 0b00100000,
		TOP_CENTER_FRONT		= 0b00000100,
		TOP_CENTER_CENTER		= 0b00010100,
		TOP_CENTER_BACK			= 0b00100100,
		TOP_RIGHT_FRONT			= 0b00001000,
		TOP_RIGHT_CENTER		= 0b00011000,
		TOP_RIGHT_BACK			= 0b00101000,
		CENTER_LEFT_FRONT		= 0b00000001,
		CENTER_LEFT_CENTER		= 0b00010001,
		CENTER_LEFT_BACK		= 0b00100001,
		CENTER_CENTER_FRONT		= 0b00000101,
		CENTER_CENTER_CENTER	= 0b00010101,
		CENTER_CENTER_BACK		= 0b00100101,
		CENTER_RIGHT_FRONT		= 0b00001001,
		CENTER_RIGHT_CENTER		= 0b00011001,
		CENTER_RIGHT_BACK		= 0b00101001,
		BOTTOM_LEFT_FRONT		= 0b00000010,
		BOTTOM_LEFT_CENTER		= 0b00010010,
		BOTTOM_LEFT_BACK		= 0b00100010,
		BOTTOM_CENTER_FRONT		= 0b00000110,
		BOTTOM_CENTER_CENTER	= 0b00010110,
		BOTTOM_CENTER_BACK		= 0b00100110,
		BOTTOM_RIGHT_FRONT		= 0b00001010,
		BOTTOM_RIGHT_CENTER		= 0b00011010,
		BOTTOM_RIGHT_BACK		= 0b00101010,
	};

	Transform3D(
		const DirectX::XMFLOAT4X4* view,
		const DirectX::XMFLOAT4X4* persp);
	Transform3D(
		float px, float py, float pz,
		float sx, float sy, float sz,
		float pitch, float yaw, float roll,
		float length, float height, float width,
		const DirectX::XMFLOAT4X4* view,
		const DirectX::XMFLOAT4X4* persp);

	virtual void set_position(float x, float y, float z);
	virtual void move(float dx, float dy, float dz);
	virtual void set_scale(float x, float y, float z);
	virtual void set_rotation(float pitch, float yaw, float roll);
	virtual void rotate(float dpitch, float dyaw, float droll);
	virtual void set_dimension(float length, float height, float width);
	virtual void dimension(float dlength, float dheight, float dwidth);

	virtual void get_position(float& x, float& y, float& z) const;
	virtual float get_position_x() const;
	virtual float get_position_y() const;
	virtual float get_position_z() const;

	virtual void get_scale(float& x, float& y, float& z) const;
	virtual float get_scale_x() const;
	virtual float get_scale_y() const;
	virtual float get_scale_z() const;

	virtual void get_rotation(float& pitch, float& yaw, float& roll) const;
	virtual float get_pitch() const;
	virtual float get_yaw() const;
	virtual float get_roll() const;

	virtual void get_dimension(float& length, float& height, float& width) const;
	virtual float get_length() const;
	virtual float get_height() const;
	virtual float get_width() const;

	virtual DirectX::XMMATRIX get_transformation_matrix() const;
	
protected:
	// p ... Position
	float px, py, pz;
	// s ... Scale
	float sx, sy, sz;
	// ... yeah
	float pitch, yaw, roll;
	// ... yeah
	float length, height, width;
	// matrices
	DirectX::XMFLOAT4X4 model_matrix;
	const DirectX::XMFLOAT4X4 *view_matrix, *perspective_matrix;

private:
	void recalculate_model_matrix();

};

class Transform2D
{
public:
	enum RELPOS 
	{
		// firs two bits check if TOP, CENTER, BOTTOM
		// next two bits check if LEFT, CENTER, RIGHT
		TOP_LEFT		= 0b00000000,
		TOP_CENTER		= 0b00000100,
		TOP_RIGHT		= 0b00001000,
		CENTER_LEFT		= 0b00000001,
		CENTER_CENTER	= 0b00000101,
		CENTER_RIGHT	= 0b00001001,
		BOTTOM_LEFT		= 0b00000010,
		BOTTOM_CENTER	= 0b00000110,
		BOTTOM_RIGHT	= 0b00001010	
	};

	Transform2D(
		const DirectX::XMFLOAT4X4* view, 
		const DirectX::XMFLOAT4X4* ortho);
	Transform2D(
		const DirectX::XMFLOAT4X4* view, 
		const DirectX::XMFLOAT4X4* ortho,
		float px, float py,
		float sx, float sy,
		float angle,
		float length, float height);

	virtual void set_position(float x, float y, RELPOS relative_pos = RELPOS::TOP_LEFT);
	virtual void move(float dx, float dy);
	virtual void set_scale(float x, float y);
	virtual void set_rotation(float angle);
	virtual void rotate(float dangle);
	virtual void set_dimension(float length, float height);
	virtual void dimension(float dlength, float dheight);

	virtual void get_position(float& x, float& y) const;
	virtual float get_position_x() const;
	virtual float get_position_y() const;

	virtual void get_scale(float& x, float& y) const;
	virtual float get_scale_x() const;
	virtual float get_scale_y() const;
	
	virtual void get_rotation(float& angle) const;
	virtual float get_angle() const;

	virtual void get_dimension(float& length, float& height) const;
	virtual float get_length() const;
	virtual float get_height() const;

	virtual bool contains(float x, float y) const;
	virtual DirectX::XMMATRIX get_transformation_matrix() const;
	
protected:
	// p ... Position
	float px, py;
	// s ... Scale
	float sx, sy;
	// ... yeah
	float angle;
	// ... yeah
	float length, height;
	// matrices
	DirectX::XMFLOAT4X4 model_matrix;
	const DirectX::XMFLOAT4X4 *view_matrix, *ortho_matrix;

private:
	void recalculate_model_matrix();

private:
	// TODO: this changes whenthe ortho matrix changes --> adjust accordingly
	float screen_half_width, screen_half_height;

};
