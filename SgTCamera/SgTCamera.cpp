#include "SgTCamera.h"

using namespace SglToolkit;

SgTCamera::SgTRange::SgTRange(float min, float max) {
	this->min = min;
	this->max = max;
}

SgTCamera::SgTRange::~SgTRange() {

}

SgTCamera::SgTCamera(const float yaw, const float pitch, const float movementSpeed,
	const float mouseSens, const float zoom, const SgTvec3 position, const SgTvec3 up, const SgTvec3 front) : World_Up(up){
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->MovementSpeed = movementSpeed;
	this->MouseSensitivity = mouseSens;
	this->Zoom = zoom;
	this->Position = position;
	this->Front = front;
	//right and up are calculated
}

SgTCamera::~SgTCamera() {

}

const SgTmat4 SgTCamera::getViewMat() {
	return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}