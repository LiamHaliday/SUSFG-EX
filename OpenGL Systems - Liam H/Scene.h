#pragma once

#ifndef SCENE_H
#define SCENE_H


#include "object.h"
#include "Text.h"




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


	FMOD::System* audioMgr;
	FMOD::Sound* hitSound;
	FMOD::Sound* bgMusic;

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

		result = audioMgr->createSound("Assets/audio/click.wav", FMOD_DEFAULT, 0, &hitSound);

		result = audioMgr->createSound("Assets/audio/backGroud.wav", FMOD_LOOP_NORMAL, 0, &bgMusic);

		bgMusic->setMode(FMOD_LOOP_NORMAL);

		return true;
	}

	float adjacent;
	float opposite;

	void init();
	void render();

	void SetBulet();
	void SetBulet2();
	void SetStarFloor();
	void Setenemy();
	void Setenemy2();

	void MoventBox();

	void update(unsigned char *keyState, unsigned int *ArrowKeyState);

	void controll(unsigned char *keyState, unsigned int *ArrowKeyState);

	camera mainCam;


private:

	// star wall scroll
	float starScrollPoint[2] = {0.0f, -10.0f};
	
	//object* enemy = new object();
	float bulletsPlace = 4.0f;

	float fireTime = 0.1;
	float fireDifference = 0.0;
	float fireDifferencep2 = 0.0;
	float BulletX;
	bool IsLeft = false;

	//text
	TextLabel* label;
	TextLabel* endlabel;
	TextLabel* EnterToRestart;
	TextLabel* FPS;

	objectStruct player;
	objectStruct player2;
	objectStruct mainMenuObject;

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


	std::vector<objectStruct> pinkEnemys;
	std::vector<objectStruct> greenEnemys;

	std::vector<objectStruct> Stars;

	glm::vec2 whiteBoxVec;

	//keyboard bits
	unsigned char keyState[255];
	float Playerspeed;

	float CamLookX = 0.0f;
	float CamLookY = 0.0f;
	float CamLookZ = 0.0f;

	glm::vec3 camLoc{ 0.0, 5.0, -0.01 };
	glm::vec3 camLook{ 0,0,0 };

	// deltaTime
	float deltaTime;
	float currentFrame;
	float lastFrame;

	float CurrentFPS;
};

#endif