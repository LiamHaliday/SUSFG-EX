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

	void update(unsigned char *keyState, unsigned int *ArrowKeyState);


private:
	
	//object* enemy = new object();

	//text
	TextLabel* label;
	TextLabel* endlabel;
	TextLabel* EnterToRestart;
	TextLabel* FPS;

	objectStruct player;
	objectStruct mainMenuObject;

	object floor;
	object end;
	bool lost = false;

	bool buletStart = false;

	//bullets 
	std::vector<objectStruct> bullets;
	int bulletsInUse;

	std::vector<objectStruct> pinkEnemys;
	std::vector<objectStruct> greenEnemys;

	glm::vec2 whiteBoxVec;

	//keyboard bits
	unsigned char keyState[255];
	float Playerspeed;

	float CamLookX = 0.0f;
	float CamLookY = 0.0f;
	float CamLookZ = 0.0f;

	// deltaTime
	float deltaTime;
	float currentFrame;
	float lastFrame;

	float CurrentFPS;
};

#endif