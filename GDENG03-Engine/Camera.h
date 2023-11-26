#pragma once
#include "AGameObject.h"
#include "InputListener.h"

class Camera : public AGameObject, public InputListener
{
public:
	Camera(string name);
	~Camera();

	void update(float deltaTime) override;
	virtual void draw(int width, int height) override;
	Matrix4x4 getViewMatrix();

	//Input Listnere
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point deltaPos);

	virtual void onLeftMouseDown(const Point deltaPos);
	virtual void onLeftMouseUp(const Point deltaPos);

	virtual void onRightMouseDown(const Point deltaPos);
	virtual void onRightMouseUp(const Point deltaPos);

private:
	void UpdateViewMatrix();


	//Added Template
	float m_delta_time;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;
	Vector3D forwardDirection;
	Vector3D backwardDirection;
	Matrix4x4 viewMatrix;
	Matrix4x4 m_world_cam;
	bool isRightClick = false;


};

