#include "Scene.h"

// this is a comment for testing stuffs
#define BUTTON_UP   0 
#define BUTTON_DOWN 1

unsigned char keyState[255];
unsigned int ArrowKeyState[4];

void keyboard(unsigned char key, int x, int y){
	keyState[key] = BUTTON_DOWN;
}
void keyboard_up(unsigned char key, int x, int y){
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




Scene MainScene;

bool mainMenu = true;
bool gameInit = false;

/****************************************************/
// Filename: main.cpp
// Created: Liam Haliday
// Description: sets up the menu
/****************************************************/
void init()
{
	MainScene.init();
}

/****************************************************/
// Filename: main.cpp
// Created: Liam Haliday
// Description: render the Scenes 
/****************************************************/
void render(void)
{
	MainScene.render();

	
}

/****************************************************/
// Filename: main.cpp
// Created: Liam Haliday
// Description: updates the Scenes 
/****************************************************/
bool fullScreen = false;
bool fullscreenButton = true;

void update() {
	// update game information.
	glutPostRedisplay();


	MainScene.update(keyState, ArrowKeyState);


	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);

	// check buttons
	for (size_t i = 0; i < 255; i++)
	{
		if (keyState[i] == BUTTON_DOWN)
		{
			std::cout << (unsigned char)i;
		}
	}
	for (size_t i = 0; i < 4; i++)
	{
		if (ArrowKeyState[i] == BUTTON_DOWN)
		{
			std::cout << i;
		}
	}

	std::cout << std::endl;



	if (keyState[(unsigned char)'p'] == BUTTON_UP || keyState[(unsigned char)'P'] == BUTTON_UP) { fullScreen = true; }

	if (fullscreenButton)
	{
		if (fullScreen)
		{
			//if (keyState[(unsigned char)'p'] == BUTTON_DOWN || keyState[(unsigned char)'P'] == BUTTON_DOWN) { fullScreen = false; }
		//	glutFullScreen();
			//fullscreenButton = true;
		}
		else
		{
	//	if (keyState[(unsigned char)'p'] == BUTTON_DOWN || keyState[(unsigned char)'P'] == BUTTON_DOWN) { fullScreen = true; }
	//	glutReshapeWindow(1600, 1000);
	//	fullscreenButton = false;
		}
	}
	

	glutSpecialFunc(SpecialInput);
	glutSpecialUpFunc(SpecialInput_up);
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 5); glutInitWindowSize(1600, 1000);
	glutCreateWindow("SUSFG-EX");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutIdleFunc(update);
	glutMainLoop();
	return 0;
}

