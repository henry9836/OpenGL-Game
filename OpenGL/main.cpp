#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>   
#include <time.h>
#include "ShaderLoader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

float r = 1.0;
float b = 1.0;
float g = 1.0;

//GLOBAL Verts

GLuint hexpro = NULL;
GLuint quadpro = NULL;
GLuint Hex = NULL;
GLuint Quad = NULL;
GLuint hexVAO;
GLuint hexVBO;
GLuint hexEBO;
GLuint quadVAO;
GLuint quadVBO;
GLuint quadEBO;
GLuint texture;
GLuint texture1;

GLuint firePro = NULL;
GLuint toasterPro = NULL;
GLuint babyPro = NULL;
GLuint fireVAO = NULL;
GLuint fireVBO = NULL;
GLuint fireEBO = NULL;
GLuint toasterVAO = NULL;
GLuint toasterVBO = NULL;
GLuint toasterEBO = NULL;
GLuint babyVAO = NULL;
GLuint babyVBO = NULL;
GLuint babyEBO = NULL;
GLuint fireTex = NULL;
GLuint toasterTex = NULL;
GLuint babyTex = NULL;

glm::vec3 firePos = glm::vec3(0.1f, 0.1f, 0.0f);
glm::mat4 fireTransMat = glm::translate(glm::mat4(), firePos);
glm::vec3 rotZ = glm::vec3(0.0f, 0.0f, 1.0f);

float rotationAngle = 180;
float currentTime;

glm::mat4 fireRot = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotZ);

/* CAMERA */
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);

GLuint fireIndices[] = {
	0, 1, 2,
	2, 3, 0,
};

GLfloat fireVerts[] = {
	0.65f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//top right		0
	-0.65f, 0.5f, 0.0f,	1.0f, 0.0f, 1.0f,	0.0f, 0.0f,		//top left		1
	-0.65f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,		//bottom left	2
	0.65f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		//bottom right	3
};

GLuint babyIndices[] = {
	0, 1, 2,
	2, 3, 0,
};

GLfloat babyVerts[] = {
	0.85f, 0.75f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//top right		0
	-0.85f, 0.75f, 0.0f,	1.0f, 0.0f, 1.0f,	0.0f, 0.0f,		//top left		1
	-0.85f, -0.75f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,		//bottom left	2
	0.85f, -0.75f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		//bottom right	3
};

GLuint hexIndices[] = {
	0, 1, 2,
	2, 3, 4,
	4, 5, 0,
	0, 2, 4,
};

GLfloat hexVerts[] = {
	0.7f, -0.9f, 0.0f,	1.0f, 0.0f, 0.0f, //bottom right	0
	0.85f, -0.7f, 0.0f,	1.0f, 0.0f, 1.0f, //right			1
	0.7f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, //top right		2
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, //top left		3
	0.35f, -0.7f, 0.0f,	1.0f, 1.0f, 0.0f, //left			4
	0.5f, -0.9f, 0.0f,	1.0f, 0.4f, 0.0f, //bottom left		5
};

GLuint quadIndices[] = {
	0, 1, 2,
	2, 3, 0,
};

GLfloat quadVerts[] = {
	0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//top right		0
	-0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 1.0f,	0.0f, 0.0f,		//top left		1
	-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,		//bottom left	2
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		//bottom right	3
};


void Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	//r = (rand() % 10 + 1)/10.0f;
	//g = (rand() % 10 + 1)/10.0f;
	//b = (rand() % 10 + 1)/10.0f;
	r = 0.0f;
	glClearColor(r, g, b, 1.0);

	/* QUAD */

	//glUseProgram(quadpro);

	//glm::mat4 rotMat = glm::rotate(glm::mat4(), glm::radians(50.0f * currentTime), glm::vec3(0, 1, 0));
	glm::vec4 newPos = /*rotMat **/ glm::vec4(0, 0, 3, 1);
	camPos = glm::vec3(newPos);

	glm::mat4 view;
	glm::vec3 camTar = glm::vec3(0.0f, 0.0f, 0.0f);
	view = glm::lookAt(camPos, camTar, camUpDir);

	glm::mat4 proj;
	proj = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	glm::vec3 objPosition = glm::vec3(0.5f, 0.5f, 0.0f);
	//objPosition += objPos;
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPosition);

	glm::vec3 rotationAxisZ = glm::vec3(1.0f, 0.0f, 0.0f);
	float rotationAngle = 0;
	//float rotationAngle = 45;
	glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxisZ);

	glm::vec3 objscale = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), objscale);

	glm::mat4 model = translationMatrix * rotationZ * scaleMatrix;

	glm::mat4 proj_calc = proj * view * model;
	/*GLuint mvpLoc = glGetUniformLocation(quadpro, "proj_calc");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(proj_calc));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(quadpro, "tex"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(quadpro, "tex1"), 1);
	glBindVertexArray(quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	/* HEX */
	/*
	glUseProgram(hexpro);
	GLint currentTimeLoc = glGetUniformLocation(hexpro, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);
	glBindVertexArray(hexVAO);
	glRotatef(90, 0, 1, 0);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);*/

	/* FIRE */
	/*
	glUseProgram(firePro);
	GLuint mvpLoc2 = glGetUniformLocation(firePro, "proj_calc");
	glUniformMatrix4fv(mvpLoc2, 1, GL_FALSE, glm::value_ptr(proj_calc));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(firePro, "tex"), 0);
	glBindVertexArray(fireVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);*/

	/* BABY */
	
	glUseProgram(babyPro);
	GLuint mvpLoc3 = glGetUniformLocation(babyPro, "proj_calc");
	glUniformMatrix4fv(mvpLoc3, 1, GL_FALSE, glm::value_ptr(proj_calc));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(babyPro, "tex"), 0);
	glBindVertexArray(babyVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	glutSwapBuffers();
}

void Update() {
	currentTime = (float)glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime * 0.001f;
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	srand((unsigned int)time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(700, 500);
	glutCreateWindow("Summ 2 ~ Henry Oliver");

	if (glewInit() != GLEW_OK) {
		std::cout << "Glew INIT FAILED";
		system("pause");
	}

	glClearColor(1.0, 0.0, 0.0, 1.0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height;

	/* FIRE */

	unsigned char* fireImage = SOIL_load_image("Resources/fire.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, fireImage);
	
	/* TEXTURE MAGIC */

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SOIL_free_image_data(fireImage);
	glBindTexture(GL_TEXTURE_2D, 0);

	/* CREATE PROGRAMS */

	firePro = ShaderLoader::CreateProgram("Resources/fire.vs", "Resources/fire.fs");

	glGenVertexArrays(1, &fireVAO);
	glBindVertexArray(fireVAO);

	glGenBuffers(1, &fireEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fireEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fireIndices), fireIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &fireVBO);
	glBindBuffer(GL_ARRAY_BUFFER, fireVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fireVerts), fireVerts, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);



	/* BABY */

	unsigned char* babyImage = SOIL_load_image("Resources/baby.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, babyImage);

	/* TEXTURE MAGIC */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SOIL_free_image_data(babyImage);
	glBindTexture(GL_TEXTURE_2D, 0);

	/* CREATE PROGRAMS */

	firePro = ShaderLoader::CreateProgram("Resources/baby.vs", "Resources/baby.fs");

	glGenVertexArrays(1, &babyVAO);
	glBindVertexArray(babyVAO);

	glGenBuffers(1, &babyEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, babyEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(babyIndices), babyIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &babyVBO);
	glBindBuffer(GL_ARRAY_BUFFER, babyVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(babyVerts), babyVerts, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);



	/*

	unsigned char* image = SOIL_load_image("Resources/FRAME1.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	unsigned char* image2 = SOIL_load_image("Resources/FRAME2.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 1);


	hexpro = ShaderLoader::CreateProgram("Resources/hex.vs", "Resources/hex.fs");
	quadpro = ShaderLoader::CreateProgram("Resources/quad.vs", "Resources/quad.fs");

	glGenVertexArrays(1, &hexVAO);
	glBindVertexArray(hexVAO);

	glGenBuffers(1, &hexEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hexEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hexIndices), hexIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &hexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, hexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(hexVerts), hexVerts, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);



	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);

	glGenBuffers(1, &quadEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	*/

	glutDisplayFunc(Render);

	glutIdleFunc(Update);

	glutMainLoop();

	return 0;
}