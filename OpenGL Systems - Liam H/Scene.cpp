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
		-1.60f, 0.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-1.60f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		1.60f, 0.0f,  1.0f, 1.0f, 1.0f,	1.0f, 0.0f, 0.0f,
		1.60f, 0.0f, -1.0f, 1.0f, 1.0f,	1.0f, 0.0f, 1.0f,
	};


	GLuint MainMenuIndices[] = {
		// front
		0, 1, 2,
		0, 2, 3, 
	};


	GLfloat * testVert = MainMenuVertices;
	GLuint * testInd = MainMenuIndices;


	mainMenuObject.object.createObj(testVert, sizeof(MainMenuVertices), testInd, sizeof(MainMenuIndices));
	
	// --------------------------------------------------- button two ---------------------------------------------------

	mainMenuObject1.object.setImage("Assets/images/SUSFG-EX_MainMenu_HELP.png");
	mainMenuObject1.object.createObj(testVert, sizeof(MainMenuVertices), testInd, sizeof(MainMenuIndices));

	// --------------------------------------------------- button three ---------------------------------------------------

	mainMenuObject2.object.setImage("Assets/images/SUSFG-EX_MainMenu_QUIT.png");
	mainMenuObject2.object.createObj(testVert, sizeof(MainMenuVertices), testInd, sizeof(MainMenuIndices));

}



void Scene::MainMenuRender(int menuNumber)
{
	//glClearColor(0.050f, 0.050f, 0.050f, 1.0f);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 3D
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	switch (menuNumber)
	{
	case 0:
	{
		mainMenuObject.object.render(0.0, 0.0, 0.0, true, mainCam);

		break;
	}
	case 1:
	{
		mainMenuObject1.object.render(0.0, 0.0, 0.0, true, mainCam);

		break;
	}
	case 2:
	{
		mainMenuObject2.object.render(0.0, 0.0, 0.0, true, mainCam);

		break;
	}

	default:
		break;
	}


	glDisable(GL_BLEND);
	glutSwapBuffers();


	mainCam.movingCam(camLocMainMenu, camLook);
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

	// Main Menu Option
	int menuOption = 1;	// Start on PLAY

	//star Scroll Point array
	starScrollPoint[0] = 0.0f;
	starScrollPoint[1] = -10.0f;

	starScrollPointBack[0] = 0.0f;
	starScrollPointBack[1] = -10.0f;

	starScrollPointBack2[0] = 0.0f;
	starScrollPointBack2[1] = -10.0f;


	FPS = new TextLabel("End score", "Assets/fonts/PressStart2P.ttf");	// SET FONT
	FPS->setScale(0.5);
	FPS->setPosition(glm::vec2(250.0f, 10.0f));
	FPS->setColor(glm::vec3(1.0f, 1.0f, 1.0f));

	// ----------- GAME OVER -----------

	greenScoreText = new TextLabel("End score", "Assets/fonts/PressStart2P.ttf");	// SET FONT
	greenScoreText->setScale(1.0);
	greenScoreText->setPosition(glm::vec2(250.0f, 750.0f));
	greenScoreText->setColor(glm::vec3(0.0f, 1.0f, 0.0f));


	mainScoreText = new TextLabel("End score", "Assets/fonts/PressStart2P.ttf");	// SET FONT
	mainScoreText->setScale(1.5);
	mainScoreText->setPosition(glm::vec2(250, 475.0f));
	mainScoreText->setColor(glm::vec3(1.0f, 1.0f, 1.0f));


	purpleScoreText = new TextLabel("End score", "Assets/fonts/PressStart2P.ttf");	// SET FONT
	purpleScoreText->setScale(1.0);
	purpleScoreText->setPosition(glm::vec2(250.0f, 225.0f));
	purpleScoreText->setColor(glm::vec3(1.0f, 0.2f, 0.5f));


	//player creation
	player.object.setImage("Assets/images/GreenPlayer.png");
	player2.object.setImage("Assets/images/purplePlayer.png");

	player.xCoord = 0.5f;
	player2.xCoord = -0.5f;

	player.yCoord = 1.5f;
	player2.yCoord = 1.5f;

	player.zCoord = 0.05f;
	player2.zCoord = 0.05f;

	Setsquare();	

	// big boss

	specialEnemy.object.setImage("Assets/images/Final/Enemy2_purple.png");
	specialEnemyCreate();

	specialEnemy.xCoord = 0.0f;
	specialEnemy.yCoord = -6.0f;
	specialEnemy.zCoord = 0.10f;


	// purple enemy1
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
		purpleEnemys.push_back(*enemy);
		delete enemy;
		purpleEnemys[purpleEnemys.size() - 1].object.setImage("Assets/images/Final/Enemy1_purple.png");
		Setenemy();
	}

	// green enemy1
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
		greenEnemys[greenEnemys.size() - 1].object.setImage("Assets/images/Final/Enemy1_Green.png");
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
		bullets2[bullets2.size() - 1].object.setImage("Assets/images/purpleBOX.png");
		SetBulet2();
	}

	for (int b = 0; b < 50; b++)
	{
		objectStruct * bullet = new objectStruct;

		bullet->direction = 0;
		bullet->xCoord = (0.5 + b * 0.02) - 1;
		bullet->yCoord = bulletsPlace;
		bullet->zCoord = 0.0f;
		specialEnemyBullets.push_back(*bullet);
		delete bullet;
		specialEnemyBullets[specialEnemyBullets.size() - 1].object.setImage("Assets/images/blueBOX.png");
		SetSpecialEnemyBullets();
	}

	// Stars
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

	//// Main Menu
	//if (menuOption == 1) {
	//	objectStruct * floor = new objectStruct;
	//	floor->direction = 0;
	//	floor->xCoord = 0;
	//	floor->yCoord = 0;
	//	mainMenu.push_back(*floor);
	//	delete floor;
	//	if (menuOption <= 1) {
	//		mainMenu[mainMenu.size() - 1].object.setImage("Assets/images/SUSFG-EX_MainMenu_PLAY.png");	// PLAY BUTTON
	//	}
	//	if (menuOption == 2) {
	//		mainMenu[mainMenu.size() - 1].object.setImage("Assets/images/SUSFG-EX_MainMenu_OPTIONS.png");	// OPTIONS BUTTON
	//	}
	//	else if (menuOption >= 3) {
	//		mainMenu[mainMenu.size() - 1].object.setImage("Assets/images/SUSFG-EX_MainMenu_QUIT.png");	// QUIT BUTTON
	//	}
	//	SetMainMenu();
	//}


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
	// RGBA Alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Beckground Render
	starFloor[0].object.render(0.0f, -0.03f, starScrollPoint[0], true, mainCam);
	starFloor[1].object.render(0.0f, -0.03f, starScrollPoint[1], true, mainCam);

	starFloor[4].object.render(0.0f, -0.01f, starScrollPointBack2[0], true, mainCam);
	starFloor[5].object.render(0.0f, -0.01f, starScrollPointBack2[1], true, mainCam);

	starFloor[2].object.render(0.0f, -0.00f, starScrollPointBack[0], true, mainCam);
	starFloor[3].object.render(0.0f, -0.00f, starScrollPointBack[1], true, mainCam);

	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i].object.render(bullets[i].xCoord, bullets[i].zCoord, bullets[i].yCoord, true, mainCam);
	}

	for (unsigned int i = 0; i < bullets2.size(); i++)
	{
		bullets2[i].object.render(bullets2[i].xCoord, bullets2[i].zCoord, bullets2[i].yCoord, true, mainCam);
	}

	for (unsigned int i = 0; i < bullets2.size(); i++)
	{
		specialEnemyBullets[i].object.render(specialEnemyBullets[i].xCoord, specialEnemyBullets[i].zCoord, specialEnemyBullets[i].yCoord, true, mainCam);
	}

	//// MAIN MENU TEST
	//for (unsigned int i = 0; i < mainMenu.size(); i++)
	//{
	//	mainMenu[i].object.render(mainMenu[i].xCoord, mainMenu[i].zCoord, mainMenu[i].yCoord, true, mainCam);
	//}

	// boss 
	specialEnemy.object.render(specialEnemy.xCoord, specialEnemy.zCoord, specialEnemy.yCoord,true, mainCam);


	for (unsigned int i = 0; i < purpleEnemys.size(); i++)
	{
		purpleEnemys[i].object.render(purpleEnemys[i].xCoord, 0.12, purpleEnemys[i].yCoord, true, mainCam);
	}

	for (unsigned int i = 0; i < greenEnemys.size(); i++)
	{
		greenEnemys[i].object.render(greenEnemys[i].xCoord, 0.11, greenEnemys[i].yCoord, true, mainCam);
	}

	// player render

	if (purpleAlive) {	player2.object.render(player2.xCoord, player2.zCoord - 0.001f, player2.yCoord, true, mainCam);	}
	
	if (greenAlive) {	player.object.render(player.xCoord, player.zCoord, player.yCoord, true, mainCam);				}

	glDisable(GL_BLEND);


	if (!greenAlive && !purpleAlive)
	{
		purpleScoreText->Render();
		greenScoreText->Render();
		mainScoreText->Render();
	}
	else
	{
		FPS->Render();
	}

	

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

	//fps
	CurrentFPS = ((1 / deltaTime) * 1000);
	//std::cout << CurrentFPS << std::endl;

	// player Speeds
	Playerspeed = 0.003 * deltaTime;
	enemySpeed = changeableSpeed * deltaTime;

	// score set up
	mainScore = (greenScore + purpleScore);

	std::string scoreText = "Green Score: ";
	scoreText += std::to_string(int(greenScore)).c_str();

	scoreText += "   Main Score: ";
	scoreText += std::to_string(int(mainScore)).c_str();

	scoreText += "   Purple Score: ";
	scoreText += std::to_string(int(purpleScore)).c_str();

	FPS->setText(scoreText.c_str());

	// --------------------- GAVE OVER ---------------------
	scoreText = "Green Score: ";
	scoreText += std::to_string(int(greenScore)).c_str();
	greenScoreText->setText(scoreText);

	scoreText = "Purple Score: ";
	scoreText += std::to_string(int(purpleScore)).c_str();
	purpleScoreText->setText(scoreText);

	scoreText = "Main Score: ";
	scoreText += std::to_string(int(mainScore)).c_str();
	mainScoreText->setText(scoreText);

	controll(keyState,  ArrowKeyState);

	// big boss 
	if (mainScore > 750)
	{
		if (specialEnemy.yCoord < -3.0f)
		{
			specialEnemy.yCoord += (Playerspeed / 3);
			specialEnemyMovement = (Playerspeed / 3);
		}
		else
		{
			specialEnemy.xCoord += specialEnemyMovement;
		}

		if (specialEnemy.xCoord > 3.0f)
		{
			specialEnemyMovement = -(Playerspeed / 3);
		}
		else if (specialEnemy.xCoord < -3.0f)
		{
			specialEnemyMovement = (Playerspeed / 3);
		}
	}


	// ---------------------------------- enemy reset
	for (unsigned int i = 0; i < purpleEnemys.size(); i++)
	{
		purpleEnemys[i].yCoord += enemySpeed;
		if (purpleEnemys[i].yCoord > 5.0)
		{			
			float RandX = rand() % 800;
			float RandY = rand() % 1000;
			RandX = (RandX / 100) - 4;
			RandY = (-(RandY / 100) - 2);

			//purpleEnemys[i].yCoord = -3.0;

			purpleEnemys[i].xCoord = RandX;
			purpleEnemys[i].yCoord = RandY - 1;
		}

		purpleEnemys[i].xCoord -= cos(currentTime) * 0.01;
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


//	if (keyState[(unsigned char)'i'] == BUTTON_DOWN && player.yCoord >= -0.5f	) { camLoc.y -= Playerspeed; } //up
//	if (keyState[(unsigned char)'k'] == BUTTON_DOWN && player.yCoord <= 2.5f	) { camLoc.y += Playerspeed; } //down
//	if (keyState[(unsigned char)'j'] == BUTTON_DOWN && player.xCoord <= 4.0f	) { camLoc.x += Playerspeed; } //left
//	if (keyState[(unsigned char)'l'] == BUTTON_DOWN && player.xCoord >= -4.0f	) { camLoc.x -= Playerspeed; } //right 
//
//	if (keyState[(unsigned char)'p'] == BUTTON_DOWN && player.xCoord <= 4.0f	) { camLoc.z += Playerspeed; } //left
//	if (keyState[(unsigned char)';'] == BUTTON_DOWN && player.xCoord >= -4.0f	) { camLoc.z -= Playerspeed; } //right 
//
//	//------------------------------
//	std::cout << "x :" << camLoc.x << ", ";;
//	std::cout << "y :" << camLoc.y << ", ";
//	std::cout << "z :" << camLoc.z << ", " << std::endl;
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

	// ------------------------ GAME OVER ------------------------
	MoventBox();
	mainCam.movingCam(camLoc, camLook);
	
}


void Scene::controll(unsigned char *keyState, unsigned int *ArrowKeyState)
{
	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime / 1000;

	
	if (greenAlive)
	{																	// COLLISIONS															// COLLISIONS
		if (keyState[(unsigned char)'w'] == BUTTON_DOWN && player.yCoord >= -4.8f || keyState[(unsigned char)'W'] == BUTTON_DOWN && player.yCoord  >= -4.8f) { player.yCoord -= Playerspeed; } // UP
		if (keyState[(unsigned char)'s'] == BUTTON_DOWN && player.yCoord <=  2.5f || keyState[(unsigned char)'S'] == BUTTON_DOWN && player.yCoord <=   2.5f) { player.yCoord += Playerspeed; } // DOWN
		if (keyState[(unsigned char)'a'] == BUTTON_DOWN && player.xCoord <=	 4.5f || keyState[(unsigned char)'A'] == BUTTON_DOWN && player.xCoord  <=  4.5f) { player.xCoord += Playerspeed; } // LEFT
		if (keyState[(unsigned char)'d'] == BUTTON_DOWN && player.xCoord >= -4.5f || keyState[(unsigned char)'D'] == BUTTON_DOWN && player.xCoord  >= -4.5f) { player.xCoord -= Playerspeed; } // RIGHT  
	}

	if (purpleAlive)
	{															// COLLISIONS
		if (ArrowKeyState[0] == BUTTON_DOWN && player2.yCoord >= -4.8f) { player2.yCoord -= Playerspeed; }	 // UP
		if (ArrowKeyState[1] == BUTTON_DOWN && player2.yCoord <=  2.5f) { player2.yCoord += Playerspeed; }	 // DOWN
		if (ArrowKeyState[2] == BUTTON_DOWN && player2.xCoord <=  4.5f) { player2.xCoord += Playerspeed; }	 // LEFT
		if (ArrowKeyState[3] == BUTTON_DOWN && player2.xCoord >= -4.5f) { player2.xCoord -= Playerspeed; }	 // RIGHT 
	}

	if (greenAlive) {
		// --------------------------------------------- BULLET PART ---------------------------------------------
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
			bullets[i].yCoord -= 0.25f;
		}

		if (bullets[i].yCoord < -5.0)
		{
			bullets[i].direction = 0;	//dircetion
			bullets[i].xCoord = (0.5 + i * 0.02) - 1;
			bullets[i].yCoord = bulletsPlace;
			//std::cout << bulletsInUse << "\n";
		}
	}

	if (purpleAlive) 
	{
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
			bullets2[i].yCoord -= 0.25f;
		}

		if (bullets2[i].yCoord < -5.0)
		{
			bullets2[i].direction = 0;	//direction
			bullets2[i].xCoord = (0.5 + i * 0.02) - 1;
			bullets2[i].yCoord = bulletsPlace;
			//std::cout << bulletsInUse << "\n";
		}
	}



}


void Scene::MoventBox() 
{

	// bullet to purple enemy
	for (size_t i = 0; i < bullets2.size(); i++)
	{
		for (size_t x = 0; x < purpleEnemys.size(); x++)
		{
			if (bullets2[i].xCoord >= (purpleEnemys[x].xCoord - 0.2) && bullets2[i].xCoord <= (purpleEnemys[x].xCoord + 0.2)
				&& bullets2[i].yCoord >= (purpleEnemys[x].yCoord - 0.2) && bullets2[i].yCoord <= (purpleEnemys[x].yCoord + 0.2))
			{
				//randomize
				//
				float RandX = rand() % 800;
				float RandY = rand() % 1000;
				RandX = (RandX / 100) - 4;
				RandY = (-(RandY / 100) - 2);

				purpleEnemys[x].xCoord = RandX;
				purpleEnemys[x].yCoord = RandY;

				//bullet delete on hit
				// ADD BULLET HIT SOUND HERE
				bullets2[i].direction = 0;	//dircetion
				bullets2[i].xCoord = (0.5 + i * 0.02) - 1;
				bullets2[i].yCoord = bulletsPlace;
				//BULLETS SPEED
				changeableSpeed += 0.000025f;
				purpleScore += 10;
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
				changeableSpeed += 0.000025f;
				greenScore += 10;
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

	// bullet to purple enemy
	for (size_t i = 0; i < bullets2.size(); i++)
	{
		for (size_t x = 0; x < purpleEnemys.size(); x++)
		{
			if (bullets[i].xCoord >= (purpleEnemys[x].xCoord - 0.2) && bullets[i].xCoord <= (purpleEnemys[x].xCoord + 0.2)
				&& bullets[i].yCoord >= (purpleEnemys[x].yCoord - 0.2) && bullets[i].yCoord <= (purpleEnemys[x].yCoord + 0.2))
			{

				//bullet delete on hit
				bullets[i].direction = 0;	//dircetion
				bullets[i].xCoord = (0.5 + i * 0.02) - 1;
				bullets[i].yCoord = bulletsPlace;
			}
		}
	}

	//	-- -- -- player colisions -- -- --

	// player1 colision
	if (greenAlive)
	{

		for (size_t x = 0; x < purpleEnemys.size(); x++)
		{
			if (player.xCoord >= (purpleEnemys[x].xCoord - 0.2) && player.xCoord <= (purpleEnemys[x].xCoord + 0.2)
				&& player.yCoord >= (purpleEnemys[x].yCoord - 0.2) && player.yCoord <= (purpleEnemys[x].yCoord + 0.2))
			{
				std::cout << "Playone hit by purple";
				greenAlive = false;
			}
		}

		for (size_t x = 0; x < greenEnemys.size(); x++)
		{
			if (player.xCoord >= (greenEnemys[x].xCoord - 0.2) && player.xCoord <= (greenEnemys[x].xCoord + 0.2)
				&& player.yCoord >= (greenEnemys[x].yCoord - 0.2) && player.yCoord <= (greenEnemys[x].yCoord + 0.2))
			{
				greenAlive = false;
			}
		}
		if (!greenAlive) 
		{ 
			std::cout << "green Dead"; 				
			deathScore = mainScore;
		}
	}
	// player2 colision
	if (purpleAlive)
	{
		for (size_t x = 0; x < purpleEnemys.size(); x++)
		{
			if (player2.xCoord >= (purpleEnemys[x].xCoord - 0.2) && player2.xCoord <= (purpleEnemys[x].xCoord + 0.2)
				&& player2.yCoord >= (purpleEnemys[x].yCoord - 0.2) && player2.yCoord <= (purpleEnemys[x].yCoord + 0.2))
			{
				purpleAlive = false;
			}
		}

		for (size_t x = 0; x < greenEnemys.size(); x++)
		{
			if (player2.xCoord >= (greenEnemys[x].xCoord - 0.2) && player2.xCoord <= (greenEnemys[x].xCoord + 0.2)
				&& player2.yCoord >= (greenEnemys[x].yCoord - 0.2) && player2.yCoord <= (greenEnemys[x].yCoord + 0.2))
			{
				purpleAlive = false;
			}
		}
		if (!purpleAlive) 
		{ 
			std::cout << "purple Dead";
			deathScore = mainScore;
		}
	}
	if (!greenAlive)
	{
		//std::cout << "green Dead";
		deltaScore = mainScore - deathScore;
		std::cout << deltaScore;
	}
	if (!purpleAlive)
	{
		//std::cout << "purple Dead";
		deltaScore = mainScore - deathScore;
		std::cout << deltaScore;
	}
	if (deltaScore >= 100)
	{
		purpleAlive = true;
		greenAlive = true;
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
	purpleEnemys[purpleEnemys.size() - 1].object.createObj(ptrEnemyVert, sizeof(vertices), prtEnemyInd, sizeof(indices));

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

void Scene::specialEnemyCreate()
{
	// square ver and ind

	GLfloat vertices[192] = {

		-1.0f, 0.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	};


	GLuint indices[36] = {
		// front
		0, 1, 2,
		0, 2, 3,

	};

	GLfloat * ptrEnemyVert = vertices;
	GLuint * prtEnemyInd = indices;


	//	std::cout << "Object \n";
	specialEnemy.object.createObj(ptrEnemyVert, sizeof(vertices), prtEnemyInd, sizeof(indices));

}

void Scene::SetBulet()
{

	GLfloat vertices[] = {
						 
		-0.025f, 0.0f, -0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.025f, 0.0f, 0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.025f, 0.0f, 0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.025f, 0.0f, -0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

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

void Scene::SetSpecialEnemyBullets()
{

	GLfloat vertices[] = {

		-0.15f, 0.0f, -0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.15f, 0.0f, 0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.15f, 0.0f, 0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.15f, 0.0f, -0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,

	};


	GLfloat * ptrEnemyVert = vertices;
	GLuint * prtEnemyInd = indices;


	specialEnemyBullets[specialEnemyBullets.size() - 1].object.createObj(ptrEnemyVert, sizeof(vertices), prtEnemyInd, sizeof(indices));

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

//// SET MAIN MENU TEST
//void Scene::SetMainMenu()
//{
//
//	GLfloat vertices[] = {
//		// Fill in the top face vertex data.							 
//		-0.025f, 0.01f, -0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
//		-0.025f, 0.01f, 0.15f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//		0.025f, 0.01f, 0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//		0.025f, 0.01f, -0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//
//	};
//
//	GLuint indices[] = {
//		// front
//		0, 1, 2,
//		0, 2, 3,
//
//	};
//
//
//	GLfloat * ptrMainMenuV = vertices;
//	GLuint * ptrMainMenuI = indices;
//
//
//	mainMenu[mainMenu.size() - 1].object.createObj(ptrMainMenuV, sizeof(vertices), ptrMainMenuI, sizeof(indices));
//
//};