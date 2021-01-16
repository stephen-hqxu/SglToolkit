#include "SgTShadowBox.h"

using namespace SglToolkit;

SgTShadowBox::SgTShadowBox(SgTCamera* const camera, const SgTvec3 lightDir, const float nearPlane, const float aspect) : Camera(camera) {
	this->LightDirection = glm::normalize(lightDir);
	this->NEAR_PLANE = nearPlane;
	this->calcViewFrustumPlanes(aspect);
}

SgTShadowBox::~SgTShadowBox() {

}

void SgTShadowBox::calcViewFrustumPlanes(const float aspect) {
	this->farWidth = static_cast<float>(this->SHADOW_DISTANCE * glm::tan(glm::radians(this->Camera->getZoomDeg())));//zoom degree is out FOV
	this->nearWidth = static_cast<float>(this->NEAR_PLANE * glm::tan(glm::radians(this->Camera->getZoomDeg())));
	//the height can be calculated via aspect ratio
	this->farHeight = this->farWidth / aspect;
	this->nearHeight = this->nearWidth / aspect;
}

const SgTvec4* const SgTShadowBox::calcFrustumVertices(SgTmat4 rotation, SgTvec3 forwardVector, SgTvec3 upVector, SgTvec3 centerNear, SgTvec3 centerFar) {
	//allocating spaces for the points
	SgTvec4* const points = new SgTvec4[8];
	//calculate vectors
	const SgTvec3 up = upVector;
	const SgTvec3 right = glm::cross(forwardVector, up);
	const SgTvec3 down = -up;
	const SgTvec3 left = -right;

	const SgTvec3 farTop = centerFar + this->farHeight * up;
	const SgTvec3 farBottom = centerFar + this->farHeight * down;
	const SgTvec3 nearTop = centerNear + this->nearHeight * up;
	const SgTvec3 nearBottom = centerNear + this->nearHeight * down;
	//calculate all the corners
	*(points + 0) = this->calcFrustumCorner(farTop, right, this->farWidth);
	*(points + 1) = this->calcFrustumCorner(farTop, left, this->farWidth);
	*(points + 2) = this->calcFrustumCorner(farBottom, right, this->farWidth);
	*(points + 3) = this->calcFrustumCorner(farBottom, left, this->farWidth);
	*(points + 4) = this->calcFrustumCorner(nearTop, right, this->nearWidth);
	*(points + 5) = this->calcFrustumCorner(nearTop, left, this->nearWidth);
	*(points + 6) = this->calcFrustumCorner(nearBottom, right, this->nearWidth);
	*(points + 7) = this->calcFrustumCorner(nearBottom, left, this->nearWidth);

	return points;
}

const SgTvec4 SgTShadowBox::calcFrustumCorner(SgTvec3 start, SgTvec3 direction, float scale) {
	SgTvec4 corner = SgTvec4(start + scale * direction, 1.0f);
	//now the corner is calculated in world space

	return corner;
}

const SgTvec3 SgTShadowBox::getCenter() {
	//get the mid points of three axis
	float midx = (this->maxX + this->minX) / 2.0f;
	float midy = (this->maxY + this->minY) / 2.0f;
	float midz = (this->maxZ + this->minZ) / 2.0f;
	//the center is in world space
	SgTvec4 center = SgTvec4(midx, midy, midz, 1.0f);
	
	return center;
}

void SgTShadowBox::update(const float aspect) {
	//update the camera view frustum since our camera FOV and aspect ratio may change every frame
	this->calcViewFrustumPlanes(aspect);

	const SgTmat4 rotation = this->getCameraRotation();
	//rotate the forward and up vector to make it align with the camera
	const SgTvec3 forward = SgTvec3(rotation * this->FORWARD);
	const SgTvec3 up = SgTvec3(rotation * this->UP);
	//now we calculate the vector pointing to near and far plane
	const SgTvec3 toNear = forward * this->NEAR_PLANE;
	const SgTvec3 toFar = forward * this->SHADOW_DISTANCE;
	//center plane for the camera view
	const SgTvec3 centerNear = toNear + this->Camera->getPosition();
	const SgTvec3 centerFar = toFar + this->Camera->getPosition();
	//get all the vertices
	const SgTvec4* const points = this->calcFrustumVertices(rotation, forward, up, centerNear, centerFar);
	//we are going to find the maximum and minimum value in both X,Y and Z direction
	bool first = true;
	for (int i = 0; i < 8; i++) {
		if (first) {
			this->maxX = (points + i)->x;
			this->minX = (points + i)->x;
			this->maxY = (points + i)->y;
			this->minY = (points + i)->y;
			this->maxZ = (points + i)->z;
			this->minZ = (points + i)->z;
			first = false;
			continue;
		}
		if ((points + i)->x > this->maxX) {
			this->maxX = (points + i)->x;
		}
		else if ((points + i)->x < this->minX) {
			this->minX = (points + i)->x;
		}

		if ((points + i)->y > this->maxY) {
			this->maxY = (points + i)->y;
		}
		else if ((points + i)->y < this->minY) {
			this->minY = (points + i)->y;
		}

		if ((points + i)->z > this->maxZ) {
			this->maxZ = (points + i)->z;
		}
		else if ((points + i)->z < this->minZ) {
			this->minZ = (points + i)->z;
		}
	}
	this->maxZ += this->OFFSET;

	//clear up
	delete[] points;
}