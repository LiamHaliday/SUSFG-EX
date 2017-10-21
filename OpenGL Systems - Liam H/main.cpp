#include "Scene.h"

// this is a comment for testing stuffs
#define BUTTON_UP   0 
#define BUTTON_DOWN 1

unsigned char keyState[255];
unsigned int ArrowKeyState[4];

void keyboard(unsigned char key, int x, int y) {
	keyState[key] = BUTTON_DOWN;
}
void keyboard_up(unsigned char key, int x, int y) {
	keyState[key] = BUTTON_UP;
}

void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		ArrowKeyState[0] = BUTTON_DOWN;
		break;
	case GLUT_KEY_DOWN:
		ArrowKeyState[1] = BUTTON_DOWN;
		break;
	case GLUT_KEY_LEFT:
		ArrowKeyState[2] = BUTTON_DOWN;
		break;
	case GLUT_KEY_RIGHT:
		ArrowKeyState[3] = BUTTON_DOWN;
		break;
	}
}
void SpecialInput_up(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		ArrowKeyState[0] = BUTTON_UP;
		break;
	case GLUT_KEY_DOWN:
		ArrowKeyState[1] = BUTTON_UP;
		break;
	case GLUT_KEY_LEFT:
		ArrowKeyState[2] = BUTTON_UP;
		break;
	case GLUT_KEY_RIGHT:
		ArrowKeyState[3] = BUTTON_UP;
		break;
	}
}


int sceneSwitch;

Scene MainScene;

bool mainMenu = true;
bool gameInit = false;
int menuNumber = 0;

enum MyEnum
{
	START,
	HELPPART,
	EXIT
};

/****************************************************/
// Filename: main.cpp
// Created: Liam Haliday
// Description: sets up the menu
/****************************************************/
void init()
{
	sceneSwitch = MAINMENU;

	switch (sceneSwitch)
	{
	case MAINMENU:
	{
		// play the main menu
		MainScene.MainMenu();

		break;
	}
	case GAMESCENE:
	{

		MainScene.init();

		break;
	}

	default:
		break;
	}

}

/****************************************************/
// Filename: main.cpp
// Created: Liam Haliday
// Description: render the Scenes 
/****************************************************/
bool gameinit = false;
void render(void)
{
	switch (sceneSwitch)
	{
	case MAINMENU:
	{
		// play the main menu
		MainScene.MainMenuRender(menuNumber);

		break;
	}
	case GAMESCENE:
	{
		if (!gameinit)
		{
			MainScene.init();
			gameinit = true;
			std::cout << "init";
		}
		MainScene.render();
		break;
	}
	}

}



/****************************************************/
// Filename: main.cpp
// Created: Liam Haliday
// Description: updates the Scenes 
/****************************************************/
bool fullScreen = false;
bool fullscreenButton = true;
GLfloat getTime = 1000000;


void update() {
	// update game information.
	glutPostRedisplay();
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
	if (keyState[27] == BUTTON_DOWN) { exit(0); };

	switch (sceneSwitch)
	{
	case MAINMENU:
	{
		// play the main menu

		//MainScene.UpdateMainMenu(sceneSwitch);
		unsigned int interval = GetCurrentTime() - getTime;
		//std::cout << getTime << std::endl;
		std::cout << interval << std::endl;

		if (interval > 200)
		{
			if (keyState[(unsigned char)'w'] == BUTTON_DOWN && menuNumber != 0)
			{
				menuNumber--;
				getTime = GetCurrentTime();
			}
			if (keyState[(unsigned char)'s'] == BUTTON_DOWN && menuNumber != 2)
			{
				menuNumber++;
				getTime = GetCurrentTime();
			}

			if (ArrowKeyState[0] == BUTTON_DOWN && menuNumber != 0) {
				menuNumber--;
				getTime = GetCurrentTime();
			};
			if (ArrowKeyState[1] == BUTTON_DOWN && menuNumber != 2) {
				menuNumber++;
				getTime = GetCurrentTime();
			};

			if (keyState[(unsigned char)' '] == BUTTON_DOWN && menuNumber == 0) {
				sceneSwitch = GAMESCENE;
				getTime = GetCurrentTime();
			};
			if (keyState[13] == BUTTON_DOWN && menuNumber == 0) {
				sceneSwitch = GAMESCENE;
				getTime = GetCurrentTime();
			}; // enter

			if (keyState[(unsigned char)' '] == BUTTON_DOWN && menuNumber == 2) { exit(0); };
			if (keyState[13] == BUTTON_DOWN && menuNumber == 2) { exit(0); }; // enter

		}
		//	if (keyState[(unsigned char)'3'] == BUTTON_DOWN) { /* EXIT GAME */ };

		break;
	}

	case HELP:
	{
		if (keyState[(unsigned char)'1'] == BUTTON_DOWN) { sceneSwitch = GAMESCENE; };

		break;
	}
	case GAMESCENE:
	{

		MainScene.update(keyState, ArrowKeyState);

		break;
	}

	default:
		break;
	}





	//// check buttons
	//for (size_t i = 0; i < 255; i++)
	//{
	//	if (keyState[i] == BUTTON_DOWN)
	//	{
	//		std::cout << (unsigned char)i;
	//	}
	//}
	//for (size_t i = 0; i < 4; i++)
	//{
	//	if (ArrowKeyState[i] == BUTTON_DOWN)
	//	{
	//		std::cout << i;
	//	}
	//}

	std::cout << std::endl;

	//	glutFullScreen();

	/*
	if (keyState[(unsigned char)'p'] == BUTTON_UP || keyState[(unsigned char)'P'] == BUTTON_UP) { fullScreen = true; }

	if (fullscreenButton)
	{
	if (fullScreen)
	{
	//if (keyState[(unsigned char)'p'] == BUTTON_DOWN || keyState[(unsigned char)'P'] == BUTTON_DOWN) { fullScreen = false; }
	//
	fullscreenButton = true;
	}
	else
	{
	//	if (keyState[(unsigned char)'p'] == BUTTON_DOWN || keyState[(unsigned char)'P'] == BUTTON_DOWN) { fullScreen = true; }
	//	glutReshapeWindow(1600, 1000);
	//	fullscreenButton = false;
	}
	}
	*/

	glutSpecialFunc(SpecialInput);
	glutSpecialUpFunc(SpecialInput_up);
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 5); glutInitWindowSize(1600, 1000);
	glutCreateWindow("SUPER ULTRA SPACE FIGHTING GAME: EDITION X");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutIdleFunc(update);
	glutMainLoop();
	return 0;
}


