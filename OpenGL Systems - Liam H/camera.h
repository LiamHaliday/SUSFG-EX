#ifndef CAMERA_H
#define CAMERA_H

//definitions
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"


class camera
{
public:

	void draw(GLuint program, GLfloat currentTime, bool spin, float one, float two, float three);
	void drawflat(GLuint program, GLfloat currentTime, bool spin, float one, float two, float three);
//	void 
	
	glm::mat4 getprojectionMatrix(){ return model; };
	glm::mat4 getViewMatrix(){ return view; };

private:

float camerafront = 0.01f;

glm::vec3 cameraPos; // where the camera is 
glm::vec3 cameraFront; // what the camera is looking at
glm::vec3 cameraUp;

glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

int WIDTH = 1600;
int HEIGHT = 1000;

};

#endif