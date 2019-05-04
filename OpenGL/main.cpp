#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>   
#include <ctime>
#include <chrono>
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

//namespaces

using std::chrono::duration_cast;
using std::chrono::minutes;
using std::chrono::seconds;
typedef std::chrono::high_resolution_clock m_clock;

//GLOBAL Classes

Camera m_Cam;
ScreenInfo m_Screen;
AudioSystem m_Audio;
TextLabel m_Score;
TextLabel m_GameOverText;
TextLabel m_MainText;
GameManager m_Game;
ObjectManager m_BabyObjManager;
ObjectManager m_FireObjManager;
//GLOBAL VARS
auto start = m_clock::now();
auto end = m_clock::now();
auto BabyDiestart = m_clock::now();
auto BabyDieend = m_clock::now();

double elapsed_mins;
double elapsed_secs;

float r = 1.0;
float b = 1.0;
float g = 1.0;

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
bool Babyisdying = false;

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
	0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//top right		0
	-0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 1.0f,	0.0f, 0.0f,		//top left		1
	-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,		//bottom left	2
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		//bottom right	3
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

void checkCollision(glm::vec4 box1, glm::vec4 box2)
{
	if ((box1.x > box2.x) && (box1.y < box2.x))
	{
		if ((box1.z < box2.z) && (box1.w > box2.z))
		{
			m_FireObjManager.ONTARGET = true;
		}
		if ((box1.z < box2.w) && (box1.w > box2.w))
		{
			m_FireObjManager.ONTARGET = true;
		}
	}
	if ((box1.x > box2.y) && (box1.y < box2.y))
	{
		if ((box1.z < box2.z) && (box1.w > box2.z))
		{
			m_FireObjManager.ONTARGET = true;
		}
		if ((box1.z < box2.w) && (box1.w > box2.w))
		{
			m_FireObjManager.ONTARGET = true;
		}
	}
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	r = (rand() % 10 + 1)/10.0f;
	g = (rand() % 10 + 1)/10.0f;
	b = (rand() % 10 + 1)/10.0f;
	
	glClearColor(r, g, b, 1.0);

	/* CAMERA */

	m_Cam.calculate();

	glm::mat4 proj;
	float halfw = (float)m_Screen.SCR_WIDTH * 0.5f;
	float halfh = (float)m_Screen.SCR_HEIGHT * 0.5f;
	proj = glm::ortho(-halfw, halfw, -halfh, halfh, 0.1f, 100.0f);

	glm::vec3 fireObjPosition = glm::vec3(-150.0f, 0.0f, 0.0f);
	glm::vec3 babyObjPosition = glm::vec3(150.0f, 0.0f, 0.0f);
	glm::vec3 backObjPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	//MOVE OBJECTS

	if (!m_Game.gameover && m_Game.currentScreen == m_Game.GAME) {
		m_BabyObjManager.movement(m_Audio, deltaTime, m_Screen.SCR_WIDTH, m_Screen.SCR_HEIGHT, false);

		babyObjPosition += m_BabyObjManager.objPos;

		m_FireObjManager.Target = babyObjPosition;
		m_FireObjManager.movement(m_Audio, deltaTime, m_Screen.SCR_WIDTH, m_Screen.SCR_HEIGHT, true);

		fireObjPosition += m_FireObjManager.objPos;
	}
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

	//CHECK COLLISIONS

	if (!m_Game.gameover && m_Game.currentScreen == m_Game.GAME) {
		glm::vec4 playerbox(m_BabyObjManager.objPos.y, babyObjPosition.y - objscale.y, babyObjPosition.x, babyObjPosition.x + objscale.x); //up down left right
		glm::vec4 enemybox((fireObjPosition.y - 30), (fireObjPosition.y - 30) - (fireObjPosition.y - 30), (fireObjPosition.x - 30), (fireObjPosition.x - 30) + objscale.x);
		checkCollision(playerbox, enemybox);
	}

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
		m_MainText.Render();
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
	}

	glutSwapBuffers();
}

void Update() {
	currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
	deltaTime = (currentTime - pasttime) *0.1f;
	pasttime = currentTime;
	glutPostRedisplay();
	m_Audio.Tick();
	m_Game.CheckGeneralInput(m_Game);

	if (m_Game.leave) {
		glutLeaveMainLoop();
	}

	if (!BackTrackPlaying && m_Game.currentScreen == m_Game.GAME) { //start loop for game
		m_Audio.Play(m_Audio.BABYBACK);
		m_Audio.Play(m_Audio.FIREBACK);
		start = m_clock::now(); //Start counting time
		end = m_clock::now();
		BackTrackPlaying = true;
	}

	if (!m_Game.gameover && m_Game.currentScreen == m_Game.GAME) {
		end = m_clock::now();
		elapsed_mins = duration_cast<minutes>(end - start).count();
		m_Game.score += 0.01f;
		std::string tmptxt;
		int tmpint = static_cast<int>(floor(m_Game.score));
		tmptxt = "SCORE: " + std::to_string(tmpint);
		m_Score.SetText(tmptxt);
		//GAME WIN CONDITION
		if ((elapsed_mins >= 240)||(elapsed_mins >= 5 && m_Game.easy_mode)|| m_Game.override_win) {
			m_Audio.babyBackTrack->release();
			m_Audio.fireBackTrack->release();
			m_Audio.speechTrack->release();
			m_Audio.AudioInit();
			m_Game.gameover = true;
			m_Game.won = true;
			std::string tmp = "You Win!\n\n\nTime Taken: ";
			int tm1 = static_cast<int>(floor(elapsed_mins));
			int tm2 = static_cast<int>(floor(m_Game.score));
			tmp = tmp + std::to_string(tm1) + " Minutes\nScore: " + std::to_string(tm2) + "\n\n\nPress C To Continue";
			m_GameOverText.SetText(tmp);
			m_Audio.Play(m_Audio.WON);

			//RESET FOR RESTART
			m_Game.currentScreen = m_Game.GAMEOVER;
			BackTrackPlaying = false;
			m_FireObjManager.ONTARGET = false;
			start = m_clock::now();
			end = m_clock::now();
			m_FireObjManager.objPos = glm::vec3(0.0f, 0.0f, 0.0f);
			m_BabyObjManager.objPos = glm::vec3(0.0f, 0.0f, 0.0f);
			m_Game.override_win = false;

		}
		else if (m_FireObjManager.ONTARGET) { //fire got the baby
			m_Audio.babyBackTrack->release();
			m_Audio.fireBackTrack->release();
			m_Audio.speechTrack->release();
			m_Audio.AudioInit();
			m_Audio.Play(m_Audio.LOST);
			if (!Babyisdying) {
				Babyisdying = true;
				BabyDiestart = m_clock::now();
				bool tmp = false;
				while (!tmp) {
					BabyDieend = m_clock::now();
					elapsed_secs = static_cast<double>(duration_cast<seconds>(BabyDieend - BabyDiestart).count());
					m_Audio.Tick();
					if (elapsed_secs > 4) {
						tmp = true;
					}
				}
			}
			std::string tmp = "Game Over!\n\n\nTime Taken: ";
			int tm1 = static_cast<int>(floor(elapsed_mins));
			int tm2 = static_cast<int>(floor(m_Game.score));
			tmp = tmp + std::to_string(tm1) + " Minutes\nScore: " + std::to_string(tm2) + "\n\n\nPress C To Continue";
			m_GameOverText.SetText(tmp);

			//RESET FOR RESTART
			m_Game.gameover = true;
			m_Game.won = false;
			m_Game.currentScreen = m_Game.GAMEOVER;
			BackTrackPlaying = false;
			m_FireObjManager.ONTARGET = false;
			start = m_clock::now();
			end = m_clock::now();
			m_FireObjManager.objPos = glm::vec3(0.0f, 0.0f, 0.0f);
			m_BabyObjManager.objPos = glm::vec3(0.0f, 0.0f, 0.0f);
		}
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
	m_GameOverText = TextLabel(m_Screen, "GAMEOVER", "Resources/DIN1451.ttf", glm::vec2(-240.0f, 300.0f));
	m_MainText = TextLabel(m_Screen, "Art\n-Henry Oliver\n\nMain Menu\n\nSelect a mode:\n1. Normal mode\n2. Lecturer/Easy mode", "Resources/Arial.ttf", glm::vec2(-240.0f, 300.0f));
	m_Score.SetScale(static_cast<GLfloat>(0.65));
	m_GameOverText.SetScale(static_cast<GLfloat>(0.5));
	m_MainText.SetScale(static_cast<GLfloat>(0.5));

	glutDisplayFunc(Render);

	glutIdleFunc(Update);

	glutKeyboardFunc(Input::KeyboardDown);
	glutKeyboardUpFunc(Input::KeyboardUp);

	glutSpecialFunc(Input::specialCharDown);
	glutSpecialUpFunc(Input::specialCharUp);

	glutMainLoop();

	return 0;
}