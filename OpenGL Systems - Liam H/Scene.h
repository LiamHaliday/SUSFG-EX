#pragma once

#ifndef SCENE_H
#define SCENE_H


#include "object.h"
#include "Text.h"


enum Scenes
{
	MAINMENU,
	GAMESCENE,
	HELP
};

struct objectStruct
{
	object object;
	float xCoord;
	float yCoord;
	float zCoord;
	float mag;
	float dir;

	int direction;
};


class Scene
{
public:

	Scene();

	void Setsquare();
	void SetFloor();

	void MainMenu();
	void UpdateMainMenu(int menuNumber);
	void MainMenuRender(int menuNumber);
	void Help();

	FMOD::System* audioMgr;
	FMOD::Sound* shotSound;
	FMOD::Sound* Explosion;
	FMOD::Sound* bgMusic;
	FMOD::Sound* lvlMusic;

	bool InitFmod()
	{

		FMOD_RESULT result;

		result = FMOD::System_Create(&audioMgr);
		if (result != FMOD_OK) return false;

		result = audioMgr->init(50, FMOD_INIT_NORMAL, 0);
		if (result != FMOD_OK) return false;

		return true;
	}

	const bool LoadAudio()
	{
		FMOD_RESULT result;

		result = audioMgr->createSound("Assets/audio/LazerShot.wav", FMOD_DEFAULT, 0, &shotSound);

		result = audioMgr->createSound("Assets/audio/Explosion.mp3", FMOD_DEFAULT, 0, &Explosion);

		result = audioMgr->createSound("Assets/audio/MainMenu.mp3", FMOD_LOOP_NORMAL, 0, &bgMusic);

		result = audioMgr->createSound("Assets/audio/MainLevel.mp3", FMOD_LOOP_NORMAL, 0, &lvlMusic);

		bgMusic->setMode(FMOD_LOOP_NORMAL);

		lvlMusic->setMode(FMOD_LOOP_NORMAL);

		return true;
	}
	bool bosskilled = false;


	float adjacent;
	float opposite;

	void init();
	void render();

	void SetBulet();
	void SetBulet2();
	void SetSpecialEnemyBullets();
	void SetStarFloor();
	void Setenemy();
	void Setenemy2();

	void specialEnemyCreate();

	void SetMainMenu();	// TEST

	void MoventBox();

	void restart();

	void update(unsigned char *keyState, unsigned int *ArrowKeyState);

	void controll(unsigned char *keyState, unsigned int *ArrowKeyState);

	camera mainCam;


private:
	// play Alives
	bool greenAlive = true;
	bool purpleAlive = true;

	// score
	int greenScore;
	int purpleScore;
	int mainScore;
	int deltaScore;
	int deathScore;
	int bossHealth;
	// star wall scroll
	float starScrollPoint[2];
	float starScrollPointBack[2];
	float starScrollPointBack2[2];

	//object* enemy = new object();
	float bulletsPlace = 4.0f;

	float fireTime = 0.1;
	float fireDifference = 0.0;
	float fireDifferencep2 = 0.0;
	float EnemyFireDifference = 0.0;
	
	float BulletX;
	bool IsLeft = false;

	//text
	TextLabel* FPS;
	TextLabel* greenScoreText;
	TextLabel* purpleScoreText;
	TextLabel* mainScoreText;
	TextLabel* restartTEXT;

	objectStruct player;
	objectStruct player2;

	//mainMenu
	objectStruct mainMenuObject;
	objectStruct mainMenuObject1;
	objectStruct mainMenuObject2;
	objectStruct mainMenuHelp;

	objectStruct mainMenuHelp1;

	objectStruct specialEnemy;
	std::vector<objectStruct> specialEnemyBullets;
	float specialEnemyMovement = 0;
	int enemybulletsinuse;

	int bossSpawnScore;
	bool isSpawned = false;

	std::vector<objectStruct> mainMenu;	// TEST

	std::vector<objectStruct> starFloor;

	object floor;
	object end;
	bool lost = false;

	bool buletStart = false;

	//bullets 
	std::vector<objectStruct> bullets;
	int bulletsInUse;

	std::vector<objectStruct> bullets2;
	int bulletsInUse2;

	// enemy objects
	std::vector<objectStruct> purpleEnemys;
	std::vector<objectStruct> greenEnemys;

	std::vector<objectStruct> Stars;

	glm::vec2 whiteBoxVec;

	//keyboard bits
	unsigned char keyState[255];
	float Playerspeed;
	float enemySpeed;
	float changeableSpeed = 0.0005f;

	float CamLookX = 0.0f;
	float CamLookY = 0.0f;
	float CamLookZ = 0.0f;

	glm::vec3 camLocMainMenu{ 0.0, 1.79, -0.000001 };

	glm::vec3 camLoc{ 0.0, 6.0, -2.5 };	// CAMERA LOCATION
	glm::vec3 camLook{ 0, 0, 0 };

	// deltaTime
	float deltaTime;
	float currentFrame;
	float lastFrame;

	float CurrentFPS;
};

#endif