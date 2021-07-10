#pragma once
#ifndef _SgTShadowBox_H_
#define _SgTShadowBox_H_

#include "./SgTCamera/SgTCamera.h"

/**
 * @brief Simple OpenGL Toolkit
*/
namespace SglToolkit {

	/**
	 * @brief Represents the 3D cuboidal area of the world in which objects will cast
	 * shadows (basically represents the orthographic projection area for the shadow
	 * render pass). It is updated each frame to optimise the area, making it as
	 * small as possible (to allow for optimal shadow map resolution) while not
	 * being too small to avoid objects not having shadows when they should.
	 * Everything inside the cuboidal area represented by this object will be
	 * rendered to the shadow map in the shadow render pass. Everything outside the
	 * area won't be.
	*/
	class SgTShadowBox {
	private:

		//the camera, this needs to be updated in whenever the camera got updated
		SgTCamera* const Camera;
		SgTvec3 LightDirection;

		//parameters that define the shadow box that is bounded by the camera view frustum
		float minX, maxX,
			minY, maxY,
			minZ, maxZ;

		//The dimension of the near and far plane of the camera view frustum (perspective projection)
		float nearWidth, nearHeight, farWidth, farHeight;

		/**
		 * @brief Get the camera rotation matrix by removing the translation from the camera view matrix
		 * @return The camera rotation matrix
		*/
		inline const SgTmat4 getCameraRotation() {
			return SgTmat4(SgTmat3(this->Camera->getViewMat()));
		}

		/**
		 * @brief Calculates the width and height of the near and far planes of the
		 * camera's view frustum. However, this doesn't have to use the "actual" far
		 * plane of the view frustum. It can use a shortened view frustum if desired
		 * by bringing the far-plane closer, which would increase shadow resolution
		 * but means that distant objects wouldn't cast shadows.
		 * @param aspect - The aspect ratio of the camera perspective
		*/
		void calcViewFrustumPlanes(const float);

		/**
		 * @brief Calculates the position of the vertex at each corner of the view frustum
		 * in world space (8 vertices in total, so this returns 8 positions).
		 * @param rotation - camera's rotation.
		 * @param forwardVector - the direction that the camera is aiming, and thus the direction of the frustum.
		 * @param upVector - the direction that the camera's up is aiming, and thus the direction of the up frustum.
		 * @param centerNear - the center point of the frustum's near plane.
		 * @param centerFar - the center point of the frustum's (possibly adjusted) far plane.
		 * @return The positions of the vertices of the frustum in world space.
		 */
		const SgTvec4* const calcFrustumVertices(SgTmat4, SgTvec3, SgTvec3, SgTvec3, SgTvec3);

		/**
		 * @brief Calculates one of the corner vertices of the view frustum in world space
		 * @param startPoint - the starting center point on the view frustum.
		 * @param direction - the direction of the corner from the start point.
		 * @param scale - the distance of the corner from the start point.
		 * @return The relevant corner vertex of the view frustum in world space.
		 */
		const SgTvec4 calcFrustumCorner(SgTvec3, SgTvec3, float);

	public:

		//setting terms
		float OFFSET = 0.0f;
		float SHADOW_DISTANCE = 1.0f;
		float NEAR_PLANE = 1.0f;

		SgTvec4 UP = SgTvec4(0.0f, 1.0f, 0.0f, 0.0f);
		SgTvec4 FORWARD = SgTvec4(0.0f, 0.0f, -1.0f, 0.0f);

		/**
		 * @brief Creates a new shadow box and calculates some initial values relating to
		 * the camera's view frustum, namely the width and height of the near plane
		 * and (possibly adjusted) far plane.
		 * Also to be note that the FOV is determined by the camera zoom degree. And the far plane is determined by SHADOW_DISTANCE
		 * @param camera - The camera for the scene
		 * @param lightDir - The direction of the light. The shadow box will be used to calculated the shadow of
		 * direcional light, e.g., sun light. And the light direction will be thus used to calculate view matrix in light's camera
		 * space.
		 * @param nearPlane - The near plane of the camera
		 * @param aspect - The aspect ratio of the camera perspective
		*/
		SgTShadowBox(SgTCamera* const, const SgTvec3, const float, const float);

		~SgTShadowBox();

		/**
		 * @brief Calculates the center of the "view cuboid" in world space
		 * @return The center of the "view cuboid" in world space.
		 */
		const SgTvec3 getCenter();

		/**
		 * @brief Updates the bounds of the shadow box based on the light direction and the
		 * camera's view frustum, to make sure that the box covers the smallest area
		 * possible while still ensuring that everything inside the camera's view
		 * (within a certain range) will cast shadows.
		 * @param aspect - The aspect ratio of the camera perspective
		*/
		void update(const float);

		/**
		 * @brief Return the width of the shadow box (orthographic projection area).
		 * @return The width
		*/
		inline const float getWidth() {
			return this->maxX - this->minX;
		}

		/**
		 * @brief Return the height of the shadow box (orthographic projection area).
		 * @return The height
		*/
		inline const float getHeight() {
			return this->maxY - this->minY;
		}

		/**
		 * @brief Return the depth(or namely length) of the shadow box (orthographic projection area).
		 * @return The depth
		*/
		inline const float getDepth() {
			return this->maxZ - this->minZ;
		}

		/**
		 * @brief Return the view matrix of the light
		 * @return The light's view matrix
		*/
		inline const SgTmat4 getLightView() {
			const SgTvec3 lightPos = this->Camera->getPosition();//althouh we are using parallel light, the view matrix requires light position
			//so we place the light at a random location in the light direction, and the random location I choose is the cuboid center
			const SgTvec3 lightCenter = lightPos + this->LightDirection;//light direction has already been normlaised
			const SgTvec3 lightRight = glm::normalize(glm::cross(this->LightDirection, SgTvec3(this->UP)));
			const SgTvec3 lightUp = normalize(cross(lightRight, this->LightDirection));

			return glm::lookAt(lightPos, lightCenter, lightUp);
		}

		/**
		 * @brief Return the projection matrix of the light
		 * @return The light's projection matrix
		*/
		inline const SgTmat4 getLightProjection() {
			const float width = this->getWidth();
			const float height = this->getHeight();
			const float depth = this->getDepth();

			return glm::ortho(width * -0.5f, width * 0.5f, height * -0.5f, height * 0.5f, depth * -0.5f, depth * 0.5f);
		}
	};
}
#endif//_SgTShadowBox_H_