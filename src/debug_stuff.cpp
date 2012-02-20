//file: debug_stuff.cpp

#include <cstdio>
#include <iostream>
#include "glut.h"
#include <cstring>
#include "common.h"
#include "Coord3.h"
#include "drawing.h"
#include "Camera.h"
using namespace std;

extern Frog g_sFrog;
//extern float cameraPos[3];
extern int scrWidth;
extern int scrHeight;
float fps;

void CalculateFrameRate()
{
    static int numberOfFrames = 0;
    static int previousFrameTime = 0;
    int elapsedTime;

    numberOfFrames++;
    elapsedTime = glutGet(GLUT_ELAPSED_TIME);

    //Only update the framerate once per second.
    if (elapsedTime - previousFrameTime > 1000)
    {
        fps = numberOfFrames*1000.0f/(elapsedTime-previousFrameTime);
        previousFrameTime = elapsedTime;
        numberOfFrames = 0;
    }
}

void PrintDebugInfo()
{
    glDisable(GL_LIGHTING);

    char buffer[50];

    //Do this so we can use window coordinates
    //for the DrawString function.
    glPushMatrix(); //Save the current modelview matrix.
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); //Save the current projection matrix.
    glLoadIdentity();

    //Switch to 2D.
    gluOrtho2D(0, scrWidth, 0, scrHeight);
    glColor3f(1.0f, 1.0f, 1.0f);
	sprintf(buffer, "Camera pos: (%.2f, %.2f, %.2f)", Camera::GetInstance()->GetPosition().GetX(),
                                                      Camera::GetInstance()->GetPosition().GetY(),
                                                      Camera::GetInstance()->GetPosition().GetZ());
    DrawString(buffer, 5, scrHeight - 10);

    sprintf(buffer, "Frog pos: (%.2f, %.2f, %.2f)",
            g_sFrog.position.GetX(), g_sFrog.position.GetY(),
            g_sFrog.position.GetZ());
    DrawString(buffer, 5, scrHeight - 25);

    sprintf(buffer, "FPS: %4.2f", fps);
    DrawString(buffer, scrWidth - 120, scrHeight - 10);
    
    //Go back to 3D.
    glPopMatrix(); //Restore previous projection matrix.

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix(); //Restore previous modelview matrix.

    glEnable(GL_LIGHTING);
}

void ResetFootball()
{
    g_sFrog.position.SetX(0.0f);
    g_sFrog.position.SetY(-3.0f);
    g_sFrog.position.SetZ(138.0f);

    g_sFrog.velocity.SetX(0.0f);
    g_sFrog.velocity.SetY(3.0f);
    g_sFrog.velocity.SetZ(-2.289f);
    g_sFrog.rotationAngle = 0.0f;
    g_sFrog.kicked = false;
}
