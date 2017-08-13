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
	player.object.setImage("Assets/images/blueBOX.png");
	player2.object.setImage("Assets/images/pinkBOX.png");

	player.yCoord = 1.5f;
	player2.yCoord = 1.5f;

	player.xCoord = 0.5f;
	player2.xCoord = -0.5f;

	Setsquare();	


	for (int i = 0; i < 50; i++)
	{
		float RandX = rand() % 800;
		float RandY = rand() % 1000;
		RandX = (RandX / 100) - 4;
		RandY = -(RandY / 100);
	
		objectStruct* enemy = new objectStruct();
		enemy->direction = 0;	//dircetion
		enemy->xCoord = RandX;
		enemy->yCoord = RandY;
		pinkEnemys.push_back(*enemy);
		delete enemy;
		pinkEnemys[pinkEnemys.size() - 1].object.setImage("Assets/images/mainMenu.png");
		Setenemy();
	}

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
	player.object.render(player.xCoord, player.zCoord, player.yCoord , 0.15, false);
	player2.object.render(player2.xCoord, player2.zCoord, player2.yCoord, 0.15, false);

	//floor.render(0.0, 0.0, -1.0, 0.0 , true);             // put back from thing
		for (unsigned int i = 0; i < pinkEnemys.size(); i++)
		{
			pinkEnemys[i].object.render(pinkEnemys[i].xCoord, 0.10, pinkEnemys[i].yCoord,  0.0, false);
		}

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

	Playerspeed = 0.005f * deltaTime;


	std::string FPString = "FPS: ";
	FPString += std::to_string(int(CurrentFPS)).c_str();
	FPS->setText(FPString.c_str());


	if (keyState[(unsigned char)'s'] == BUTTON_DOWN && player.yCoord <=  2.5f  || keyState[(unsigned char)'S'] == BUTTON_DOWN && player.yCoord <=   2.5f) { player.yCoord += Playerspeed; }
	if (keyState[(unsigned char)'w'] == BUTTON_DOWN && player.yCoord >= -0.5f  || keyState[(unsigned char)'W'] == BUTTON_DOWN && player.yCoord >=  -0.5f){ player.yCoord -= Playerspeed; }
	if (keyState[(unsigned char)'d'] == BUTTON_DOWN && player.xCoord >= -4.0f || keyState[(unsigned char)'D'] == BUTTON_DOWN && player.xCoord >=   -4.0f) { player.xCoord -= Playerspeed; }
	if (keyState[(unsigned char)'a'] == BUTTON_DOWN && player.xCoord <=  4.0f  || keyState[(unsigned char)'A'] == BUTTON_DOWN && player.xCoord <=   4.0f){ player.xCoord += Playerspeed; }


	//if (keyState[(unsigned char)'r'] == BUTTON_DOWN || keyState[(unsigned char)'R'] == BUTTON_DOWN){ player.zCoord -= Playerspeed; }
	//if (keyState[(unsigned char)'f'] == BUTTON_DOWN || keyState[(unsigned char)'F'] == BUTTON_DOWN){ player.zCoord += Playerspeed; }
	std::cout << "x:" << player.xCoord << std::endl;
	std::cout << "y:" << player.yCoord << std::endl;

	if (ArrowKeyState[0] == BUTTON_DOWN && player2.yCoord >= -0.5f)  { player2.yCoord -= Playerspeed; }	 //up
	if (ArrowKeyState[1] == BUTTON_DOWN && player2.yCoord <= 2.5f) { player2.yCoord += Playerspeed; }	 //down
	if (ArrowKeyState[2] == BUTTON_DOWN && player2.xCoord <= 4.0f) { player2.xCoord += Playerspeed; }	 //left
	if (ArrowKeyState[3] == BUTTON_DOWN && player2.xCoord >= -4.0f)  { player2.xCoord -= Playerspeed; }	 //right 


	for (unsigned int i = 0; i < pinkEnemys.size(); i++)
	{
		pinkEnemys[i].yCoord += 0.01f;
		if (pinkEnemys[i].yCoord > 2.0)
		{
			pinkEnemys[i].yCoord = -3.0;
		}
	}

	
}



void Scene::MoventBox() 
{

	if (player.xCoord > 0.4f)
	{
		player.xCoord -= (Playerspeed);
	}


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

	// player two ind and vert 
	GLfloat Player2Vert[] = {
		-0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};

	GLuint Player2Ind[] = {
		0, 1, 2,
		0, 2, 3,
	};


	GLfloat * playerVert = vertices;
	GLuint * playerInd = indices;

	GLfloat * prtPlayer2Vert = Player2Vert;
	GLuint * prtPlayer2Ind = Player2Ind;
	
	player.object.createObj(playerVert, sizeof(vertices), playerInd, sizeof(indices));

	player2.object.createObj(prtPlayer2Vert, sizeof(Player2Vert), prtPlayer2Ind, sizeof(Player2Ind));
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



void Scene::Setenemy()
{
	// square ver and ind

	GLfloat vertices[192] = {

		-0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	};


	GLuint indices[36] = {
		// front
		0, 1, 2,
		0, 2, 3,

	};

	GLfloat * ptrEnemyVert = vertices;
	GLuint * prtEnemyInd = indices;


	//	std::cout << "Object \n";
	pinkEnemys[pinkEnemys.size() - 1].object.createObj(ptrEnemyVert, sizeof(vertices), prtEnemyInd, sizeof(indices));

}
