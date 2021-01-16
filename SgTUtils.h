#pragma once
#ifndef _SgTUtils_H_
#define _SgTUtils_H_

#include "define_file.h"
#include <iostream>

/**
 * @brief Simple OpenGL Toolkit
*/
namespace SglToolkit {

	/**
	 * @brief A utility struct for OpenGL that contains some useful constants.
	*/
	struct SgTUtils {
	private:

		/**
		 * @brief This is a full-static struct and should not be instanciated
		*/
		SgTUtils() {

		}

		~SgTUtils() {

		}

	public:

		/**
		 * @brief A unit box model for environment map, the vertex coordinate can be used as texture coordinate
		*/
		constexpr static int UNITBOX_VERTICES[] = {
			// positions and UV         
			-1, -1, -1,//origin
			1, -1, -1,//x=1
			1, -1, 1,//x=z=1
			-1, -1, 1,//z=1
			-1, 1, -1,//y=1
			1, 1, -1,//x=y=1
			1, 1, 1,//x=y=z=1
			-1, 1, 1,//y=z=1
		};

		/**
		 * @brief The indices for the unit box model
		*/
		constexpr static unsigned int UNITBOX_INDICES[] = {
			0, 1, 2,
			0, 2, 3,

			0, 1, 5,
			0, 5, 4,

			1, 2, 6,
			1, 6, 5,

			2, 3, 7,
			2, 7, 6,

			3, 0, 4,
			3, 4, 7,

			4, 5, 6,
			4, 6, 7
		};

		const static unsigned int UNITBOX_INDICES_SIZE = 36;

		/**
		 * @brief A standard quard that prefectly fits the default camera clip space for framebuffer feedback.
		 * Note that the quad is filled in normalied device coordinate
		*/
		constexpr static int FRAMEBUFFER_QUAD[] = {
			// positions   // texCoords
			-1,  1,        0, 1,
			-1, -1,        0, 0,
			 1, -1,        1, 0,

			-1,  1,        0, 1,
			 1, -1,        1, 0,
			 1,  1,        1, 1
		};

		//A unit plane that can be used a patch for terrain
		constexpr static int UNITPLANE_VERTICES[] = {
			//position		//texcoords		//normal	//tangent	//bitangent
			0, 0, 0,		0, 0,			0, 1, 0,	1, 0, 0,	0, 0, -1,
			1, 0, 0,		1, 0,			0, 1, 0,	1, 0, 0,	0, 0, -1,
			1, 0, 1,		1, 1,			0, 1, 0,	1, 0, 0,	0, 0, -1,
			0, 0, 1,		0, 1,			0, 1, 0,	1, 0, 0,	0, 0, -1
		};

		//The indices for the unit plane
		constexpr static unsigned int UNITPLANE_INDICES[] = { 0, 1, 2, 0, 2, 3 };

		//The number of element in the index list of the unit plane
		const static unsigned int UNITPLANE_INDICES_SIZE = 6;

		//The full debug output callback function for the OpenGL debug callback, auto-printed arrived information
		const static void debugOutput(unsigned int src, unsigned int type, unsigned int id, unsigned int severity, int length, const char* log, const void* user_param) {
			auto const src_str = [src]() {
				switch (src) {
				case GL_DEBUG_SOURCE_API: return "API";
					break;
				case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
					break;
				case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
					break;
				case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
					break;
				case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
					break;
				case GL_DEBUG_SOURCE_OTHER: return "OTHER";
					break;
				default: return "NULL";
					break;
				}
			}();

			auto const type_str = [type]() {
				switch (type) {
				case GL_DEBUG_TYPE_ERROR: return "ERROR";
					break;
				case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
					break;
				case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
					break;
				case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
					break;
				case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
					break;
				case GL_DEBUG_TYPE_MARKER: return "MARKER";
					break;
				case GL_DEBUG_TYPE_OTHER: return "OTHER";
					break;
				default: return "NULL";
					break;
				}
			}();

			auto const severity_str = [severity]() {
				switch (severity) {
				case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
					break;
				case GL_DEBUG_SEVERITY_LOW: return "LOW";
					break;
				case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
					break;
				case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
					break;
				default: return "NULL";
					break;
				}
			}();

			std::cout << "------------------------------------New debug output arrived----------------------------" << std::endl;
			std::cout << src_str << "::" << type_str << "::" << severity_str << "::" << id << ": \n" << log << std::endl;
			std::cout << "--------------------------------End of the debug output session-------------------------" << "\n" << std::endl;
		}
	};
}
#endif//_SgTUtils_H_