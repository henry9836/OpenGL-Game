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
#include "ScreenInfo.h"
#include "Camera.h"
#include "Audio.h"
#include "TextLabel.h"
#include "GamerManager.h"
#include "ObjectManager.h"

float r = 1.0;
float b = 1.0;
float g = 1.0;

//GLOBAL Classes

Camera m_Cam;
ScreenInfo m_Screen;
AudioSystem m_Audio;
TextLabel m_Score;
TextLabel m_GameOverText;
TextLabel m_MainText;
GameManager m_Game;
ObjectManager m_ObjManager;

//GLOBAL VARS

//GLuint hexpro = NULL;
//GLuint quadpro = NULL;
//GLuint Hex = NULL;
//GLuint Quad = NULL;
//GLuint hexVAO;
//GLuint hexVBO;
//GLuint hexEBO;
//GLuint quadVAO;
//GLuint quadVBO;
//GLuint quadEBO;

GLuint fireTexture = NULL;
GLuint babyTexture = NULL;
GLuint toasterTexture = NULL;
GLuint backgroundTexture = NULL;

GLuint firePro = NULL;
GLuint toasterPro = NULL;
GLuint babyPro = NULL;
GLuint backgroundPro = NULL;

GLuint fireVAO = NULL;
GLuint fireVBO = NULL;
GLuint fireEBO = NULL;
GLuint toasterVAO = NULL;
GLuint toasterVBO = NULL;
GLuint toasterEBO = NULL;
GLuint babyVAO = NULL;
GLuint babyVBO = NULL;
GLuint babyEBO = NULL;
GLuint backVAO = NULL;
GLuint backVBO = NULL;
GLuint backEBO = NULL;


glm::vec3 firePos = glm::vec3(0.1f, 0.1f, 0.0f);
glm::mat4 fireTransMat = glm::translate(glm::mat4(), firePos);
glm::vec3 rotZ = glm::vec3(0.0f, 0.0f, 1.0f);

float rotationAngle = 0;
float currentTime;
float deltaTime;
float pasttime;

bool BackTrackPlaying = false;

glm::mat4 fireRot = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotZ);

/* CAMERA */
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);


GLuint backIndices[] = {
	0, 1, 2,
	2, 3, 0,
};

GLfloat backVerts[] = {
	1.0f, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//top right		0
	-1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 1.0f,	0.0f, 0.0f,		//top left		1
	-1.0f, -1.0f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,		//bottom left	2
	1.0f, -1.0f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		//bottom right	3
};

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

	r = (rand() % 10 + 1)/10.0f;
	g = (rand() % 10 + 1)/10.0f;
	b = (rand() % 10 + 1)/10.0f;
	
	glClearColor(r, g, b, 1.0);

	/* CAMERA */

	m_Cam.calculate();

	glm::mat4 proj;
	//proj = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	float halfw = (float)m_Screen.SCR_WIDTH * 0.5f;
	float halfh = (float)m_Screen.SCR_HEIGHT * 0.5f;
	proj = glm::ortho(-halfw, halfw, -halfh, halfh, 0.1f, 100.0f);

	glm::vec3 fireObjPosition = glm::vec3(-150.0f, 0.0f, 0.0f);
	glm::vec3 babyObjPosition = glm::vec3(150.0f, 0.0f, 0.0f);
	glm::vec3 backObjPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	m_ObjManager.movement(m_Audio, deltaTime, m_Screen.SCR_WIDTH, m_Screen.SCR_HEIGHT);

	babyObjPosition += m_ObjManager.GetObjectPos();

	glm::mat4 fireTranslationMatrix = glm::translate(glm::mat4(), fireObjPosition);
	glm::mat4 babyTranslationMatrix = glm::translate(glm::mat4(), babyObjPosition);
	glm::mat4 backTranslationMatrix = glm::translate(glm::mat4(), backObjPosition);

	glm::vec3 rotationAxisZ = glm::vec3(1.0f, 0.0f, 0.0f);
	float rotationAngle = 0;
	glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxisZ);

	glm::vec3 objscale = glm::vec3(90.0f, 90.0f, 90.0f);
	glm::vec3 objscaleBack = glm::vec3(350.0f, 350.0f, 350.0f);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), objscale);
	glm::mat4 scaleMatrixBack = glm::scale(glm::mat4(), objscaleBack);

	glm::mat4 babyModel = babyTranslationMatrix * rotationZ * scaleMatrix;
	glm::mat4 fireModel = fireTranslationMatrix * rotationZ * scaleMatrix;
	glm::mat4 backModel = backTranslationMatrix * rotationZ * scaleMatrixBack;

	glm::mat4 fireProj_calc = proj * m_Cam.view * fireModel;
	glm::mat4 babyProj_calc = proj * m_Cam.view * babyModel;
	glm::mat4 backProj_calc = proj * m_Cam.view * backModel;

	/* BACKROUND */

	glUseProgram(backgroundPro);
	GLuint mvpLoc2 = glGetUniformLocation(backgroundPro, "proj_calc");
	glUniformMatrix4fv(mvpLoc2, 1, GL_FALSE, glm::value_ptr(backProj_calc));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glUniform1i(glGetUniformLocation(backgroundPro, "tex"), 0);
	glBindVertexArray(backVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	if (!m_Game.gameover && m_Game.currentScreen == m_Game.MAIN) {
		
		m_Game.currentScreen = m_Game.GAME;
		system("pause");
	}

	else if (!m_Game.gameover && m_Game.currentScreen == m_Game.GAME) {

		/* BABY */

		glUseProgram(babyPro);
		GLuint mvpLoc3 = glGetUniformLocation(babyPro, "proj_calc");
		glUniformMatrix4fv(mvpLoc3, 1, GL_FALSE, glm::value_ptr(babyProj_calc));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, babyTexture);
		glUniform1i(glGetUniformLocation(babyPro, "tex"), 0);
		glBindVertexArray(babyVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		/* FIRE */

		glUseProgram(firePro);
		GLuint mvpLoc1 = glGetUniformLocation(firePro, "proj_calc");
		glUniformMatrix4fv(mvpLoc1, 1, GL_FALSE, glm::value_ptr(fireProj_calc));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fireTexture);
		glUniform1i(glGetUniformLocation(firePro, "tex"), 0);
		glBindVertexArray(fireVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		/* TEXT */

		m_Score.Render();

	}

	else {
		m_GameOverText.Render();
		m_Score.SetPosition(glm::vec2(-250.0f, 100.0f));
		m_Score.Render();
	}

	glutSwapBuffers();
}

void Update() {
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentTime - pasttime) *0.1f;
	pasttime = currentTime;
	glutPostRedisplay();
	m_Audio.Tick();

	if (!BackTrackPlaying && m_Game.currentScreen == m_Game.GAME) { //start loop for game
		m_Audio.Play(m_Audio.BABYBACK);
		m_Audio.Play(m_Audio.FIREBACK);
		BackTrackPlaying = true;
	}

	if (!m_Game.gameover) {
		m_Game.score += 0.01f;
		std::string tmptxt;
		int tmpint = static_cast<int>(floor(m_Game.score));
		tmptxt = "SCORE: " + std::to_string(tmpint);
		m_Score.SetText(tmptxt);
	}
	
}

int main(int argc, char **argv) {
	srand((unsigned int)time(NULL));

	int h = 700;
	int w = 500;

	m_Game.score = 0;
	m_Game.gameover = false;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(h, w);
	m_Screen.SCR_HEIGHT = static_cast<GLfloat>(h);
	m_Screen.SCR_WIDTH = static_cast<GLfloat>(w);

	glutCreateWindow("Summ 2 ~ Henry Oliver");

	if (glewInit() != GLEW_OK) {
		std::cout << "Glew INIT FAILED";
		system("pause");
	}

	if (!m_Audio.AudioInit()) {
		system("pause");
	}

	glClearColor(1.0, 0.0, 0.0, 1.0);

	glGenTextures(1, &fireTexture);
	glBindTexture(GL_TEXTURE_2D, fireTexture);

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

	glGenTextures(1, &babyTexture);
	glBindTexture(GL_TEXTURE_2D, babyTexture);

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

	babyPro = ShaderLoader::CreateProgram("Resources/baby.vs", "Resources/baby.fs");

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

	/* BACKGROUND */

	glGenTextures(1, &backgroundTexture);
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);

	unsigned char* backImage = SOIL_load_image("Resources/back.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, backImage);

	/* TEXTURE MAGIC */

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SOIL_free_image_data(backImage);
	glBindTexture(GL_TEXTURE_2D, 0);

	/* CREATE PROGRAMS */

	backgroundPro = ShaderLoader::CreateProgram("Resources/back.vs", "Resources/back.fs");

	glGenVertexArrays(1, &backVAO);
	glBindVertexArray(backVAO);

	glGenBuffers(1, &backEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, backEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(backIndices), backIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &backVBO);
	glBindBuffer(GL_ARRAY_BUFFER, backVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(backVerts), backVerts, GL_STATIC_DRAW);

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


	m_Cam.initializeCamera();

	/* AUDIO */

	m_Audio.Play(m_Audio.SPEECH);
	
	/* TEXT */
	m_Score = TextLabel(m_Screen, "SCORE: 0", "Resources/DIN1451.ttf", glm::vec2(-250.0f, 300.0f));
	m_GameOverText = TextLabel(m_Screen, "GAMEOVER", "Resources/DIN1451.ttf", glm::vec2(-150.0f, 300.0f));
	m_Score.SetScale(0.75);
	m_GameOverText.SetScale(0.75);

	glutDisplayFunc(Render);

	glutIdleFunc(Update);

	glutKeyboardFunc(Input::KeyboardDown);
	glutKeyboardUpFunc(Input::KeyboardUp);

	glutSpecialFunc(Input::specialCharDown);
	glutSpecialUpFunc(Input::specialCharUp);

	glutMainLoop();

	return 0;
}