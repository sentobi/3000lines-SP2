/******************************************************************************/
/*!
\file	Application.cpp
\author 3000 Lines Studio
\brief
Functions for application
*/
/******************************************************************************/

#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "MainMenu.h"
#include "SP2.h"
#include "SharedData.h"

GLFWwindow* m_window;

const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

/******************************************************************************/
/*!
\brief	Application default constructor
*/
/******************************************************************************/
Application::Application()
{
}

/******************************************************************************/
/*!
\brief	Application default destructor
*/
/******************************************************************************/
Application::~Application()
{
}

void resize_callback(GLFWwindow * window, int w, int h)
{
    glViewport(0, 0, w, h);     //update opengl the new window size
}

void Application::get_resolution()
{
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    SharedData::GetInstance()->width = mode->width;
    SharedData::GetInstance()->height = mode->height;
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

    get_resolution();

	//Create a window and create its OpenGL context
    //m_window = glfwCreateWindow(800, 600, "Computer Graphics", NULL, NULL);  //800 x 600
    //m_window = glfwCreateWindow(SharedData::GetInstance()->width, SharedData::GetInstance()->height, "Computer Graphics", NULL, NULL);
    m_window = glfwCreateWindow(SharedData::GetInstance()->width, SharedData::GetInstance()->height, "Romantic Room", glfwGetPrimaryMonitor(), NULL);
    //glfwSetWindowSize(m_window, SharedData::GetInstance()->width, SharedData::GetInstance()->height);

    glfwSetWindowSizeCallback(m_window, resize_callback);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

void Application::Run()
{
	//Main Loop
	Scene *scene = 0;
    switch (SharedData::GetInstance()->program_state)
    {
    case PROGRAM_MENU: scene = new MainMenu();
        if (SharedData::GetInstance()->playMusic) {
            SharedData::GetInstance()->engine->play2D("Sound/main menu bgm.XM", true);
        }
        break;
    case PROGRAM_GAME: scene = new SP2();
        if (SharedData::GetInstance()->playMusic) {
            SharedData::GetInstance()->engine->play2D("Sound/game bgm.S3M", true);
        }
        break;
    }
	scene->Init();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
    while (!glfwWindowShouldClose(m_window) && SharedData::GetInstance()->program_state != PROGRAM_EXIT)
	{
		scene->Update(m_timer.getElapsedTime());
        scene->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        //setting cursor
        if (SharedData::GetInstance()->program_state == PROGRAM_MENU || SharedData::GetInstance()->gamestate == GAME_STATE_DIALOGUE || SharedData::GetInstance()->gamestate == GAME_STATE_SHOP
            || SharedData::GetInstance()->paused || SharedData::GetInstance()->rabbitFight || SharedData::GetInstance()->gameEnd)
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        else
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwGetCursorPos(m_window, &SharedData::GetInstance()->cursor_newxpos, &SharedData::GetInstance()->cursor_newypos);

        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.

        if (SharedData::GetInstance()->programstate_change) {
            delete scene;
            SharedData::GetInstance()->programstate_change = false;
            
            SharedData::GetInstance()->engine->stopAllSounds();
            switch (SharedData::GetInstance()->program_state)
            {
            case PROGRAM_MENU: scene = new MainMenu();
                if (SharedData::GetInstance()->playMusic) {
                    SharedData::GetInstance()->engine->play2D("Sound/main menu bgm.XM", true);
                }
                break;
            case PROGRAM_GAME: scene = new SP2();
                if (SharedData::GetInstance()->playMusic) {
                    SharedData::GetInstance()->engine->play2D("Sound/game bgm.S3M", true);
                }
                break;
            }
            scene->Init();
        }

	} //Check if the ESC key had been pressed or if the window had been closed
	scene->Exit();
	delete scene;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
