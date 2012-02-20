//file: main.cpp

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "glut.h"
#include <windows.h>
#include "debug_stuff.h"
#include "drawing.h"
#include "Coord3.h"
#include "Model_3DS.h"
#include "player.h"

#include "Camera.h"
#include "Input.h"
#include "common.h"

using namespace std;

double frameRate = 1000.0 / 60;

//Mouse sensitivity.
const double SENSITIVITY = 0.0009;

//Various variables to draw the scene.
GLUquadricObj *sphere;
GLUquadricObj *cylinder;
GLUnurbsObj *flag;
GLfloat flagPoints[4][4][3];
GLuint turfList;
GLuint stadiumList;
GLuint redHelmetList;
GLuint blueHelmetList;
Frog g_sFrog;

bool useMouse = false;

bool fullScreen = false;
bool useWireframe = false;
bool displayHelp = true;
bool crowdWild = false;

int scrWidth = 800;
int scrHeight = 600;
int windowCenter[2] = { 0 };

//Texture handles.
GLuint grassTexture = -1;
GLuint zeroTexture = -1;
GLuint oneTexture = -1;
GLuint twoTexture = -1;
GLuint threeTexture = -1;
GLuint fourTexture = -1;
GLuint fiveTexture = -1;
GLuint flagTexture = -1;
GLuint crowdTexture = -1;
GLuint faceTexture = -1;
GLuint stfxLogo = -1;
GLuint smuLogo = -1;
GLuint easterEgg = -1;

Player players[22];

const GLfloat light0_direction[] = { 1.0f, -0.5f, 0.0f };
const GLfloat light0_position[] = {-525.0f, 200.0f, 262.0f, 1.0f};
const GLfloat light1_direction[] = { 1.0f, -0.5f, 0.0f };
const GLfloat light1_position[] = {-525.0f, 200.0f, -87.5f, 1.0f};
const GLfloat light2_direction[] = { -1.0, -0.5, 0.0 };
const GLfloat light2_position[] = {525.0f, 200.0f, 87.5f, 1.0f};
const GLfloat light3_direction[] = { -1.0, -0.5, 0.0 };
const GLfloat light3_position[] = {525.0f, 200.0f, -262.0f, 1.0f};
const GLfloat light4_direction[] = { -1.0, -0.5, 0.0 };
const GLfloat light4_position[] = {525.0f, 200.0f, -436.5f, 1.0f};
const GLfloat light5_direction[] = { -1.0, -0.5, 0.0 };
const GLfloat light5_position[] = {525.0f, 200.0f, 436.5f, 1.0f};
const GLfloat light6_direction[] = { 1.0, -0.5, 0.0 };
const GLfloat light6_position[] = {-525.0f, 200.0f, -436.5f, 1.0f};
const GLfloat light7_direction[] = { 1.0, -0.5, 0.0 };
const GLfloat light7_position[] = {-525.0f, 200.0f, 436.5f, 1.0f};
const GLfloat white_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat red_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
const GLfloat blue_ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f };
const GLfloat white_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
Model_3DS helmet, jet1, jet2, jet3;


void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DrawFlag();
    glCallList(turfList);
    glCallList(stadiumList);

    glPushMatrix();
        glRotatef(180.0, 0.0, 1.0, 0.0);
        DrawTeam();
    glPopMatrix();

    DrawFootball();

    if (crowdWild)
    {
        jet1.DrawPlane();
        jet2.DrawPlane();
        jet3.DrawPlane();
    }

    if (Input::GetInstance()->IsDisplayHelp())
        PrintHelp();

	if (Input::GetInstance()->IsDisplayDebugInfo())
        PrintDebugInfo();
    
    glutSwapBuffers();
}

void Timer(int i)
{
    static GLfloat light0_direction[] = { 1.0f, -0.5f, 0.0f };
    static GLfloat light1_direction[] = { 1.0f, -0.5f, 0.0f };
    static GLfloat light2_direction[] = { -1.0, -0.5, 0.0 };
    static GLfloat light3_direction[] = { -1.0, -0.5, 0.0 };
    static GLfloat light4_direction[] = { -1.0, -0.5, 0.0 };
    static GLfloat light5_direction[] = { -1.0, -0.5, 0.0 };
    static GLfloat light6_direction[] = { 1.0, -0.5, 0.0 };
    static GLfloat light7_direction[] = { 1.0, -0.5, 0.0 };
    float pos[3];

    //Set the mouse cursor to the center of the window.
    if (useMouse)
    {
        windowCenter[0] = glutGet(GLUT_WINDOW_X) + scrWidth / 2;
        windowCenter[1] = glutGet(GLUT_WINDOW_Y) + scrHeight / 2;
        SetCursorPos(windowCenter[0], windowCenter[1]);
    }

	Input::GetInstance()->HandleInput();
	/*
    if (g_sFrog.kicked)
    {
        //Make the g_sFrog fall down.
        g_sFrog.velocity[1] -= 0.03f;

        //Move the g_sFrog.
        Coord3_add(g_sFrog.position, g_sFrog.velocity);

        //Ball is caught at this point.
        if (g_sFrog.position[2] < -309.0f)
        {
            g_sFrog.kicked = false;
            g_sFrog.position[0] += 4.0f;

            //Make the player run for the touchdown
            //after catching the ball.
            players[21].setRunForTouchDown(true);
            //Players will stop running at this
            //point unless we do this.
            for (int i = 0; i < 22; i++)
                players[i].setWaitUntilBallIsKicked(false);
        }
    }
	*/

    players[21].getPosition(pos);

   

	//Camera::GetInstance()->SetType(Camera::GetInstance()->GetType());

	if (Camera::GetInstance()->GetType() == E_CAMERA_FREE_FLOAT)
    {
        //Prevent the camera from going out of bounds
        //in free float mode.
        if (Camera::GetInstance()->GetPosition().GetX() < -540.f)
		{
            Camera::GetInstance()->GetPosition().SetX(-540.f);
		}
        else if (Camera::GetInstance()->GetPosition().GetX() > 540.f)
		{
            Camera::GetInstance()->GetPosition().SetX(540.f);
		}

        if (Camera::GetInstance()->GetPosition().GetY() < -4.8f)
		{
            Camera::GetInstance()->GetPosition().SetY(-4.8f);
		}
        else if (Camera::GetInstance()->GetPosition().GetY() > 1290.f)
		{
            Camera::GetInstance()->GetPosition().SetY(1290.f);
		}

        if (Camera::GetInstance()->GetPosition().GetZ() < -810.f)
		{
            Camera::GetInstance()->GetPosition().SetZ(-810.f);
		}
        else if (Camera::GetInstance()->GetPosition().GetZ() > 810.f)
		{
            Camera::GetInstance()->GetPosition().SetZ(810.f);
		}
    }

	Camera::GetInstance()->GetView().SetX(Camera::GetInstance()->GetPosition().GetX() + Camera::GetInstance()->GetDirVec().GetX());
	Camera::GetInstance()->GetView().SetY(Camera::GetInstance()->GetPosition().GetY() + Camera::GetInstance()->GetDirVec().GetY());
	Camera::GetInstance()->GetView().SetZ(Camera::GetInstance()->GetPosition().GetZ() + Camera::GetInstance()->GetDirVec().GetZ());
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	Coord3 position = Camera::GetInstance()->GetPosition();

    gluLookAt(Camera::GetInstance()->GetPosition().GetX(),
		Camera::GetInstance()->GetPosition().GetY(),
		Camera::GetInstance()->GetPosition().GetZ(),
		Camera::GetInstance()->GetView().GetX(), 
		Camera::GetInstance()->GetView().GetY(),
		Camera::GetInstance()->GetView().GetZ(),
		0.0, 1.0, 0.0);

    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,
                  (crowdWild ? light0_direction : ::light0_direction));
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);    

    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,
                  (crowdWild ? light1_direction : ::light1_direction));
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION,
                  (crowdWild ? light2_direction : ::light2_direction));
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION,
                  (crowdWild ? light3_direction : ::light3_direction));
    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);

    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION,
                  (crowdWild ? light4_direction : ::light4_direction));
    glLightfv(GL_LIGHT4, GL_POSITION, light4_position);    

    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION,
                  (crowdWild ? light5_direction : ::light5_direction));
    glLightfv(GL_LIGHT5, GL_POSITION, light5_position);

    glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION,
                  (crowdWild ? light6_direction : ::light6_direction));
    glLightfv(GL_LIGHT6, GL_POSITION, light6_position);    

    glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION,
                  (crowdWild ? light7_direction : ::light7_direction));
    glLightfv(GL_LIGHT7, GL_POSITION, light7_position); 

    //Make this player change run direction at this point.
    if (pos[2] < 160.0f)
        players[21].setRunDirection(0.5f, 0.0f, -1.5f);

    //Make this player change run direction at this point.
    players[10].getPosition(pos);
    if (pos[2] > 30)
    {
        players[10].setRunDirection(0.65f, 0.0f, 0.38f);
        players[10].setDirection(45.0f);
    }

    CalculateFrameRate();

    glutPostRedisplay();
    glutTimerFunc(frameRate, Timer, 1);
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glPointSize(5.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 15.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 75.0f);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_diffuse);

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 75.0f);
    glLightfv(GL_LIGHT1, GL_AMBIENT, white_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white_diffuse);

    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15.0);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 75.0f);
    glLightfv(GL_LIGHT2, GL_AMBIENT, white_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, white_diffuse);

    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 15.0);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 75.0f);
    glLightfv(GL_LIGHT3, GL_AMBIENT, white_ambient);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, white_diffuse);

    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 15.0);
    glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 75.0f);
    glLightfv(GL_LIGHT4, GL_AMBIENT, white_ambient);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, white_diffuse);

    glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 15.0);
    glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 75.0f);
    glLightfv(GL_LIGHT5, GL_AMBIENT, white_ambient);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, white_diffuse);

    glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 15.0);
    glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 75.0f);
    glLightfv(GL_LIGHT6, GL_AMBIENT, white_ambient);
    glLightfv(GL_LIGHT6, GL_DIFFUSE, white_diffuse);

    glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 15.0);
    glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, 75.0f);
    glLightfv(GL_LIGHT7, GL_AMBIENT, white_ambient);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, white_diffuse);

    //This makes OpenGL take the polygon's color
    //into consideration when doing lighting.
    //Otherwise we get gray surfaces.
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    //Enable lights.
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_LIGHT5);
    glEnable(GL_LIGHT6);
    glEnable(GL_LIGHT7);

    glEnable(GL_LIGHTING);
        
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    GLint minFilter = GL_NEAREST_MIPMAP_NEAREST;
    GLint magFilter = GL_NEAREST_MIPMAP_NEAREST;

    //Load all the textures.
	
    loadTexture("textures\\egg.bmp", easterEgg,
                minFilter, magFilter);
    loadTexture("textures\\grass.bmp", grassTexture,
                minFilter, magFilter);
	/*
    loadTexture("textures\\five.bmp", fiveTexture,
                minFilter, magFilter);
    loadTexture("textures\\four.bmp", fourTexture,
                minFilter, magFilter);
    loadTexture("textures\\three.bmp", threeTexture,
                minFilter, magFilter);
    loadTexture("textures\\two.bmp", twoTexture,
                minFilter, magFilter);
    loadTexture("textures\\one.bmp", oneTexture,
                minFilter, magFilter);
    loadTexture("textures\\zero.bmp", zeroTexture,
                minFilter, magFilter);
    loadTexture("textures\\crowd.bmp", crowdTexture,
                minFilter, magFilter);
    loadTexture("textures\\face.bmp", faceTexture,
                GL_LINEAR, magFilter);
    loadTexture("textures\\smuLogo.bmp", smuLogo,
                GL_LINEAR, magFilter);
    loadTexture("textures\\stfxLogo.bmp", stfxLogo,
                GL_LINEAR, magFilter);
	*/

    loadFlagTexture();
    SkyBox_CreateTextures();

    sphere = gluNewQuadric();
    cylinder = gluNewQuadric();

    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);

    gluQuadricTexture(cylinder, GL_TRUE);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    
    //Generate the control points for the flag.
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            flagPoints[i][j][0] = 2.0*((GLfloat)i - 1.5);
            flagPoints[i][j][1] = 2.0*((GLfloat)j - 1.5);

        if ((i == 1 || i == 2) && (j == 1 || j == 2))
            flagPoints[i][j][2] = 3.0;
        else
            flagPoints[i][j][2] = -3.0;
        }
    } 

    flagPoints[2][2][2] -= 5.0f;
    flagPoints[2][1][2] -= 5.0f;

    flagPoints[1][2][2] -= 10.0f;
    flagPoints[1][1][2] -= 10.0f;

    flag = gluNewNurbsRenderer();
    gluNurbsProperty(flag, GLU_SAMPLING_TOLERANCE, 50.0);
    gluNurbsProperty(flag, GLU_DISPLAY_MODE, GLU_FILL);
    gluNurbsProperty(flag, GLU_CULLING, GL_TRUE);
    
    ResetFootball();

    //Set our initial view vector.
	Camera::GetInstance()->GetView().SetX(Camera::GetInstance()->GetPosition().GetX() + Camera::GetInstance()->GetDirVec().GetX());
	Camera::GetInstance()->GetView().SetY(Camera::GetInstance()->GetPosition().GetY() + Camera::GetInstance()->GetDirVec().GetY());
	Camera::GetInstance()->GetView().SetZ(Camera::GetInstance()->GetPosition().GetZ() + Camera::GetInstance()->GetDirVec().GetZ());

    //Create a display list for the turf.
    turfList = glGenLists(4);
    glNewList(turfList, GL_COMPILE);
        DrawTurf();
        DrawUpRights();
    glEndList();

    //Create a display list for the stadium.
    stadiumList = turfList + 1;
    glNewList(stadiumList, GL_COMPILE);
        SkyBox_Draw(0, 100, 0, 3400, 3400, 3400);
        DrawStadium();
        DrawLights();
    glEndList();

    //Load the g_sFrog helmet model.
	//Frog model courtesy of http://thefree3dmodels.com/stuff/animal/frog/24-1-0-1276
	//Log model courtesy of http://www.turbosquid.com/3d-models/free-3ds-model-log/651693
    helmet.Load("data\\frog\\FROG.3DS");

    //Create a display list for the red helmets.
    redHelmetList = stadiumList + 1;
    glNewList(redHelmetList, GL_COMPILE);
        helmet.rot.x = 90.0f;
        helmet.pos.z = 1.5;
        helmet.pos.y = 1.0;
        helmet.scale = 0.017f;
        helmet.color[0] = 0.6f;
        helmet.DrawHelmet();
    glEndList();

    //Create a display list for the blue helmets.
    blueHelmetList = redHelmetList + 1;
    glNewList(blueHelmetList, GL_COMPILE);
        helmet.color[0] = 0.0f;
        helmet.color[2] = 0.6f;
        helmet.DrawHelmet();
    glEndList();

	/*
    jet1.Load("models\\F15.3DS");   
    jet1.scale = 0.015f;
    jet1.pos.z = -900.0f;
    jet1.pos.y = 600.f;
    jet1.pos.x = 0.0f;
    
    jet2.Load("models\\F15.3DS");   
    jet2.scale = 0.015f;
    jet2.pos.z = -975.0f;
    jet2.pos.y = 550.f;
    jet2.pos.x = 100.0f;

    jet3.Load("models\\F15.3DS");
    jet3.scale = 0.015f;
    jet3.pos.z = -975.0f;
    jet3.pos.y = 550.f;
    jet3.pos.x = -100.0f;
	*/

    if (useMouse)
        glutSetCursor(GLUT_CURSOR_NONE);

    //Kicker.
    players[0].setParams(-1.0f, 1.0f, -195.4f, 0.0f,
                         "stfx", true, false);
    players[0].setRunDirection(0.0f, 0.0f, 0.6f);
    players[0].setStopDistance(103);

    //Defenders.
    //All standing at 25 yard line.
    players[1].setParams(160.0f, 1.0f, -180.0f, 0.0f,
                         "stfx", false, false);
    players[1].setRunDirection(-0.1f, 0.0f, 0.65f);
    players[1].setStopDistance(113);
    ///////////////////////////////////////////////////
    players[2].setParams(130.0f, 1.0f, -180.0f, 0.0f,
                         "stfx", false, false);
    players[2].setRunDirection(-0.13f, 0.0f, 0.65f);
    players[2].setStopDistance(142);
    ///////////////////////////////////////////////////
    players[3].setParams(100.0f, 1.0f, -180.0f, 0.0f,
                         "stfx", false, false);
    players[3].setRunDirection(-0.28f, 0.0f, 0.65f);
    players[3].setStopDistance(112);
    ///////////////////////////////////////////////////
    players[4].setParams(70.0f, 1.0f, -180.0f, 0.0f,
                         "stfx", false, false);
    players[4].setRunDirection(-0.15f, 0.0f, 0.65f);
    players[4].setStopDistance(160);
    ///////////////////////////////////////////////////
    players[5].setParams(40.0f, 1.0f, -180.0f, 0.0f,
                         "stfx", false, false);
    players[5].setRunDirection(-0.09f, 0.0f, 0.65f);
    players[5].setStopDistance(300);
    ///////////////////////////////////////////////////
    players[6].setParams(-40.0f, 1.0f, -180.0f, 0.0f,
                         "stfx", false, false);
    players[6].setRunDirection(-0.09f, 0.0f, 0.65f);
    players[6].setStopDistance(150);
    ///////////////////////////////////////////////////
    players[7].setParams(-70.0f, 1.0f, -180.0f, 0.0f,
                         "stfx", false, false);
    players[7].setRunDirection(-0.09f, 0.0f, 0.65f);
    players[7].setStopDistance(200);
    ///////////////////////////////////////////////////
    players[8].setParams(-100.0f, 1.0f, -180.0f, 0.0f,
                         "stfx", false, false);
    players[8].setRunDirection(-0.09f, 0.0f, 0.65f);
    players[8].setStopDistance(185);
    ///////////////////////////////////////////////////
    players[9].setParams(-130.0f, 1.0f, -180.0f, 0.0f,
                         "stfx", false, false);
    players[9].setRunDirection(-0.11f, 0.0f, 0.7f);
    players[9].setStopDistance(105);
    ///////////////////////////////////////////////////
    players[10].setParams(-160.0f, 1.0f, -180.0f, 0.0f,
                          "stfx", false, false);
    players[10].setRunDirection(0.0f, 0.0f, 1.0f);
    players[10].setStopDistance(300);

    //Offense.
    //Next 5 stand at 45 yard line.
    ///////////////////////////////////////////////////
    players[11].setParams(165.0f, 1.0f, 40.0f, 180.0f,
                          "smu", false, false);
    players[11].setRunDirection(-0.1f, 0.0f, -0.6f);
    players[11].setStopDistance(100);
    ///////////////////////////////////////////////////
    players[12].setParams(75.0f, 1.0f, 40.0f, 180.0f,
                          "smu", false, false);
    players[12].setRunDirection(-0.1f, 0.0f, -0.6f);
    players[12].setStopDistance(100);
    ///////////////////////////////////////////////////
    players[13].setParams(2.5f, 1.0f, 40.0f, 180.0f,
                          "smu", false, false);
    players[13].setRunDirection(0.00f, 0.0f, -0.9f);
    players[13].setStopDistance(100);
    ///////////////////////////////////////////////////
    players[14].setParams(-65.0f, 1.0f, 40.0f, 180.0f,
                          "smu", false, false);
    players[14].setRunDirection(0.04f, 0.0f, -0.24f);
    players[14].setStopDistance(55);
    ///////////////////////////////////////////////////
    players[15].setParams(-155.0f, 1.0f, 40.0f, 180.0f,
                          "smu", false, false);
    players[15].setRunDirection(0.1f, 0.0f, -0.7f);
    players[15].setStopDistance(100);
    //Next 4 stand at 30 yard line.
    ///////////////////////////////////////////////////
    players[16].setParams(135.0f, 1.0f, 125.0f, 180.0f,
                          "smu", false, false);
    players[16].setRunDirection(-0.125f, 0.0f, -0.75f);
    players[16].setStopDistance(155);
    ///////////////////////////////////////////////////
    players[17].setParams(110.0f, 1.0f, 140.0f, 180.0f,
                          "smu", false, false);
    players[17].setRunDirection(-0.3f, 0.0f, -0.6f);
    players[17].setStopDistance(145);
    ///////////////////////////////////////////////////
    players[18].setParams(-95.0f, 1.0f, 140.0f, 180.0f,
                          "smu", false, false);
    players[18].setRunDirection(0.01f, 0.0f, -0.35f);
    players[18].setStopDistance(105);
    ///////////////////////////////////////////////////
    players[19].setParams(-125.0f, 1.0f, 125.0f, 180.0f,
                          "smu", false, false);
    players[19].setRunDirection(0.01f, 0.0f, -0.375f);
    players[19].setStopDistance(105);
    ///////////////////////////////////////////////////
    //This player stands at the 15 yard line.
    players[20].setParams(2.5f, 1.0f, 250.0f, 180.0f,
                          "smu", false, false);
    players[20].setRunDirection(0.0f, 0.0f, -0.25f);
    players[20].setStopDistance(115);
    ///////////////////////////////////////////////////
    //This player stands at the 5 yard line.
    players[21].setParams(2.5f, 1.0f, 315.0f, 180.0f,
                          "smu", false, true);
    players[21].setRunDirection(0.0f, 0.0f, -0.58f);
    players[21].setStopDistance(680);
    ///////////////////////////////////////////////////
}

void processMousePassiveMotion(int x, int y)
{
	/*
    const double MAX_ANGLE = 2.6;

    if (useMouse)
    {
        Coord3 up(0.0, 1.0, 0.0);
        Coord3 cross;
        float dx, dy;

        //Calculate which way we are looking.
		Camera::GetInstance()->GetDirVec().SetX(Camera::GetInstance()->GetView().GetX() - Camera::GetInstance()->GetPosition().GetX());
		Camera::GetInstance()->GetDirVec().SetY(Camera::GetInstance()->GetView().GetX() - Camera::GetInstance()->GetPosition().GetX());
		Camera::GetInstance()->GetDirVec().SetZ(Camera::GetInstance()->GetView().GetX() - Camera::GetInstance()->GetPosition().GetX());

        //Calculate the camera's local x-axis.
		Coord3_crossproduct(Camera::GetInstance()->GetDirVec(), up, &cross);
        Coord3_normalize(&Camera::GetInstance()->GetDirVec());

        dx = (scrWidth / 2 - x);
        dy = (scrHeight / 2 - y);

        //Scale down the sensitivity.
        dx *= SENSITIVITY;
        dy *= SENSITIVITY;

		Camera::GetInstance()->SetCurrentRotation(Camera::GetInstance()->GetCurrentRotation() + dy);

        //Rotate the camera like in quake.
		Coord3_rotateY(&Camera::GetInstance()->GetDirVec(), -dx);

        //Place a cap on the maximum angle.
        if (fabs(Camera::GetInstance()->GetCurrentRotation()) > MAX_ANGLE)
        {
            if (Camera::GetInstance()->GetCurrentRotation() > 0.0)
                Camera::GetInstance()->SetCurrentRotation(MAX_ANGLE);
            else
                Camera::GetInstance()->SetCurrentRotation(-MAX_ANGLE);
        }
        else
			Coord3_rotate(&Camera::GetInstance()->GetDirVec(), cross.GetX(), cross.GetY(), cross.GetZ(), -dy);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    
		Camera::GetInstance()->GetView().SetX(Camera::GetInstance()->GetPosition().GetX() + Camera::GetInstance()->GetDirVec().GetX());
		Camera::GetInstance()->GetView().SetY(Camera::GetInstance()->GetPosition().GetY() + Camera::GetInstance()->GetDirVec().GetY());
		Camera::GetInstance()->GetView().SetZ(Camera::GetInstance()->GetPosition().GetZ() + Camera::GetInstance()->GetDirVec().GetZ());

		gluLookAt(Camera::GetInstance()->GetPosition().GetX(),
			Camera::GetInstance()->GetPosition().GetY(),
			Camera::GetInstance()->GetPosition().GetZ(),
			Camera::GetInstance()->GetView().GetX(), 
			Camera::GetInstance()->GetView().GetY(),
			Camera::GetInstance()->GetView().GetZ(),
                  0.0, 1.0, 0.0);
    }
	*/
}

void Reshape(int w, int h)
{
    GLdouble aspect = (float)w / h;
    scrWidth = w;
    scrHeight = h;

    glViewport(0, 0, scrWidth, scrHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, aspect, 0.1, 3200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt(Camera::GetInstance()->GetPosition().GetX(),
		Camera::GetInstance()->GetPosition().GetY(),
		Camera::GetInstance()->GetPosition().GetZ(),
		Camera::GetInstance()->GetView().GetX(), 
		Camera::GetInstance()->GetView().GetY(),
		Camera::GetInstance()->GetView().GetZ(),
              0.0, 1.0, 0.0);

    windowCenter[0] = glutGet(GLUT_WINDOW_X) + scrWidth / 2;
    windowCenter[1] = glutGet(GLUT_WINDOW_Y) + scrHeight / 2;
}

void KeyUpMap(unsigned char key, int x, int y)
{
	Input::GetInstance()->KeyUpMap(key,x,y);
}
void KeyMap(unsigned char key, int x, int y)
{
	Input::GetInstance()->KeyMap(key,x,y);
}

int main(int argc, char **argv)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Frogger - AdamD");

    init();

    glutDisplayFunc(Display);
	
	glutKeyboardFunc(KeyMap);
    glutKeyboardUpFunc(KeyUpMap);
    glutReshapeFunc(Reshape);
    glutPassiveMotionFunc(processMousePassiveMotion);
    
    if (argc == 2)
        frameRate = 1000.0 / atoi(argv[1]);

    glutTimerFunc(frameRate, Timer, 1);
    glutMainLoop();
}
