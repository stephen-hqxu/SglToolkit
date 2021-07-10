#include "SgTShaderProc.h"

using namespace SglToolkit;

SgTShaderProc::SgTShaderProc() {

}

SgTShaderProc::~SgTShaderProc() {
	
}

void SgTShaderProc::addShader(const GLenum type, const SgTstring path) {
	//Determine which shader is that
	int handleIndex = 1;
	switch (type) {
	case GL_VERTEX_SHADER: handleIndex = 1;
		break;
	case GL_TESS_CONTROL_SHADER: handleIndex = 2;
		break;
	case GL_TESS_EVALUATION_SHADER: handleIndex = 3;
		break;
	case GL_GEOMETRY_SHADER: handleIndex = 4;
		break;
	case GL_FRAGMENT_SHADER: handleIndex = 5;
		break;
	case GL_COMPUTE_SHADER: handleIndex = 6;
		break;
	default: throw "InvalidGLenumException";
		break;
	}

	//Start working
	//Read the code from file
	const SgTstring scode = SgTShaderProc::readCode(path);
	const char* code = scode.c_str();
	//We don't need to worry about whether the file exits or not since the readCode function has done that
	//Generating shader
	this->shaderHandle[handleIndex] = glCreateShader(type);
	this->shaderused[handleIndex - 1] = true;
	//adding the source file
	glShaderSource(this->shaderHandle[handleIndex], 1, &code, NULL);

	//Finished
}

SgTShaderStatus SgTShaderProc::linkShader(GLchar* log, const int bufferSize, SgTProgramPara arg) {
	if (this->shaderHandle[0] == 0) {//check if we have a programe
		//create the programe
		this->shaderHandle[0] = glCreateProgram();
	}
	//Compile all shaders that have been created
	for (int i = 1; i < 7; i++) {//shader start from 1

		if (this->shaderused[i - 1]) { //if shader exists
			//compile it
			glCompileShader(this->shaderHandle[i]);
			//check for error
			if (!this->debugCompile(this->shaderHandle[i], true, log, bufferSize)) {//if error occurs
				//return to user which shader causes the error
				return this->VERTEX_SHADER_ERR + (i - 1);//this will effectively output the shader we are looping
			}

			//No error? attach shaders to programe
			glAttachShader(this->shaderHandle[0], this->shaderHandle[i]);
			
		}
	}

	//user-set program parameter
	if (arg != NULL) {//meaning user has set the program parameter
		(*arg)(this->getP());
	}

	//We have attached all shaders, now link the programe
	glLinkProgram(this->shaderHandle[0]);
	//check for error
	if (!this->debugCompile(this->shaderHandle[0], false, log, bufferSize)) {
		return this->PROGRAME_LINKING_ERR;
	}

	//everything works fine
	return this->OK;
	//we will delete the shader source when the class got destructed just in case we need to re-attach it
}

void SgTShaderProc::deleteShader() {
	glUseProgram(0);
	if (this->shaderHandle[0] != 0) {//checking for programe existance
		//detach all shader and delete them
		for (int i = 1; i < 7; i++) {
			if (this->shaderused[i - 1]) {//shader exists
				glDetachShader(this->shaderHandle[0], this->shaderHandle[i]);
				glDeleteShader(this->shaderHandle[i]);

				this->shaderused[i - 1] = false;
				this->shaderHandle[i] = 0;
			}
		}
		//delete the programe
		glDeleteProgram(this->shaderHandle[0]);
		this->shaderHandle[0] = 0;//clear up the pointer such that it can be reused
	}
}

const SgTstring SgTShaderProc::readCode(const SgTstring Path) {
	//return value
	SgTstring code;
	//create the file stream
	std::fstream file;
	std::stringstream stream;

	file.open(Path, std::ios_base::in);
	file.exceptions(std::fstream::failbit | std::fstream::badbit);//make sure there is no exceptions
	stream << file.rdbuf();
	code = stream.str();

	//finishing up
	file.close();

	return code;
}

const bool SgTShaderProc::debugCompile(GLuint shader, bool isShader, GLchar* log, const int bufferSize) {
	//variables
	GLint success;

	if (isShader) {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, bufferSize, NULL, log);
			return false;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, bufferSize, NULL, log);
			return false;
		}
	}

	return true;
}

const int SgTShaderProc::getP() const {
	return this->shaderHandle[0];
}

const int SgTShaderProc::getVS() const {
	return this->shaderHandle[1];
}

const int SgTShaderProc::getTCS() const {
	return this->shaderHandle[2];
}

const int SgTShaderProc::getTES() const {
	return this->shaderHandle[3];
}

const int SgTShaderProc::getGS() const {
	return this->shaderHandle[4];
}

const int SgTShaderProc::getFS() const {
	return this->shaderHandle[5];
}