#pragma once
#ifndef _SgTShaderProc_H_
#define _SgTShaderProc_H_

#include "SgTDefineFile.h"

/**
 * @brief Simple OpenGL Toolkit
*/
namespace SglToolkit {

	/*
	Shader processor, used to import and compile shader.
	It will throws out the error if compile has failed.
	*/
	class SgTShaderProc {
	private:

		/*
		Storing programe ID, vertex shader ID, tessellation control shader ID,
		tessellation evaluation ID, geometry shader ID, fragment shader ID and compute shader respectively
		*/
		GLuint shaderHandle[7] = { 0, 0, 0, 0, 0, 0, 0 };
		/**
		 * @brief Check if the shader is used
		*/
		bool shaderused[6] = { false, false, false, false, false, false };

		/*
		Check if the GLSL compiler throws any errors
		If the "isShader" is true, function will check the shader compiler or otherwise program linkage.
		@param GLuint shader - The shader that needs to be checked
		@param bool isShader - if the checked item is a shader or programe
		@param GLchar*& log - a reference that stores log if compile is not successful. Needs to be allocated space.
		 * @param bufferSize The size of the buffer that is allocated for the log
		@return True if compiler does not return any error
		*/
		const bool debugCompile(GLuint, bool, GLchar*&, const int);

	public:

		//Error codes
		static const SgTShaderStatus OK = 200;
		static const SgTShaderStatus VERTEX_SHADER_ERR = 401;
		static const SgTShaderStatus TESS_CONTROL_SHADER_ERR = 402;
		static const SgTShaderStatus TESS_EVALUATION_SHADER_ERR = 403;
		static const SgTShaderStatus GEOMETRY_SHADER_ERR = 404;
		static const SgTShaderStatus FRAGMENT_SHADER_ERR = 405;
		static const SgTShaderStatus COMPUTE_SHADER_ERR = 406;
		static const SgTShaderStatus PROGRAME_LINKING_ERR = 407;

		/*
		Initialse the ShaderProc class, this operation will create a programe
		*/
		SgTShaderProc();

		/*
		Terminate the class, delete all in used shaders and programe
		*/
		~SgTShaderProc();

		/*
		Import the shader code and add to a new shader, shader is not compiled.
		Throw exception If the GLenum is invalid, or computational shader is mixed with graphical shader
		@param const GLenum type - The type of shader
		@param const string path - The path where the shader code is stored
		@return nothing
		*/
		void addShader(const GLenum, const SgTstring);

		/**
		 * @brief Compile all shaders that have been set and link to the programe
		 * @param GLchar*& log - The error log if error occurs
		 * @param bufferSize The size of the buffer that is allocated for the log
		 * @param arg The argument for the program before the program is linked, supplied with a callback function
		 * @return The status of compilation and linkage
		*/
		SgTShaderStatus linkShader(GLchar*&, const int, SgTProgramPara = NULL);

		/**
		 * @brief Delete the current program and all linked shader, after which the ShaderProc will be reset and can be reused
		*/
		void deleteShader();

		/*
		Read the shader code from the path
		@param const string Path - the path that the code is stored
		@return const char* The entire code contains within the file
		*/
		const static SgTstring readCode(const SgTstring);

		/*
		Get the programe ID
		@return the ID of the programe
		*/
		const int getP() const;

		/*
		Get the vertex shader ID
		@return the ID of the vertex shader
		*/
		const int getVS() const;

		/*
		Get the tessellation control shader ID
		@return the ID of the tessellation control shader
		*/
		const int getTCS() const;

		/*
		Get the tessellation evaluation shader ID
		@return the ID of the tessellation evaluation shader
		*/
		const int getTES() const;

		/*
		Get the geometry shader ID
		@return the ID of the geometry shader*/
		const int getGS() const;

		/*
		Get the fragment shader ID
		@return the ID of the fragment shader
		*/
		const int getFS() const;

	};
}
#endif//_SgTShaderProc_H_