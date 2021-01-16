#pragma once
#ifndef _SgTSpectatorCamera_H_
#define _SgTSpectatorCamera_H_

#include "SgTCamera.h"

/**
 * @brief Simple OpenGL Toolkit
*/
namespace SglToolkit {

	/**
	 * @brief The spectator camera class that provides the spectator movement for the camera
	 * The camera moving direction will totally depended on the camera facing direction
	*/
	class SgTSpectatorCamera : public SgTCamera{
	public:

		//Camera movement flags
		static const SgTCameraMovement FORWARD = 100u;
		static const SgTCameraMovement BACKWARD = 101u;
		static const SgTCameraMovement LEFT = 102u;
		static const SgTCameraMovement RIGHT = 103u;
		static const SgTCameraMovement UP = 104u;
		static const SgTCameraMovement DOWN = 105u;

	private:

		/**
		 * @brief Calculate and update the camera vectors like front, up and right vectors using the existing yaw and pitch values
		*/
		void calcCameraVector();

		/**
		 * @brief Process mouse movement to update the pitch and yaw value
		 * @param Xoffset The amount of mouse moved in X
		 * @param Yoffset The amount of mouse moved in Y
		 * @param limitPitch If set to true, pitch will not go pass 90.0
		*/
		void procMouseMov(float, float, const bool);

	public:

		/**
		 * @brief Initialise the camera.
		 * @param yaw The initial yaw value for the camera
		 * @param pitch The initial pitch value for the camera
		 * @param movementSpeed The movement speed of the camera
		 * @param mouseSens The sensitivity of the mouse movement
		 * @param zoom The initialial zoom degree for the camera
		 * @param position The initial position vector for the camera
		 * @param up The initial up vector for the camera
		 * @param front The initial front vector for the camera
		*/
		SgTSpectatorCamera(const float = SgTCamera::YAW, const float = SgTCamera::PITCH,
			const float = SgTCamera::MOVEMENTSPEED, const float = SgTCamera::MOUSESENSITIVITY, const float = SgTCamera::ZOOM,
			const SgTvec3 = SgTCamera::POSITION, const SgTvec3 = SgTCamera::WORLD_UP, const SgTvec3 = SgTCamera::FRONT);

		/*
		Finish up the camera class
		*/
		~SgTSpectatorCamera();

		//These are camera callback functions

		/**
		 * @brief Update the camera direction for the keyboard input
		 * @param direction The direction of movement
		 * @param deltaTime Frame-based timer, the speed of the movement will also be controlled by the FPS. Providing value of 1 can disable the feature
		*/
		void SgTCamera::keyUpdate(const SgTCameraMovement, const float);

		/**
		 * @brief Update the yaw and pitch value using the mouse position and how much the mouse has moved compare to last frame
		 * @param Xpos The X position of the mouse
		 * @param Ypos The Y position of the mouse
		 * @param limitPitch If set to true, pitch will not go pass 90.0
		*/
		void SgTCamera::mouseUpdate(const float, const float, const bool);

		/**
		 * @brief Update the zooming level
		 * @param Yoffset The input scrolling offset
		 * @param limitZoom If set then the zoom will be limited
		*/
		void SgTCamera::scrollUpdate(const float, const SgTRange = SgTCamera::LIMIT_ZOOM);

	};
}
#endif//_SgTSpectatorCamera_H_