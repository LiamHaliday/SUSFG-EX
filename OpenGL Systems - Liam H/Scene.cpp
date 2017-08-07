// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Scene.cpp
// Description	: Scenes
// Author		: Liam Haliday
// Mail			: liamhaliday@gmail.com	

#include "Scene.h"

#define BUTTON_UP   0 
#define BUTTON_DOWN 1
#define UP 0;
#define DOWN 1;
#define LEFT 2;
#define RIGHT 3;

Scene::Scene()
{
	srand(time(NULL));
};


/****************************************************/
// Filename: Scene.cpp
// Created: Liam Haliday
// Description: Creates all the objects for the main game scene
/****************************************************/
void Scene::init()
{
	//sound
	InitFmod();
	LoadAudio();
	FMOD::Channel* channel;
	//audioMgr->playSound(bgMusic, 0, false, &channel); // background sound                                                 //sound -----------------------------------------


	FPS = new TextLabel("End score", "Assets/fonts/arial.ttf");
	FPS->setPosition(glm::vec2(1350.0f, 900.0f));
	FPS->setColor(glm::vec3(1.0f, 1.0f, 0.0f));


	//player creation
	player.object.setImage("Assets/images/lava.jpg");
	Setsquare();	

	//floor.setImage("Assets/images/blueBOX.png");
	//SetFloor();

}

/****************************************************/
// Filename: Scene.cpp
// Created: Liam Haliday
// Description: Renders the main game objects 
/****************************************************/
void Scene::render()
{
	glClearColor(0.050f, 0.050f, 0.050f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 3D
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// player render and movment
	player.object.render(player.xCoord, player.yCoord,  player.zCoord, 0.15, false);
	//floor.render(0.0, 0.0, -1.0, 0.0 , true);             // put back from thing


	FPS->Render();
	
	glutSwapBuffers();
}



/****************************************************/
// Filename: Scene.cpp
// Created: Liam Haliday
// Description: Updates things in the game like movement and firing bullets and Collision 
/****************************************************/
void Scene::update(unsigned char *keyState, unsigned int *ArrowKeyState)
{
	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime / 1000;

	//delta time
	currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	CurrentFPS = ((1 / deltaTime) * 1000);
	//std::cout << currentTime << std::endl;

	Playerspeed = 0.001f * deltaTime;


	std::string FPString = "FPS: ";
	FPString += std::to_string(int(CurrentFPS)).c_str();
	FPS->setText(FPString.c_str());


	if (keyState[(unsigned char)'w'] == BUTTON_DOWN || keyState[(unsigned char)'W'] == BUTTON_DOWN){ player.zCoord -= Playerspeed;}
	if (keyState[(unsigned char)'s'] == BUTTON_DOWN || keyState[(unsigned char)'S'] == BUTTON_DOWN){ player.zCoord += Playerspeed; }
	if (keyState[(unsigned char)'a'] == BUTTON_DOWN || keyState[(unsigned char)'A'] == BUTTON_DOWN){ player.xCoord -= Playerspeed; }
	if (keyState[(unsigned char)'d'] == BUTTON_DOWN || keyState[(unsigned char)'D'] == BUTTON_DOWN){ player.xCoord += Playerspeed; }
	if (keyState[(unsigned char)'r'] == BUTTON_DOWN || keyState[(unsigned char)'R'] == BUTTON_DOWN){ player.yCoord -= Playerspeed; }
	if (keyState[(unsigned char)'f'] == BUTTON_DOWN || keyState[(unsigned char)'F'] == BUTTON_DOWN){ player.yCoord += Playerspeed; }


	if (ArrowKeyState[0] == BUTTON_DOWN) { std::cout << "UP"; } //up
	if (ArrowKeyState[1] == BUTTON_DOWN) { std::cout << "DOWN"; } //down
	if (ArrowKeyState[2] == BUTTON_DOWN) { std::cout << "LEFT";  CamLookX - 0.01f; } //left
	if (ArrowKeyState[3] == BUTTON_DOWN) { std::cout << "RIGHT"; CamLookX + 0.01f; } //right

	
}


/****************************************************/
// Filename: Scene.cpp
// Created: Liam Haliday
// Description: passes the object vertices and indices
/****************************************************/
void Scene::Setsquare()
{
	// square ver and ind
	GLfloat vertices[] = {
//		//position				//color				//texture coord
//		-0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
//		-0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//		0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//		0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//		// Fill in the back face vertex data.
//		-0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//		0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
//		0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//		-0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the top face vertex data.
		-0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//		// Fill in the bottom face vertex data.
//		-0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//		0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
//		0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//		-0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//		// Fill in the left face vertex data.
//		-0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
//		-0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//		-0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//		-0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//		// Fill in the right face vertex data.
//		0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
//		0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//		0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//		0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,
		// top
//		4, 5, 6,
//		4, 6, 7,
//		// back
//		8, 9, 10,
//		8, 10, 11,
//
//		// bottom
//		12, 13, 14,
//		12, 14, 15,
//		// left
//		16, 17, 18,
//		16, 18, 19,
//		// right
//		20, 21, 22,
//		20, 22, 23,
	};


	GLfloat * testVert = vertices;
	GLuint * testInd = indices;

	
	player.object.createObj(testVert, sizeof(vertices), testInd, sizeof(indices));
}







void Scene::SetFloor()
{

	//floor vec ands ind
	GLfloat floorVertices[] = {
		//position				//color				//texture coord		 
		-0.10f, -0.10f, -0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		-0.10f,  0.10f, -0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		 0.10f,   0.10f, -0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
		 0.10f,  -0.10f, -0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,				 
		// Fill 1n the b2ck face vertex data.							 
		-0.10f, -0.10f,  0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,				 
		 0.10f,  -0.10f,  0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		 0.10f,   0.10f,  0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		-0.10f,  0.10f,  0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
		// Fill 1n the t2p face vertex data.							 
		-0.10f,  0.10f, -0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		-0.10f,  0.10f,  0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		 0.10f,   0.10f,  0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
	 	 0.10f,   0.10f, -0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,				 
		// Fill 1n the b2ttom face vertex data.							 
		-0.10f, -0.10f, -0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,				 
		 0.10f,  -0.10f, -0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		 0.10f,  -0.10f,  0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		-0.10f, -0.10f,  0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
		// Fill 1n the l2ft face vertex data.							 
		-0.10f, -0.10f,  0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		-0.10f,  0.10f,  0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		-0.10f,  0.10f, -0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
		-0.10f, -0.10f, -0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,				 
		// Fill 1n the r2ght face vertex data.							 
		 0.10f,  -0.10f, -0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		 0.10f,   0.10f, -0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		 0.10f,   0.10f,  0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
		 0.10f,  -0.10f,  0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,				 
	};


	GLuint floorIndices[] = {
		// front
		0, 1, 2,
		0, 2, 3,
		// top
		4, 5, 6,
		4, 6, 7,
		// back
		8, 9, 10,
		8, 10, 11,

		// bottom
		12, 13, 14,
		12, 14, 15,
		// left
		16, 17, 18,
		16, 18, 19,
		// right
		20, 21, 22,
		20, 22, 23,
	};


	GLfloat * testVert = floorVertices;
	GLuint * testInd = floorIndices;


	floor.createObj(testVert, sizeof(floorVertices), testInd, sizeof(floorIndices));
};
