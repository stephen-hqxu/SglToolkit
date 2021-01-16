#pragma once
//glm
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"
//system
#include <string>
#include <fstream>
#include <sstream>
//OpenGL engine
#include "glad/glad.h"

typedef glm::vec2 SgTvec2;
typedef glm::vec3 SgTvec3;
typedef glm::vec4 SgTvec4;
typedef glm::mat3 SgTmat3;
typedef glm::mat4 SgTmat4;
typedef std::string SgTstring;

/*
The SgTShaderStatus indicates the status returned when user tries to compile the shader and link their programe
*/
typedef int SgTShaderStatus;
/**
 * @brief Specify the movement of the general camera
*/
typedef unsigned int SgTCameraMovement;
typedef void (*SgTProgramPara)(const GLuint);