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
#include <iostream>

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


void Scene::MainMenu()
{

	mainMenuObject.object.setImage("Assets/images/SUSFG-EX_MainMenu_PLAY.png");
	
	//floor vec ands ind
	GLfloat MainMenuVertices[] = {

		// Fill in the top face vertex data.							 
		-5.0f, 0.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-5.0f, 0.0f,  5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		5.0f, 0.0f,  5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		5.0f, 0.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};


	GLuint MainMenuIndices[] = {
		// front
		0, 1, 2,
		0, 2, 3, 
	};


	GLfloat * testVert = MainMenuVertices;
	GLuint * testInd = MainMenuIndices;


	mainMenuObject.object.createObj(testVert, sizeof(MainMenuVertices), testInd, sizeof(MainMenuIndices));

}


void Scene::MainMenuRender()
{
	mainMenuObject.object.render(0.0, 0.0, 0.0, true, mainCam);
}


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
	//audioMgr->playSound(shootSound, 0, false, &channel); // shooting sound    

	//star Scroll Point array (place where the fucking stars are bitch)
	starScrollPoint[0] = 0.0f;
	starScrollPoint[1] = -10.0f;

	starScrollPointBack[0] = 0.0f;
	starScrollPointBack[1] = -10.0f;

	starScrollPointBack2[0] = 0.0f;
	starScrollPointBack2[1] = -10.0f;


	FPS = new TextLabel("End score", "Assets/fonts/arial.ttf");
	FPS->setPosition(glm::vec2(1350.0f, 900.0f));
	FPS->setColor(glm::vec3(1.0f, 1.0f, 0.0f));


	//player creation
	player.object.setImage("Assets/images/GreenPlayer.png");
	player2.object.setImage("Assets/images/PinkPlayer.png");

	player.xCoord = 0.5f;
	player2.xCoord = -0.5f;

	player.yCoord = 1.5f;
	player2.yCoord = 1.5f;

	player.zCoord = 0.05f;
	player2.zCoord = 0.05f;

	Setsquare();	

	// pink
	for (int i = 0; i < 10; i++)
	{
		float RandX = rand() % 800;
		float RandY = rand() % 1000;
		RandX = (RandX / 100) - 4;
		RandY = (-(RandY / 100) - 2);
	
		objectStruct* enemy = new objectStruct();
		enemy->direction = 0;	
		enemy->xCoord = RandX;
		enemy->yCoord = RandY;
		pinkEnemys.push_back(*enemy);
		delete enemy;
		pinkEnemys[pinkEnemys.size() - 1].object.setImage("Assets/images/pinkBOX - Copy.png");
		Setenemy();
	}

	//green
	for (int i = 0; i < 10; i++)
	{
		float RandX = rand() % 800;
		float RandY = rand() % 1000;
		RandX = (RandX / 100) - 4;
		RandY = (-(RandY / 100) - 2);

		objectStruct* enemy = new objectStruct();
		enemy->direction = 0;	
		enemy->xCoord = RandX;
		enemy->yCoord = RandY;
		greenEnemys.push_back(*enemy);
		delete enemy;
		greenEnemys[greenEnemys.size() - 1].object.setImage("Assets/images/blueBOX - Copy.png");
		Setenemy2();
	}

	//bullet creation
	for (int b = 0; b < 50; b++)
	{
		objectStruct * bullet = new objectStruct;

		bullet->direction = 0;	
		bullet->xCoord = (0.5 + b * 0.02) - 1;
		bullet->yCoord = bulletsPlace;
		bullets.push_back(*bullet);
		delete bullet;
		bullets[bullets.size() - 1].object.setImage("Assets/images/blueBOX.png");
		SetBulet();
	}

	for (int b = 0; b < 50; b++)
	{
		objectStruct * bullet = new objectStruct;

		bullet->direction = 0;	
		bullet->xCoord = (0.5 + b * 0.02) - 1;
		bullet->yCoord = bulletsPlace;
		bullets2.push_back(*bullet);
		delete bullet;
		bullets2[bullets2.size() - 1].object.setImage("Assets/images/pinkBOX.png");
		SetBulet2();
	}


	for (int b = 0; b < 6; b++)
	{
		objectStruct * floor = new objectStruct;

		floor->direction = 0;
		floor->xCoord = 0;
		floor->yCoord = 0;
		starFloor.push_back(*floor);
		delete floor;
		if (starFloor.size() <= 2)
		{
			starFloor[starFloor.size() - 1].object.setImage("Assets/images/Back_Stars.png");	// Back Layer
		}
		else if (starFloor.size() > 2 && starFloor.size() <= 4)
		{
			starFloor[starFloor.size() - 1].object.setImage("Assets/images/Bg_grid.png");	// Middle Layer
		}
		else
		{
			starFloor[starFloor.size() - 1].object.setImage("Assets/images/Top_Stars.png");	// Front Layer
		}

		SetStarFloor();
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
	//glClearColor(0.050f, 0.050f, 0.050f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 3D
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//floor.render(0.0, 0.0, -1.0, 0.0 , true);             // put back from thing

	for (unsigned int i = 0; i < pinkEnemys.size(); i++)
	{
		pinkEnemys[i].object.render(pinkEnemys[i].xCoord, 0.12, pinkEnemys[i].yCoord, true, mainCam);
	}

	for (unsigned int i = 0; i < greenEnemys.size(); i++)
	{
		greenEnemys[i].object.render(greenEnemys[i].xCoord, 0.11, greenEnemys[i].yCoord, true, mainCam);
	}

	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i].object.render(bullets[i].xCoord, bullets[i].zCoord, bullets[i].yCoord, true, mainCam);
	}

	for (unsigned int i = 0; i < bullets2.size(); i++)
	{
		bullets2[i].object.render(bullets2[i].xCoord, bullets2[i].zCoord, bullets2[i].yCoord, true, mainCam);
	}

	// RGBA Alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	starFloor[0].object.render(0.0f, -0.03f, starScrollPoint[0], true, mainCam);
	starFloor[1].object.render(0.0f, -0.03f, starScrollPoint[1], true, mainCam);

	starFloor[4].object.render(0.0f, -0.01f, starScrollPointBack2[0], true, mainCam);
	starFloor[5].object.render(0.0f, -0.01f, starScrollPointBack2[1], true, mainCam);

	starFloor[2].object.render(0.0f, -0.00f, starScrollPointBack[0], true, mainCam);
	starFloor[3].object.render(0.0f, -0.00f, starScrollPointBack[1], true, mainCam);

//	std::cout << "place " << starScrollPointBack[i] << std::endl;


	// player render and movment

	player2.object.render(player2.xCoord, player2.zCoord - 0.001f, player2.yCoord, true, mainCam);
	player.object.render(player.xCoord, player.zCoord, player.yCoord , true, mainCam);

	glDisable(GL_BLEND);

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

	Playerspeed = 0.003 * deltaTime;
	enemySpeed = changeableSpeed * deltaTime;


	std::string FPString = "FPS: ";
	FPString += std::to_string(int(CurrentFPS)).c_str();
	FPS->setText(FPString.c_str());

	controll(keyState,  ArrowKeyState);


	// ---------------------------------- enemy reset
	for (unsigned int i = 0; i < pinkEnemys.size(); i++)
	{
		pinkEnemys[i].yCoord += enemySpeed;
		if (pinkEnemys[i].yCoord > 3.0)
		{			
			float RandX = rand() % 800;
			float RandY = rand() % 1000;
			RandX = (RandX / 100) - 4;
			RandY = (-(RandY / 100) - 2);

			//pinkEnemys[i].yCoord = -3.0;

			pinkEnemys[i].xCoord = RandX;
			pinkEnemys[i].yCoord = RandY - 1;
		}

		pinkEnemys[i].xCoord -= cos(currentTime) * 0.01;
		//camZ = cos(currentTime) * 4.0f;
	}

	for (unsigned int i = 0; i < greenEnemys.size(); i++)
	{
		greenEnemys[i].yCoord += enemySpeed;
		if (greenEnemys[i].yCoord > 3.0)
		{
			//randomize
			float RandX = rand() % 800;
			float RandY = rand() % 1000;
			RandX = (RandX / 100) - 4;
			RandY = (-(RandY / 100) - 2);


			greenEnemys[i].xCoord = RandX;
			greenEnemys[i].yCoord = RandY - 1;
		}

		greenEnemys[i].xCoord -= sin(currentTime) * 0.01;
	}


	if (keyState[(unsigned char)'i'] == BUTTON_DOWN && player.yCoord >= -0.5f	) { camLoc.y -= Playerspeed; } //up
	if (keyState[(unsigned char)'k'] == BUTTON_DOWN && player.yCoord <= 2.5f	) { camLoc.y += Playerspeed; } //down
	if (keyState[(unsigned char)'j'] == BUTTON_DOWN && player.xCoord <= 4.0f	) { camLoc.x += Playerspeed; } //left
	if (keyState[(unsigned char)'l'] == BUTTON_DOWN && player.xCoord >= -4.0f	) { camLoc.x -= Playerspeed; } //right 

	if (keyState[(unsigned char)'p'] == BUTTON_DOWN && player.xCoord <= 4.0f	) { camLoc.z += Playerspeed; } //left
	if (keyState[(unsigned char)';'] == BUTTON_DOWN && player.xCoord >= -4.0f	) { camLoc.z -= Playerspeed; } //right 

	//------------------------------
	std::cout << "x :" << camLoc.x << ", ";;
	std::cout << "y :" << camLoc.y << ", ";
	std::cout << "z :" << camLoc.z << ", " << std::endl;

	//camLook.x = player.xCoord;	//0.0;//sin(currentTime) *  0.50f;
	//camLook.y = player.zCoord;	//0.0;//0.25f;
	//camLook.z = -player.yCoord;	//0.0;//cos(currentTime) *  0.50f;
	//------------------------------

	for (size_t i = 0; i < 2; i++)
	{
		starScrollPoint[i] += 0.02f;
		if (starScrollPoint[i] > 10.0f)
		{
			starScrollPoint[i] = -10.0f;
		}
	}

	for (size_t i = 0; i < 2; i++)
	{
		starScrollPointBack[i] += 0.015f;
		if (starScrollPointBack[i] > 10.0f)
		{
			starScrollPointBack[i] = -10.0f;
		}
	}

	for (size_t i = 0; i < 2; i++)
	{
		starScrollPointBack2[i] += 0.025f;
		if (starScrollPointBack2[i] > 10.0f)
		{
			starScrollPointBack2[i] = -10.0f;
		}
	}


	
	MoventBox();
	mainCam.movingCam(camLoc, camLook);
	
}


void Scene::controll(unsigned char *keyState, unsigned int *ArrowKeyState)
{
	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime / 1000;

	

	if (keyState[(unsigned char)'w'] == BUTTON_DOWN && player.yCoord >= -0.5f || keyState[(unsigned char)'W'] == BUTTON_DOWN && player.yCoord >= -0.5f) { player.yCoord -= Playerspeed; } //up
	if (keyState[(unsigned char)'s'] == BUTTON_DOWN && player.yCoord <= 2.5f || keyState[(unsigned char)'S'] == BUTTON_DOWN && player.yCoord <= 2.5f) { player.yCoord += Playerspeed; } //down
	if (keyState[(unsigned char)'a'] == BUTTON_DOWN && player.xCoord <= 4.0f || keyState[(unsigned char)'A'] == BUTTON_DOWN && player.xCoord <= 4.0f) { player.xCoord += Playerspeed; } //left
	if (keyState[(unsigned char)'d'] == BUTTON_DOWN && player.xCoord >= -4.0f || keyState[(unsigned char)'D'] == BUTTON_DOWN && player.xCoord >= -4.0f) { player.xCoord -= Playerspeed; } //right 


	//if (keyState[(unsigned char)'r'] == BUTTON_DOWN || keyState[(unsigned char)'R'] == BUTTON_DOWN){ player.zCoord -= Playerspeed; }
	//if (keyState[(unsigned char)'f'] == BUTTON_DOWN || keyState[(unsigned char)'F'] == BUTTON_DOWN){ player.zCoord += Playerspeed; }
	//std::cout << "x:" << player.xCoord << std::endl;
	//std::cout << "y:" << player.yCoord << std::endl;

	if (ArrowKeyState[0] == BUTTON_DOWN && player2.yCoord >= -0.5f) { player2.yCoord -= Playerspeed; }	 //up
	if (ArrowKeyState[1] == BUTTON_DOWN && player2.yCoord <= 2.5f) { player2.yCoord += Playerspeed; }	 //down
	if (ArrowKeyState[2] == BUTTON_DOWN && player2.xCoord <= 4.0f) { player2.xCoord += Playerspeed; }	 //left
	if (ArrowKeyState[3] == BUTTON_DOWN && player2.xCoord >= -4.0f) { player2.xCoord -= Playerspeed; }	 //right 

																										 // bullet part ---------------------------------------------
	if (keyState[(unsigned char)'g'] == BUTTON_DOWN || keyState[(unsigned char)'G'] == BUTTON_DOWN)
	{
		if ((currentTime - fireDifference) > fireTime)
		{
			// ADD SHOOTING SOUND HERE
			fireDifference = currentTime;
			bullets[bulletsInUse].xCoord = player.xCoord;
			bullets[bulletsInUse].yCoord = player.yCoord;
			bullets[bulletsInUse].zCoord = player.zCoord;
			bullets[bulletsInUse].direction = 1;
			bulletsInUse++;
			if (IsLeft == false)
			{
				IsLeft = true;
			}
			else
			{
				IsLeft = false;
			}
		}
	}

	if (bulletsInUse >= 50)
	{
		bulletsInUse = 0;
	}


	// ---------------------------------- enemy reset
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].direction == 1)
		{
			float Amplitude = 0.3;
			float Frequency = 7;
			float StartingAngle = 0;
			float Yshift = 0;
			bullets[i].yCoord -= 0.15f;
		}

		if (bullets[i].yCoord < -3.0)
		{
			bullets[i].direction = 0;	//dircetion
			bullets[i].xCoord = (0.5 + i * 0.02) - 1;
			bullets[i].yCoord = bulletsPlace;
			//std::cout << bulletsInUse << "\n";
		}
	}


	// bullet part ---------------------------------------------   2   ----------------------------------------------
	if (keyState[(unsigned char)'/'] == BUTTON_DOWN || keyState[(unsigned char)'?'] == BUTTON_DOWN)
	{
		if ((currentTime - fireDifferencep2) > fireTime)
		{
			fireDifferencep2 = currentTime;

			bullets2[bulletsInUse2].xCoord = player2.xCoord;
			bullets2[bulletsInUse2].yCoord = player2.yCoord;
			bullets2[bulletsInUse2].zCoord = player2.zCoord;

			bullets2[bulletsInUse2].direction = 1;
			bulletsInUse2++;

		}
	}

	// shooting
	if (bulletsInUse2 >= 50)
	{
		bulletsInUse2 = 0;
	}


	// ---------------------------------- enemy reset  2
	for (unsigned int i = 0; i < bullets2.size(); i++)
	{
		if (bullets2[i].direction == 1)
		{
			bullets2[i].yCoord -= 0.1f;
		}

		if (bullets2[i].yCoord < -3.0)
		{
			bullets2[i].direction = 0;	//dircetion
			bullets2[i].xCoord = (0.5 + i * 0.02) - 1;
			bullets2[i].yCoord = bulletsPlace;
			//std::cout << bulletsInUse << "\n";
		}
	}

}


void Scene::MoventBox() 
{

	// bullet to pink enemy
	for (size_t i = 0; i < bullets2.size(); i++)
	{
		for (size_t x = 0; x < pinkEnemys.size(); x++)
		{
			if (bullets2[i].xCoord >= (pinkEnemys[x].xCoord - 0.2) && bullets2[i].xCoord <= (pinkEnemys[x].xCoord + 0.2)
				&& bullets2[i].yCoord >= (pinkEnemys[x].yCoord - 0.2) && bullets2[i].yCoord <= (pinkEnemys[x].yCoord + 0.2))
			{
				//randomize
				//
				float RandX = rand() % 800;
				float RandY = rand() % 1000;
				RandX = (RandX / 100) - 4;
				RandY = (-(RandY / 100) - 2);

				pinkEnemys[x].xCoord = RandX;
				pinkEnemys[x].yCoord = RandY;

				//bullet delete on hit
				// ADD BULLET HIT SOUND HERE
				bullets2[i].direction = 0;	//dircetion
				bullets2[i].xCoord = (0.5 + i * 0.02) - 1;
				bullets2[i].yCoord = bulletsPlace;
				//BULLETS SPEED
				changeableSpeed += 0.00005f;
			}
		}
	}


	for (size_t i = 0; i < bullets.size(); i++)
	{
		for (size_t x = 0; x < greenEnemys.size(); x++)
		{
			if (bullets[i].xCoord >= (greenEnemys[x].xCoord - 0.2) && bullets[i].xCoord <= (greenEnemys[x].xCoord + 0.2)
				&& bullets[i].yCoord >= (greenEnemys[x].yCoord - 0.2) && bullets[i].yCoord <= (greenEnemys[x].yCoord + 0.2))
			{
				//randomize
				float RandX = rand() % 800;
				float RandY = rand() % 1000;
				RandX = (RandX / 100) - 4;
				RandY = (-(RandY / 100) - 2);
	
	
				greenEnemys[x].xCoord = RandX;
				greenEnemys[x].yCoord = RandY;
	
				//bullet delete on hit
				bullets[i].direction = 0;	//dircetion
				bullets[i].xCoord = (0.5f + i * 0.02f) - 1;
				bullets[i].yCoord = bulletsPlace;
				//BULLETS SPEED
				changeableSpeed += 0.00005f;
			}
		}
	}


	// bullets reset
	for (size_t i = 0; i < bullets2.size(); i++)
	{
		for (size_t x = 0; x < greenEnemys.size(); x++)
		{
			if (bullets2[i].xCoord >= (greenEnemys[x].xCoord - 0.2) && bullets2[i].xCoord <= (greenEnemys[x].xCoord + 0.2)
				&& bullets2[i].yCoord >= (greenEnemys[x].yCoord - 0.2) && bullets2[i].yCoord <= (greenEnemys[x].yCoord + 0.2))
			{

				//bullet delete on hit
				bullets2[i].direction = 0;	//dircetion
				bullets2[i].xCoord = (0.5f + i * 0.02f) - 1;
				bullets2[i].yCoord = bulletsPlace;
			}
		}
	}

	// bullet to pink enemy
	for (size_t i = 0; i < bullets2.size(); i++)
	{
		for (size_t x = 0; x < pinkEnemys.size(); x++)
		{
			if (bullets[i].xCoord >= (pinkEnemys[x].xCoord - 0.2) && bullets[i].xCoord <= (pinkEnemys[x].xCoord + 0.2)
				&& bullets[i].yCoord >= (pinkEnemys[x].yCoord - 0.2) && bullets[i].yCoord <= (pinkEnemys[x].yCoord + 0.2))
			{

				//bullet delete on hit
				bullets[i].direction = 0;	//dircetion
				bullets[i].xCoord = (0.5 + i * 0.02) - 1;
				bullets[i].yCoord = bulletsPlace;
			}
		}
	}

		// player1 colision

		for (size_t x = 0; x < pinkEnemys.size(); x++)
		{
			if (player.xCoord >= (pinkEnemys[x].xCoord - 0.2) && player.xCoord <= (pinkEnemys[x].xCoord + 0.2)
				&& player.yCoord >= (pinkEnemys[x].yCoord - 0.2) && player.yCoord <= (pinkEnemys[x].yCoord + 0.2))
			{
				std::cout << "Playone hit by pink";
			}
		}

		for (size_t x = 0; x < greenEnemys.size(); x++)
		{
			if (player.xCoord >= (greenEnemys[x].xCoord - 0.2) && player.xCoord <= (greenEnemys[x].xCoord + 0.2)
				&& player.yCoord >= (greenEnemys[x].yCoord - 0.2) && player.yCoord <= (greenEnemys[x].yCoord + 0.2))
			{
				std::cout << "Playone hit by green";
			}
		}

		
		// player2 colision

		for (size_t x = 0; x < pinkEnemys.size(); x++)
		{
			if (player2.xCoord >= (pinkEnemys[x].xCoord - 0.2) && player2.xCoord <= (pinkEnemys[x].xCoord + 0.2)
				&& player2.yCoord >= (pinkEnemys[x].yCoord - 0.2) && player2.yCoord <= (pinkEnemys[x].yCoord + 0.2))
			{
				std::cout << "PlayTwo hit by pink";
			}
		}

		for (size_t x = 0; x < greenEnemys.size(); x++)
		{
			if (player2.xCoord >= (greenEnemys[x].xCoord - 0.2) && player2.xCoord <= (greenEnemys[x].xCoord + 0.2)
				&& player2.yCoord >= (greenEnemys[x].yCoord - 0.2) && player2.yCoord <= (greenEnemys[x].yCoord + 0.2))
			{
				std::cout << "PlayTwo hit by green";

			}
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
		-0.125f, 0.0f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.125f, 0.0f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.125f, 0.0f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.125f, 0.0f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
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
		-0.125f, 0.0f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.125f, 0.0f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.125f, 0.0f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.125f, 0.0f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
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
			 
		// Fill 1n the t2p face vertex data.							 
		-0.10f,  0.0f, -0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		-0.10f,  0.0f,  0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		 0.10f,   0.0f,  0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
	 	 0.10f,   0.0f, -0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,				 						 

	};


	GLuint floorIndices[] = {
		// front
		0, 1, 2,
		0, 2, 3,
	};


	GLfloat * testVert = floorVertices;
	GLuint * testInd = floorIndices;


	floor.createObj(testVert, sizeof(floorVertices), testInd, sizeof(floorIndices));
};


void Scene::Setenemy()
{
	// square ver and ind

	GLfloat vertices[192] = {

		-0.125f, 0.0f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.125f, 0.0f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.125f, 0.0f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.125f, 0.0f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

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

void Scene::Setenemy2()
{
	// square ver and ind

	GLfloat vertices[192] = {

		-0.125f, 0.0f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.125f, 0.0f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.125f, 0.0f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.125f, 0.0f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	};


	GLuint indices[36] = {
		// front
		0, 1, 2,
		0, 2, 3,

	};

	GLfloat * ptrEnemyVert = vertices;
	GLuint * prtEnemyInd = indices;


	//	std::cout << "Object \n";
	greenEnemys[greenEnemys.size() - 1].object.createObj(ptrEnemyVert, sizeof(vertices), prtEnemyInd, sizeof(indices));

}

void Scene::SetBulet()
{

	GLfloat vertices[] = {
	//  //position				//color				//texture coord		 
	//  -0.15f, -0.025f, -0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	//  -0.15f, 0.025f, -0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	//  0.15f, 0.025f, -0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	//  0.15f, -0.025f, -0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	//  // Fill in the back face vertex data.							 
	//  -0.15f, -0.025f, 0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	//  0.15f, -0.025f, 0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	//  0.15f, 0.025f, 0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	//  -0.15f, 0.025f, 0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the top face vertex data.							 
		-0.025f, 0.0f, -0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.025f, 0.0f, 0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.025f, 0.0f, 0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.025f, 0.0f, -0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	//	// Fill in the bottom face vertex data.							 
	//	-0.15f, -0.025f, -0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	//	0.15f, -0.025f, -0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	//	0.15f, -0.025f, 0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	//	-0.15f, -0.025f, 0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	//	// Fill in the left face vertex data.							 
	//	-0.15f, -0.025f, 0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	//	-0.15f, 0.025f, 0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	//	-0.15f, 0.025f, -0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	//	-0.15f, -0.025f, -0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	//	// Fill in the right face vertex data.							 
	//	0.15f, -0.025f, -0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	//	0.15f, 0.025f, -0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	//	0.15f, 0.025f, 0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	//	0.15f, -0.025f, 0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,

	};


	GLfloat * ptrEnemyVert = vertices;
	GLuint * prtEnemyInd = indices;


	bullets[bullets.size() - 1].object.createObj(ptrEnemyVert, sizeof(vertices), prtEnemyInd, sizeof(indices));

};

void Scene::SetBulet2()
{

	GLfloat vertices[] = {
		// Fill in the top face vertex data.							 
		-0.025f, 0.01f, -0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.025f, 0.01f, 0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.025f, 0.01f, 0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.025f, 0.01f, -0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,

	};


	GLfloat * ptrEnemyVert = vertices;
	GLuint * prtEnemyInd = indices;


	bullets2[bullets2.size() - 1].object.createObj(ptrEnemyVert, sizeof(vertices), prtEnemyInd, sizeof(indices));

};

void Scene::SetStarFloor() 
{
	GLfloat vertices[] = {
		// Fill in the top face vertex data.							 
		-5.0f, 0.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-5.0f, 0.0f,  5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 5.0f, 0.0f,  5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 5.0f, 0.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,

	};


	GLfloat * ptrEnemyVert = vertices;
	GLuint * prtEnemyInd = indices;


	starFloor[starFloor.size() - 1].object.createObj(ptrEnemyVert, sizeof(vertices), prtEnemyInd, sizeof(indices));

}