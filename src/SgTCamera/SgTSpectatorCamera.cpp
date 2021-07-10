#include "SgTCamera/SgTSpectatorCamera.h"

using namespace SglToolkit;

SgTSpectatorCamera::SgTSpectatorCamera(const float yaw, const float pitch, const float movementSpeed,
	const float mouseSens, const float zoom, const SgTvec3 position, const SgTvec3 up, const SgTvec3 front)
	: SgTCamera(yaw, pitch, movementSpeed, mouseSens, zoom, position, up, front) {
	//initialse values
	this->calcCameraVector();
}

SgTSpectatorCamera::~SgTSpectatorCamera() {

}

void SgTSpectatorCamera::calcCameraVector() {
	//calculate the front base on the yaw and pitch
	SgTvec3 newFront;
	newFront.x = glm::cos(glm::radians(this->Yaw)) * glm::cos(glm::radians(this->Pitch));
	newFront.y = glm::sin(glm::radians(this->Pitch));
	newFront.z = glm::sin(glm::radians(this->Yaw)) * glm::cos(glm::radians(this->Pitch));
	//update the new front
	this->Front = glm::normalize(newFront);
	//update the right and up
	// normalize the Right vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->Right = glm::normalize(glm::cross(this->Front, this->World_Up));
	this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}

void SgTSpectatorCamera::procMouseMov(float Xoffset, float Yoffset, const bool limitPitch = true) {
	//using sensitivity to scale the offsets
	Xoffset *= this->MouseSensitivity;
	Yoffset *= this->MouseSensitivity;
	//update the pitch and yaw
	this->Yaw += Xoffset;
	this->Pitch += Yoffset;

	if (this->Yaw >= 360.0f) {
		this->Yaw = 0.0f;
	}
	if (this->Yaw <= -360.0f) {
		this->Yaw = 0.0f;
	}
	//make the limit works, do not allow pitch to go pass +-90
	if (limitPitch) {
		if (this->Pitch > 89.0f) {
			this->Pitch = 89.0f;
		}
		if (this->Pitch < -89.0f) {
			this->Pitch = -89.0f;
		}
	}

	//update the front, right and up
	this->calcCameraVector();
}

void SgTSpectatorCamera::keyUpdate(const SgTCameraMovement direction, const float deltaTime) {
	//scale the movement speed with the frame time
	float velocity = this->MovementSpeed * deltaTime;

	//super easy to understand
	switch (direction) {
	case SgTSpectatorCamera::FORWARD: this->Position += this->Front * velocity;
		break;
	case SgTSpectatorCamera::BACKWARD: this->Position -= this->Front * velocity;
		break;
	case SgTSpectatorCamera::LEFT: this->Position -= this->Right * velocity;
		break;
	case SgTSpectatorCamera::RIGHT: this->Position += this->Right * velocity;
		break;
	case SgTSpectatorCamera::UP: this->Position += SgTCamera::WORLD_UP * velocity;
		break;
	case SgTSpectatorCamera::DOWN: this->Position -= SgTCamera::WORLD_UP * velocity;
		break;
	default:
		break;
	}
}

void SgTSpectatorCamera::mouseUpdate(const float Xpos, const float Ypos, const bool limitPitch) {
	//The first time the programe runs, last position will be initialised
	static float lastX = Xpos;
	static float lastY = Ypos;

	//we reverse Y since Y goes from bottom to top (from negative axis to positive)
	this->procMouseMov(Xpos - lastX, lastY - Ypos, limitPitch);
	//update the last position
	lastX = Xpos;
	lastY = Ypos;
}

void SgTSpectatorCamera::scrollUpdate(const float Yoffset, const SgTRange limitZoom) {
	//we only need the y axis, and the y is counted from negative to positive so we use minus.
	this->Zoom -= Yoffset;
	//limit the zoom
	if (this->Zoom < limitZoom.min) {
		this->Zoom = limitZoom.min;
	}
	if (this->Zoom > limitZoom.max) {
		this->Zoom = limitZoom.max;
	}
}