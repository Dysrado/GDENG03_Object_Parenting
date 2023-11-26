#include "Camera.h"
#include "InputSystem.h"

Camera::Camera(string name) : AGameObject(name), InputListener()
{
	this->forwardDirection = Vector3D(1.0f, 0.0f, 1.0f);
	this->backwardDirection = Vector3D(-1.0f, 0.0f, -1.0f);

	this->setPosition(0.0f, 0.0f, -4.0f);
	this->UpdateViewMatrix();
	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	m_delta_time = deltaTime;
	UpdateViewMatrix();

	/*Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;
	float moveSpeed = 10.0f;*/

	Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;
	float moveSpeed = 10.0f;

	if (InputSystem::getInstance()->isKeyDown('W')) {
		Vector3D direction = localMatrix.getZDirection();
		Vector3D newPos = Vector3D(
			x + direction.m_x * deltaTime * moveSpeed,
			y + direction.m_y * deltaTime * moveSpeed,
			z + direction.m_z * deltaTime * moveSpeed);

		this->setPosition(newPos.m_x, newPos.m_y, newPos.m_z);
		this->UpdateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		Vector3D direction = localMatrix.getZDirection();
		Vector3D newPos = Vector3D(
			x + direction.m_x * deltaTime * -moveSpeed,
			y + direction.m_y * deltaTime * -moveSpeed,
			z + direction.m_z * deltaTime * -moveSpeed);

		this->setPosition(newPos.m_x, newPos.m_y, newPos.m_z);
		this->UpdateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		Vector3D direction = localMatrix.getXDirection();
		Vector3D newPos = Vector3D(
			x + direction.m_x * deltaTime * -moveSpeed,
			y + direction.m_y * deltaTime * -moveSpeed,
			z + direction.m_z * deltaTime * -moveSpeed);

		this->setPosition(newPos.m_x, newPos.m_y, newPos.m_z);
		this->UpdateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		Vector3D direction = localMatrix.getXDirection();
		Vector3D newPos = Vector3D(
			x + direction.m_x * deltaTime * moveSpeed,
			y + direction.m_y * deltaTime * moveSpeed,
			z + direction.m_z * deltaTime * moveSpeed);

		this->setPosition(newPos.m_x, newPos.m_y, newPos.m_z);
		this->UpdateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('Q')) {
		Vector3D direction = Vector3D(0, 1, 0);
		Vector3D newPos = Vector3D(
			x + direction.m_x * deltaTime * -moveSpeed,
			y + direction.m_y * deltaTime * -moveSpeed,
			z + direction.m_z * deltaTime * -moveSpeed);

		this->setPosition(newPos.m_x, newPos.m_y, newPos.m_z);
		this->UpdateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('E')) {
		Vector3D direction = Vector3D(0, 1, 0);
		Vector3D newPos = Vector3D(
			x + direction.m_x * deltaTime * moveSpeed,
			y + direction.m_y * deltaTime * moveSpeed,
			z + direction.m_z * deltaTime * moveSpeed);

		this->setPosition(newPos.m_x, newPos.m_y, newPos.m_z);
		this->UpdateViewMatrix();
	}
}

void Camera::draw(int width, int height)
{
	
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point deltaPos)
{
	if (isRightClick) {
		m_rot_x = (deltaPos.getY()) * EngineTime::getDeltaTime() * 0.3f;
		m_rot_y = (deltaPos.getX()) * EngineTime::getDeltaTime() * 0.3f;

		setRotation(getLocalRotation().m_x + m_rot_x,
			getLocalRotation().m_y + m_rot_y,
			getLocalRotation().m_z
		);
	}

	
}

void Camera::onLeftMouseDown(const Point deltaPos)
{
}

void Camera::onLeftMouseUp(const Point deltaPos)
{
}

void Camera::onRightMouseDown(const Point deltaPos)
{
	isRightClick = true;
}

void Camera::onRightMouseUp(const Point deltaPos)
{
	isRightClick = false;
}

void Camera::UpdateViewMatrix()
{
	Matrix4x4 worldCam;
	worldCam.setIdentity();
	Matrix4x4 temp;
	temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.m_x);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(localRot.m_y);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(localRot.m_z);
	worldCam *= temp;

	/*temp.setIdentity();
	temp.setRotationX(m_rot_x);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	worldCam *= temp;*/

	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());
	worldCam *= temp;

	this->localMatrix = worldCam;

	worldCam.inverse();

	this->viewMatrix = worldCam;
	
}
