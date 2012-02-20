#include "Input.h"
#include "common.h"
#include "Coord3.h"
#include "Camera.h"

Input* Input::p_pInstance = 0;
Input* Input::GetInstance()
{
	if(p_pInstance == 0)
	{
		p_pInstance = new Input();
	}
	return p_pInstance;
}

Input::Input()
{
	for(int i = 0; i < 256; ++i)
	{
		keyDown[i] = false;
	}
}
void Input::KeyUpMap(unsigned char key, int x, int y)
{
	//keyDown[key] = false;
	
	switch (key)
	{
	case 'W':
	case 'w':
		//Zoom camera in.
		keyDown[KEY_W] = false;
		break;
	case 'S':
	case 's':
		//Zoom camera out.
		keyDown[KEY_S] = false;
		break;
	case 'A':
	case 'a':
		//Move camera left.
		keyDown[KEY_A] = false;
		break;
	case 'D':
	case 'd':
		//Move camera right.
		keyDown[KEY_D] = false;
		break;
	case ' ':
		//Move camera up.
		keyDown[KEY_SPACE] = false;
		break;
	case 'C':
	case 'c':
		//Move camera down.
		keyDown[KEY_C] = false;
		break;
	default:
		break;
	}
	
}


void Input::KeyMap(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'W':
	case 'w':
		//Move camera forward.
		keyDown[KEY_W] = true;
		break;
	case 'S':
	case 's':
		//Move camera backward.
		keyDown[KEY_S] = true;
		break;
	case 'A':
	case 'a':
		//Move camera left.
		keyDown[KEY_A] = true;
		break;
	case 'D':
	case 'd':
		//Move camera right.
		keyDown[KEY_D] = true;
		break;
	case 'C':
	case 'c':
		//Move camera down.
		keyDown[KEY_C] = true;
		break;
	case ' ':
		//Move camera up.
		keyDown[KEY_SPACE] = true;
		break;
	case 'Q':
	case 'q':
	case 27:
		//Exit the program.
		exit(0);
		break;
	case 'G':
	case 'g':
		displayDebugInfo = !displayDebugInfo;
		displayHelp = false;
		break;
		/*
	case 'M':
	case 'm':
		//Toggle the use of the mouse.
		useMouse = !useMouse;
		if (useMouse)
			glutSetCursor(GLUT_CURSOR_NONE);
		else
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		break;
	case '+':
	case '=':
		//Toggles between fullscreen and windowed mode.
		if (!fullScreen)
		{
			useMouse = true;
			glutSetCursor(GLUT_CURSOR_NONE);
			glutFullScreen();
		}
		else
		{
			glutPositionWindow(200, 200);
			glutReshapeWindow(640, 480);
		}

		fullScreen = !fullScreen;
		break;
	case 'W':
	case 'w':
		//Toggles between wireframe and fill mode.
		useWireframe = !useWireframe;
		if (useWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'H':
	case 'h':
		displayHelp = !displayHelp;
		displayDebugInfo = false;
		break;
	
	case 'R':
	case 'r':
		ResetFootball();

		//Reset all the players.
		for (int i = 0; i < 22; i++)
			players[i].reset();

		break;
	case 'T':
	case 't':
		ResetFootball();

		//Reset all the players.
		for (int i = 0; i < 22; i++)
			players[i].reset();

		//Make all players run.
		for (int i = 1; i < 21; i++)
			players[i].setRunning(true, true);

		
		break;
		*/
	default:
		break;
	}
}

void Input::HandleInput()
{
	const float l_rScale = 50.f;

    if (keyDown[KEY_SPACE])
	{
		Camera::GetInstance()->GetPosition().SetY(Camera::GetInstance()->GetPosition().GetY() + 1.f);
	}
    if (keyDown[KEY_C])
	{
        Camera::GetInstance()->GetPosition().SetY(Camera::GetInstance()->GetPosition().GetY() - 1.f);
	}
    if (keyDown[KEY_W])
    {
		Camera::GetInstance()->GetDirVec().Scale(l_rScale);
        Camera::GetInstance()->GetDirVec().Normalize();
        Camera::GetInstance()->GetDirVec().Scale(turboSpeed);
        //Coord3_add(Camera::GetInstance()->GetPosition(), Camera::GetInstance()->GetDirVec());
		Camera::GetInstance()->SetPosition(Camera::GetInstance()->GetPosition() + Camera::GetInstance()->GetDirVec());
    }
    if (keyDown[KEY_S])
    {
        Camera::GetInstance()->GetDirVec().Scale(l_rScale);
        Camera::GetInstance()->GetDirVec().Normalize();
        Camera::GetInstance()->GetDirVec().Scale(turboSpeed);
        //Coord3_subtract(&Camera::GetInstance()->GetPosition(), Camera::GetInstance()->GetDirVec());
		Camera::GetInstance()->SetPosition(Camera::GetInstance()->GetPosition() - Camera::GetInstance()->GetDirVec());

    }
    if (keyDown[KEY_A])
    {
		Coord3 cross = Camera::GetInstance()->GetDirVec().CrossProduct(Camera::GetInstance()->GetUp());

        //Sometimes the vector's length is < 1.0.
        cross.Scale(l_rScale);
        cross.Normalize();
        cross.Scale(turboSpeed);

        //Coord3_subtract(&Camera::GetInstance()->GetPosition(), cross);
		Camera::GetInstance()->SetPosition(Camera::GetInstance()->GetPosition() - cross);
    }
    if (keyDown[KEY_D])
    {
        Coord3 cross = Camera::GetInstance()->GetDirVec().CrossProduct(Camera::GetInstance()->GetUp());
        //Coord3_crossproduct(Camera::GetInstance()->GetDirVec(), Camera::GetInstance()->GetUp(), &cross);
		

        //Sometimes the vector's length is < 1.0.
        cross.Scale(l_rScale);
        cross.Normalize();
        cross.Scale(turboSpeed);

		Camera::GetInstance()->SetPosition(Camera::GetInstance()->GetPosition() + cross);
    }
}