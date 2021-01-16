#pragma once
#ifndef _SgTCamera_H_
#define _SgTCamera_H_

#include "../define_file.h"

/**
 * @brief Simple OpenGL Toolkit
*/
namespace SglToolkit {

	/**
	 * @brief Base camera with full abstraction, a general camera class contains the basic properties of a camera such as Position, Front and Up.
	 * Using this camera class to develop other types of camera, with independent implementations.
	*/
	class SgTCamera {
	public:

		/**
		 * @brief Specify a range of data that contains min and max variables
		*/
		struct SgTRange {
		public:

			//The minimum and maximum range
			float min, max;

			/**
			 * @brief Initialise the range struct
			 * @param min The minimum range
			 * @param max The maximum range
			*/
			SgTRange(float, float);

			~SgTRange();

		};

	protected:

		//Default camera attributes
		static constexpr float YAW = -90.0f;
		static constexpr float PITCH = 0.0f;
		static constexpr float MOVEMENTSPEED = 2.5f;
		static constexpr float MOUSESENSITIVITY = 0.1f;
		static constexpr float ZOOM = 45.0f;
		inline static const SgTRange LIMIT_ZOOM = SgTCamera::SgTRange(1.0f, 180.0f);

		static constexpr SgTvec3 POSITION = SgTvec3(0.0f, 0.0f, 0.0f);
		static constexpr SgTvec3 WORLD_UP = SgTvec3(0.0f, 1.0f, 0.0f);
		static constexpr SgTvec3 FRONT = SgTvec3(0.0f, 0.0f, -1.0f);
		//Camera attributes
		float Yaw, Pitch, MovementSpeed, MouseSensitivity, Zoom;
		SgTvec3 Position, Front, Up, Right;
		const SgTvec3 World_Up;

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
		SgTCamera(const float = SgTCamera::YAW, const float = SgTCamera::PITCH,
			const float = SgTCamera::MOVEMENTSPEED, const float = SgTCamera::MOUSESENSITIVITY, const float = SgTCamera::ZOOM,
			const SgTvec3 = SgTCamera::POSITION, const SgTvec3 = SgTCamera::WORLD_UP, const SgTvec3 = SgTCamera::FRONT);

		~SgTCamera();

		/**
		 * @brief Update the camera direction for the keyboard input
		 * @param direction The direction of movement
		 * @param deltaTime Frame-based timer, the speed of the movement will also be controlled by the FPS. Providing value of 1 can disable the feature
		*/
		virtual void keyUpdate(const SgTCameraMovement, const float) = 0;

		/**
		 * @brief Update the yaw and pitch value using the mouse position and how much the mouse has moved compare to last frame
		 * @param Xpos The X position of the mouse
		 * @param Ypos The Y position of the mouse
		 * @param limitPitch If set to true, pitch will not go pass 90.0
		*/
		virtual void mouseUpdate(const float, const float, const bool) = 0;

		/**
		 * @brief Update the zooming level
		 * @param Yoffset The input scrolling offset
		 * @param limitZoom If set then the zoom will be limited
		*/
		virtual void scrollUpdate(const float, const SgTRange) = 0;

		/**
		 * @brief Return the look at camera matrix for the camera
		 * @return The lookat matrix
		*/
		virtual const SgTmat4 getViewMat();

		/**
		 * @brief Get the current camera front vector
		 * @return Camera front
		*/
		inline const SgTvec3 getFront() {
			return this->Front;
		}

		/**
		 * @brief Get the current camera up vector
		 * @return camera up
		*/
		inline const SgTvec3 getUp() {
			return this->Up;
		}
		/**
		 * @brief Get the current camera position vector
		 * @return camera position
		*/
		inline const SgTvec3 getPosition() {
			return this->Position;
		}

		/**
		 * @brief Get the current camera yaw in degree
		 * @return Camera yaw in degree
		*/
		inline const float getYaw() {
			return this->Yaw;
		}

		/**
		 * @brief Get the current camera pitch in degree
		 * @return Camera pitch in degree
		*/
		inline const float getPitch() {
			return this->Pitch;
		}

		/**
		 * @brief Get the current camera zooming level, in degree
		 * @return camera zoom
		*/
		inline const float getZoomDeg() {
			return this->Zoom;
		}

	};
}
#endif//_SgTCamera_H_