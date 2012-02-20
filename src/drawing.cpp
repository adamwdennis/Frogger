//file: drawing.cpp

#include <iostream>
#include <fstream>
#include "glut.h"
#include "GL/GLAux.h"
#include <cmath>
#include "Coord3.h"
#include "Model_3DS.h"
#include "drawing.h"
#include "Player.h"
using namespace std;

extern GLUquadricObj *sphere;
extern GLUquadricObj *cylinder;
extern Frog g_sFrog;
extern GLuint grassTexture;
extern GLuint zeroTexture;
extern GLuint oneTexture;
extern GLuint twoTexture;
extern GLuint threeTexture;
extern GLuint fourTexture;
extern GLuint fiveTexture;
extern GLuint flagTexture;
extern GLuint crowdTexture;
extern GLuint faceTexture;
extern GLuint smuLogo;
extern GLuint stfxLogo;
extern GLuint easterEgg;
extern Model_3DS helmet;
extern int scrWidth;
extern int scrHeight;
extern GLfloat flagPoints[4][4][3];
extern GLUnurbsObj *flag;
extern GLuint redHelmetList;
extern GLuint blueHelmetList;
extern Player players[22];
GLuint TexIDSkyBox[6] = { -1 };

void loadTexture(char *texture, GLuint &texId, GLint minFilter, GLint magFilter);

static void DrawArms(const Player &player)
{
    static float normal[] = { 1.0, 0.0, 0.0 };
    const double radius = 0.5;
    float color[3];

    if (player.getTeam() == "smu")
    {
        color[0] = 1.0f;
        color[1] = 0.0f;
        color[2] = 0.0f;
    }
    else
    {
        color[0] = 0.0f;
        color[1] = 0.0f;
        color[2] = 1.0f;
    }

    glColor3fv(color);
    glPushMatrix();
        //Left arm.
        glPushMatrix();
            //Shoulder.
            glTranslatef(0.25f, 4.5f, 1.0f);            
            gluSphere(sphere, 0.75f, 6, 6);

            glRotatef(player.getLeftArmRoll(), 0.0, 1.0, 0.0);
            glRotatef(player.getLeftArmPitch(), 1.0, 0.0, 0.0);

            //Arm.
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(cylinder, 0.75f, 0.9f, 2.0f, 10, 4);
            
            //Elbow.
            glTranslatef(0.0f, 0.0f, 2.0f);
            gluSphere(sphere, 0.9f, 6, 6);

            //Forearm.
            glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(cylinder, 0.9f, 0.4f, 2.0f, 10, 4);
        
            //Hand.
            glTranslatef(0.0f, 0.5f, 2.65f);
            glPushMatrix();
                glColor3f(1.0f, 1.0f, 0.0f);
                glPushMatrix();
                    glTranslatef(0.0f, -0.4f, -0.70f);
                    gluCylinder(cylinder, 0.1f, 0.1f, 0.2f, 6, 1);
                glPopMatrix();

                glDisable(GL_CULL_FACE);
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                glBegin(GL_QUAD_STRIP);
                for (double theta = 36.0; theta >-234.0; theta -= 36.0)
                {
                    float c = cos(theta * M_PI / 180);
                    float s = sin(theta * M_PI / 180);

                    glNormal3f(c * normal[0] - s * normal[0],
                               s * normal[1] + c * normal[1],
                               0.0);

                    glVertex3f(radius * c, radius * s, 0.75f);
                    glVertex3f(radius * c, radius * s, 0.0f);
                }
                glEnd();
                glEnable(GL_CULL_FACE);
            glPopMatrix();
        glPopMatrix();

        //Right arm.
        glPushMatrix();
        glColor3fv(color);
            //Shoulder.
            glTranslatef(4.75f, 4.5f, 1.0f);            
            gluSphere(sphere, 0.75f, 6, 6);
            
            glRotatef(player.getRightArmRoll(), 0.0, 1.0, 0.0);
            glRotatef(player.getRightArmPitch(), 1.0f, 0.0f, 0.0f);

            //Arm.
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(cylinder, 0.75f, 0.9f, 2.0f, 10, 4);

            //Elbow.
            glTranslatef(0.0f, 0.0f, 2.0f);
            gluSphere(sphere, 0.9f, 6, 6);

            //Forearm.
            glRotatef(-60.0f , 1.0f, 0.0f, 0.0f);
            gluCylinder(cylinder, 0.9f, 0.4f, 2.0f, 10, 4);

            //Hand.
            glTranslatef(0.0f, 0.5f, 2.65f);
            glPushMatrix();
                glColor3f(1.0f, 1.0f, 0.0f);
                glPushMatrix();
                    glTranslatef(0.0f, -0.4f, -0.70f);
                    gluCylinder(cylinder, 0.1f, 0.1f, 0.2f, 6, 1);
                glPopMatrix();

                glDisable(GL_CULL_FACE);
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                glBegin(GL_QUAD_STRIP);
                for (double theta = 36.0; theta >-234.0; theta -= 36.0)
                {
                    float c = cos(theta * M_PI / 180);
                    float s = sin(theta * M_PI / 180);

                    glNormal3f(c * normal[0] - s * normal[0],
                               s * normal[1] + c * normal[1],
                               0.0);

                    glVertex3f(radius * c, radius * s, 0.75f);
                    glVertex3f(radius * c, radius * s, 0.0f);
                }
                glEnd();
                glEnable(GL_CULL_FACE);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

static void DrawLegs(const Player &player)
{
    static GLfloat LEG_SPACING = 0.4f;
    static GLfloat LEG_WIDTH = 2.3f;
    static GLfloat LEG_HEIGHT = 4.25f;
    float color[3];

    if (player.getTeam() == "smu")
    {
        color[0] = 1.0f;
        color[1] = 0.0f;
        color[2] = 0.0f;
    }
    else
    {
        color[0] = 0.0f;
        color[1] = 0.0f;
        color[2] = 1.0f;
    }

    glTranslatef(0.0f, -0.75f, 0.0f);
    //Left leg.
    glPushMatrix();
        glTranslatef(1.0f, 0.0f, 1.0f);
        glRotatef(player.getLeftLegRoll(), 0.0f, 1.0f, 0.0f);
        glTranslatef(-1.0f, 0.0f, -1.0f);
        //Hip.
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 1.0f);
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            glColor3fv(color);
            gluCylinder(cylinder, 0.9f, 0.9f, LEG_WIDTH, 10, 2);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glBegin(GL_POLYGON);
                for(double theta = 378.0; theta > 18.0; theta -= 36.0)
                    glVertex3f(0.9f * cos(theta * M_PI / 180), 
                               0.9f * sin(theta * M_PI / 180),
                               0.0f);
            glEnd();            
        glPopMatrix();

        //Leg.
        glTranslatef(0.0f, 0.0f, 0.825f);
        glRotatef(player.getLeftLegPitch(), 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, -0.825f);

        glTranslatef(0.001f, -LEG_HEIGHT, 1.75f);
        DrawUnit(LEG_WIDTH, LEG_HEIGHT, 1.65f);

        //Foot.
        glColor3f(1.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, -1.0f, 0.6f);
        DrawUnit(LEG_WIDTH, 1.0f, 2.25f);
    glPopMatrix();

    //Right leg.
    glPushMatrix();     
        glTranslatef(LEG_WIDTH + LEG_SPACING, 0.0f, 0.0f);
        glTranslatef(1.0f, 0.0f, 1.0f);
        glRotatef(player.getRightLegRoll(), 0.0f, 1.0f, 0.0f);
        glTranslatef(-1.0f, 0.0f, -1.0f);
        //Hip.
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 1.0f);
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            glColor3fv(color);
            gluCylinder(cylinder, 0.9f, 0.9f, LEG_WIDTH, 10, 2);
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, LEG_WIDTH);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glBegin(GL_POLYGON);
                for (double theta = 18.0; theta < 378.0; theta += 36.0)
                    glVertex3f(0.9f * cos(theta * M_PI / 180), 
                               0.9f * sin(theta * M_PI / 180),
                               0.0f);
            glEnd();
            glPopMatrix();
        glPopMatrix();

        //Leg.
        glTranslatef(0.0f, 0.0f, 0.825f);
        glRotatef(player.getRightLegPitch(), 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, -0.825f);

        glTranslatef(-0.001f, -LEG_HEIGHT, 1.75f);
        DrawUnit(LEG_WIDTH, LEG_HEIGHT, 1.65f);

        //Foot.
        glColor3f(1.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, -1.0f, 0.6f);
        DrawUnit(LEG_WIDTH, 1.0f, 2.25f);
    glPopMatrix();
}

static void DrawHead(const Player &player)
{
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 5.0f, 1.0f);
    glRotatef(player.getHeadPitch(), 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -5.0f, -1.0f);

    glTranslatef(2.5f, 5.0f, 1.0f);
    glPushMatrix();
    glRotatef(-90.0, 1.0f, 0.0f, 0.0f);

    //Draw neck.
    gluCylinder(cylinder, 1.1f, 1.1f, 0.75f, 10, 1);

    //Draw face.
    glTranslatef(0.0f, 0.0f, 0.75f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, faceTexture);
    gluCylinder(cylinder, 1.8f, 1.8f, 3.0f, 10, 2);
    glDisable(GL_TEXTURE_2D);

    //Draw hair?
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 3.0f);
        gluCylinder(cylinder, 0.75f, 0.75f, 0.5f, 10, 1);
    glPopMatrix();
    
    glNormal3f(0.0f, 0.0f, -1.0f);
    glBegin(GL_POLYGON);
        for (double theta = 378.0; theta > 18.0; theta -= 36.0)
            glVertex3f(1.8f * cos(theta * M_PI / 180),
                       1.8f * sin(theta * M_PI / 180),
                       0.0f);

    glEnd();

    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
        for (double theta = 18.0; theta < 378.0; theta += 36.0)
            glVertex3f(1.8f * cos(theta * M_PI / 180),
                       1.8f * sin(theta * M_PI / 180),
                       3.0f);
    glEnd();

    //Top of hair.
    glBegin(GL_POLYGON);
        for (double theta = 18.0; theta < 378.0; theta += 36.0)
            glVertex3f(0.75f * cos(theta * M_PI / 180),
                       0.75f * sin(theta * M_PI / 180),
                       3.5f);
    glEnd();

    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);

    if (player.getTeam() == "smu")
        glCallList(redHelmetList);
    else
    {
        if (player.isTackled())
            glTranslatef(0.0f, -1.75f, 0.0f);
        glCallList(blueHelmetList);
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);

    glPopMatrix();
    glPopMatrix();
}

static void DrawBody(const Player &player)
{
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 2.0f);
    DrawUnit(5.0f, 0.4f, 2.0f);
    glPopMatrix();

    glTranslatef(0.0f, 0.4f, 0.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);
    if (player.getTeam() == "smu")
        glBindTexture(GL_TEXTURE_2D, smuLogo);
    else
        glBindTexture(GL_TEXTURE_2D, stfxLogo);
    glBegin(GL_QUADS);
        //Front.
        //Bottom left.
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 2.0f);
        //Bottom right.
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(5.0f, 0.0f, 2.0f);
        //Top right.
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(4.5f, 5.0f, 2.0f);
        //Top left.
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.5f, 5.0f, 2.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    //Back.
    glNormal3f(0.0f, 0.0f, -1.0f);
    glBegin(GL_QUADS);
        //Top left
        glVertex3f(0.5f, 5.0f, 0.0f);
        //Top right.
        glVertex3f(4.5f, 5.0f, 0.0f);
        //Bottom right.
        glVertex3f(5.0f, 0.0f, 0.0f);
        //Bottom left.
        glVertex3f(0.0f, 0.0f, 0.0f);

        //Top.
        //Back left.
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.5f, 5.0f, 2.0f);
        //Back right.
        glVertex3f(4.5f, 5.0f, 2.0f);
        //Front right.
        glVertex3f(4.5f, 5.0f, 0.0f);
        //Front left.
        glVertex3f(0.5f, 5.0f, 0.0f);

        //Bottom.
        //Front left.
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        //Front right.
        glVertex3f(5.0f, 0.0f, 0.0f);
        //Back right.
        glVertex3f(5.0f, 0.0f, 2.0f);
        //Back left.
        glVertex3f(0.0f, 0.0f, 2.0f);

        //Left.
        //Top left.
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(0.5f, 5.0f, 2.0f);
        //Top right.
        glVertex3f(0.5f, 5.0f, 0.0f);
        //Bottom right.
        glVertex3f(0.0f, 0.0f, 0.0f);
        //Bottom left.
        glVertex3f(0.0f, 0.0f, 2.0f);

        //Right.
        glNormal3f(1.0f, 0.0f, 0.0f);
        //Top left.
        glVertex3f(4.5f, 5.0f, 0.0f);
        //Top right.
        glVertex3f(4.5f, 5.0f, 2.0f);
        //Bottom right.
        glVertex3f(5.0f, 0.0f, 2.0f);
        //Bottom left.
        glVertex3f(5.0f, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();
}

static void DrawPlayer(Player &player)
{
    float pos[3];

    glPushMatrix();
    player.getPosition(pos);
    //Move the player.
    glTranslatef(pos[0], pos[1], pos[2]);
    //Make the player face a certain direction.
    glRotatef(player.getDirection(), 0.0f, 1.0f, 0.0f);
    

    player.run();
    player.hold();
    player.catchBall();
    player.runForTouchDown();
    player.getTackled();

    glPushMatrix();
    //Make the player lean backward/forward.
    glTranslatef(0.0f, 0.0f, 1.6f);
    glRotatef(player.getTorsoPitch(), 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -1.6f);
    DrawBody(player);
    DrawHead(player);
    DrawArms(player);
    
    glPopMatrix();

    DrawLegs(player);
    glPopMatrix();
}

void DrawTeam()
{
    for (int i = 0; i < 22; i++)
        DrawPlayer(players[i]);
}

void DrawStadium()
{
    //Draw endzone markers.
    glPushMatrix();
        glTranslatef(188.0f, -4.9f, 388.8f);
        DrawMarkers();
        glTranslatef(0.0f, 0.0f, -738.8f);
        DrawMarkers();
    glPopMatrix();

    //Bottom Crowd.
    GLfloat bcLength = 105.0f;
    GLfloat bcHeight = 50.0f;
    GLfloat bcWidth = 160.0f;

    //Top Crowd.
    GLfloat mcLength = 105.0f;
    GLfloat mcHeight = 100.0f;
    GLfloat mcWidth = 160.0f;

    GLfloat tcLength = 105.0f;
    GLfloat tcHeight = 120.0f;
    GLfloat tcWidth = 160.0f;


    //Draw bottom right crowds.
    glPushMatrix();
        glTranslatef(230.0f, 0.0f, -420.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(bcLength, 0.0f, -0.1f);
                glVertex3f(-945.0f, 0.0f, -0.1f);
                glVertex3f(-945.0f, 6.0f, -0.1f);
                glVertex3f(bcLength, 6.0f, -0.1f);
            glEnd();
        glPopMatrix();

        glTranslatef(bcLength, 0.0f, 2.0f);
        for(int i = 0; i < 10; i++)
        {
            DrawSeat(bcLength, bcLength, bcHeight, bcWidth);
            glTranslatef(-bcLength, 0.0f, 0.0f);
        }
    glPopMatrix();

    //Draw bottom left crowds.
    glPushMatrix();
        glTranslatef(-230.0f, 0.0f, 420.0f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(bcLength, 0.0f, -0.1f);
                glVertex3f(-945.0f, 0.0f, -0.1f);
                glVertex3f(-945.0f, 6.0f, -0.1f);
                glVertex3f(bcLength, 6.0f, -0.1f);
            glEnd();
        glPopMatrix();
        
        glTranslatef(bcLength, 0.0f, 2.0f);
        for(int i = 0; i < 10; i++)
        {
            DrawSeat(bcLength, bcLength, bcHeight, bcWidth);
            glTranslatef(-105.0f, 0.0f, 0.0f);
        }
    glPopMatrix();

    //Draw bottom front crowds.
    glPushMatrix();
        glTranslatef(-230.0f, 0.0f, -525.0f);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 6.0f, 0.0f);
                glVertex3f(0.0f, 6.0f, 0.0f);
            glEnd();
        glPopMatrix();

        for(int i = 0; i < 4; i++)
        {
            DrawSeat(bcLength+10, bcLength+10, bcHeight, bcWidth);
            glTranslatef(-bcLength-10, 0.0f, 0.0f);
        }
    glPopMatrix();
        
    //Draw bottom back crowds.
    glPushMatrix();
        glTranslatef(230.0f, 0.0f, 525.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 6.0f, 0.0f);
                glVertex3f(0.0f, 6.0f, 0.0f);
            glEnd();
        glPopMatrix();

        for(int i = 0; i < 4; i++)
        {
            DrawSeat(bcLength+10, bcLength+10, bcHeight, bcWidth);
            glTranslatef(-bcLength-10, 0.0f, 0.0f);
        }
    glPopMatrix();
    

    //Draw middle right crowds.
    glPushMatrix(); 
        glTranslatef(350.0f, 40.0f, -420.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(mcLength, 0.0f, 0.0f);
                glVertex3f(-945.0f, 0.0f, 0.0f);
                glVertex3f(-945.0f, 6.0f, 0.0f);
                glVertex3f(mcLength, 6.0f, 0.0f);
            glEnd();
        glPopMatrix();

        glTranslatef(bcLength, 0.0f, 0.0f);
        for(int i = 0; i < 10; i++)
        {
            DrawSeat(mcLength, mcLength, mcHeight, mcWidth);
            glTranslatef(-mcLength, 0.0f, 0.0f);
        }
    glPopMatrix();

    //Draw middle left crowds.
    glPushMatrix();
        glTranslatef(-350.0f, 40.0f, 420.0f);
        glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(mcLength, 0.0f, 0.0f);
                glVertex3f(-945.0f, 0.0f, 0.0f);
                glVertex3f(-945.0f, 6.0f, 0.0f);
                glVertex3f(mcLength, 6.0f, 0.0f);
            glEnd();
        glPopMatrix();

        glTranslatef(bcLength, 0.0f, 0.0f);
        for(int i = 0; i < 10; i++)
        {
            DrawSeat(mcLength, mcLength, mcHeight, mcWidth);
            glTranslatef(-mcLength, 0.0f, 0.0f);
        }
    glPopMatrix();
    //Draw middle front crowds.
    glPushMatrix();
        glTranslatef(-230.0f, 40.0f, -635.0f);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 6.0f, 0.0f);
                glVertex3f(0.0f, 6.0f, 0.0f);
            glEnd();
        glPopMatrix();

        for(int i = 0; i < 4; i++)
        {
            DrawSeat(mcLength+10, mcLength+10, mcHeight, mcWidth);
            glTranslatef(-mcLength-10, 0.0f, 0.0f);
        }
    glPopMatrix();

    

    //Draw middle back crowds.
    glPushMatrix();
        glTranslatef(230.0f, 40.0f, 635.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 6.0f, 0.0f);
                glVertex3f(0.0f, 6.0f, 0.0f);
            glEnd();
        glPopMatrix();

        for(int i = 0; i < 4; i++)
        {
            DrawSeat(mcLength+10, mcLength+10, mcHeight, mcWidth);
            glTranslatef(-mcLength-10, 0.0f, 0.0f);
        }
    glPopMatrix();

    //Draw middle back corner right crowds.
    glPushMatrix();
        glTranslatef(418.0f, 0.0f, 278.0f);
        glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 6.0f, 0.0f);
                glVertex3f(0.0f, 6.0f, 0.0f);
            glEnd();
        glPopMatrix();

        for(int i = 0; i < 4; i++)
        {
            DrawSeat(bcLength+50, bcLength+50, bcHeight+mcHeight+tcHeight-20, 2*bcWidth+50);
            glTranslatef(-bcLength-50, 0.0f, 0.0f);
        }
    glPopMatrix();

    //Draw middle back corner left crowds.
    glPushMatrix();
        glTranslatef(30.0f, 0.0f, 720.0f);
        glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 6.0f, 0.0f);
                glVertex3f(0.0f, 6.0f, 0.0f);
            glEnd();
        glPopMatrix();

        for(int i = 0; i < 4; i++)
        {
            DrawSeat(bcLength+50, bcLength+50, bcHeight+mcHeight+tcHeight-20, 2*bcWidth+50);
            glTranslatef(-bcLength-50, 0.0f, 0.0f);
        }
    glPopMatrix();

    //Draw middle front corner right crowds.
    glPushMatrix();
        glTranslatef(-30.0f, 0.0f, -720.0f);
        glRotatef(135.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 6.0f, 0.0f);
                glVertex3f(0.0f, 6.0f, 0.0f);
            glEnd();
        glPopMatrix();

        for(int i = 0; i < 4; i++)
        {
            DrawSeat(bcLength+50, bcLength+50, bcHeight+mcHeight+tcHeight-20, 2*bcWidth+50);
            glTranslatef(-bcLength-50, 0.0f, 0.0f);
        }
    glPopMatrix();

    //Draw middle front corner left crowds.
    glPushMatrix();
        glTranslatef(-(418.0f), 0.0f, -278.0f);
        glRotatef(225.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 6.0f, 0.0f);
                glVertex3f(0.0f, 6.0f, 0.0f);
            glEnd();
        glPopMatrix();

        for(int i = 0; i < 4; i++)
        {
            DrawSeat(bcLength+50, bcLength+50, bcHeight+mcHeight+tcHeight-20, 2*bcWidth+50);
            glTranslatef(-bcLength-50, 0.0f, 0.0f);
        }
    glPopMatrix();


    //Draw top right crowds.
    glPushMatrix();
        glTranslatef((280 + bcLength + mcLength), (bcHeight+mcHeight-10), -420.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(tcLength, 0.0f, -0.1f);
                glVertex3f(-945.0f, 0.0f, -0.1f);
                glVertex3f(-945.0f, 6.0f, -0.1f);
                glVertex3f(tcLength, 6.0f, -0.1f);
            glEnd();
        glPopMatrix();

        glTranslatef(bcLength, 0.0f, 2.0f);
        for(int i = 0; i < 10; i++)
        {
            DrawSeat(tcLength, tcLength, tcHeight, tcWidth);
            glTranslatef(-tcLength, 0.0f, 0.0f);
        }
    glPopMatrix();

    //Draw top left crowds.
    glPushMatrix();
        glTranslatef(-(280 + bcLength + mcLength), (bcHeight+mcHeight-10), 420.0f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(tcLength, 0.0f, -0.1f);
                glVertex3f(-945.0f, 0.0f, -0.1f);
                glVertex3f(-945.0f, 6.0f, -0.1f);
                glVertex3f(tcLength, 6.0f, -0.1f);
            glEnd();
        glPopMatrix();
        
        glTranslatef(tcLength, 0.0f, 2.0f);
        for(int i = 0; i < 10; i++)
        {
            DrawSeat(tcLength, tcLength, tcHeight, tcWidth);
            glTranslatef(-105.0f, 0.0f, 0.0f);
        }
    glPopMatrix();

    //Draw top front crowds.
    glPushMatrix();
        glTranslatef(-230.0f, (bcHeight+mcHeight-10), -(465.0f+bcWidth+mcWidth));
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 6.0f, 0.0f);
                glVertex3f(0.0f, 6.0f, 0.0f);
            glEnd();
        glPopMatrix();

        for(int i = 0; i < 4; i++)
        {
            DrawSeat(tcLength+10, tcLength+10, tcHeight, tcWidth);
            glTranslatef(-tcLength-10, 0.0f, 0.0f);
        }
    glPopMatrix();
        
    //Draw top back crowds.
    glPushMatrix();
        glTranslatef(230.0f, (bcHeight+mcHeight-10), (465.0f+bcWidth+mcWidth));
        glPushMatrix();
            glColor3f(0.65f, 0.65f, 0.65f);
            glTranslatef(0.0f, -5.0f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 0.0f, 0.0f);
                glVertex3f(-460.0f, 6.0f, 0.0f);
                glVertex3f(0.0f, 6.0f, 0.0f);
            glEnd();
        glPopMatrix();

        for(int i = 0; i < 4; i++)
        {
            DrawSeat(tcLength+10, tcLength+10, tcHeight, tcWidth);
            glTranslatef(-tcLength-10, 0.0f, 0.0f);
        }
    glPopMatrix();

	//Draw bottom front easter egg.
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -750.0f);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        //glPushMatrix();
            //glColor3f(0.65f, 0.65f, 0.65f);
			//glRotatef(180.0f, 0.0f,1.0f,0.0f);
            //glTranslatef(0.0f, -5.0f, 0.0f);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, easterEgg);
            glBegin(GL_QUADS);
				glTexCoord2f(1.0f, 1.0f);
                glVertex3f(0.0f, 50.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f);
                glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f);
                glVertex3f(50.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0f, 1.0f);
                glVertex3f(50.0f, 50.0f, 0.0f);
            glEnd();
			glDisable(GL_TEXTURE_2D);
        //glPopMatrix();
        
    glPopMatrix();
}

static void DrawSeat(float bottomLength, float topLength,
                     float height, float width)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, crowdTexture);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0.0f, 2.0f);
        glVertex3f(0.0f, height - 0.1f, width);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.0f, -0.1f, 0.0f);
        glTexCoord2f(2.0f, 2.0f);
        glVertex3f(-topLength, height - 0.1f, width);
        glTexCoord2f(2.0f, 0.0f);
        glVertex3f(-bottomLength, -0.1f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void DrawUpRights()
{
    // |
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(1.0f, -5.0f, -393.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(cylinder, 1.0f, 1.0f, 20.0f, 10, 5);
    glPopMatrix();

    //___
    // |
    glPushMatrix();
        glColor3f(0.9f,0.9f,0.0f);
        glTranslatef(16.0f, 15.0f, -393.0f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(cylinder, 1.0f, 1.0f, 30.0f, 10, 5);
    glPopMatrix();

    //___|
    // |
    glPushMatrix();
        glTranslatef(15.0f, 14.0f, -393.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(cylinder, 1.0f, 1.0f, 50.0f, 10, 5);
    glPopMatrix();

    //|___|
    //  |
    glPushMatrix();
        glTranslatef(-13.0f, 14.0f, -393.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(cylinder, 1.0f, 1.0f, 50.0f, 10, 5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-13.0f, 64.0f, -393.0f);
        glBegin(GL_POLYGON);
            for (double theta = 360.0; theta > 0.0; theta -= 36.0)
                glVertex3f(cos(theta * M_PI / 180), 0.0f,
                           sin(theta * M_PI / 180));
        glEnd();
        glTranslatef(28.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
            for (double theta = 360.0; theta > 0.0; theta -= 36.0)
                glVertex3f(cos(theta * M_PI / 180), 0.0f,
                           sin(theta * M_PI / 180));
        glEnd();
    glPopMatrix();

    // |
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(1.0f, -5.0f, 391.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(cylinder, 1.0f, 1.0f, 20.0f, 10, 5);
    glPopMatrix();

    //___
    // |
    glPushMatrix();
        glColor3f(0.9f,0.9f,0.0f);
        glTranslatef(16.0f, 15.0f, 391.0f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(cylinder, 1.0f, 1.0f, 30.0f, 10, 5);
    glPopMatrix();

    //___|
    // |
    glPushMatrix();
        glTranslatef(15.0f, 14.0f, 391.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(cylinder, 1.0f, 1.0f, 50.0f, 10, 5);
    glPopMatrix();

    //|___|
    //  |
    glPushMatrix();
        glTranslatef(-13.0f, 14.0f, 391.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(cylinder, 1.0f, 1.0f, 50.0f, 10, 5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-13.0f, 64.0f, 391.0f);
        glBegin(GL_POLYGON);
            for (double theta = 360.0; theta > 0.0; theta -= 36.0)
                glVertex3f(cos(theta * M_PI / 180), 0.0f,
                           sin(theta * M_PI / 180));
        glEnd();
        glTranslatef(28.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
            for (double theta = 360.0; theta > 0.0; theta -= 36.0)
                glVertex3f(cos(theta * M_PI / 180), 0.0f,
                           sin(theta * M_PI / 180));
        glEnd();
    glPopMatrix();
}

static void DrawMarkers()
{
    //Draw 4 orange endzone markers.
    glPushMatrix();
        glColor3f(1.0f, 0.4f, 0.0f);
        DrawUnit(0.8f, 5.0f, 0.8f);
        glTranslatef(0.0f, 0.0f, -40.0f);
        DrawUnit(0.8f, 5.0f, 0.8f);
        glTranslatef(-376.8f, 0.0f, 0.0f);
        DrawUnit(0.8f, 5.0f, 0.8f);
        glTranslatef(0.0f, 0.0f, 40.0f);
        DrawUnit(0.8f, 5.0f, 0.8f);
    glPopMatrix();
}

void DrawLights()
{
    glPushMatrix();
    glTranslatef(657.0f, 250.0f, -87.5f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 40.0f, 0.2f);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    //Ugly hack to make the lights brighter.
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
        glVertex3f(-30.0f, 30.0f, 0.0f);
        glVertex3f(-30.0f, 0.0f, 0.0f);
        glVertex3f(30.0f, 0.0f, 0.0f);
        glVertex3f(30.0f, 30.0f, 0.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    glTranslatef(0.0f, -40.0f, -1.0f);
    glColor3f(0.65f, 0.65f, 0.65f);
    DrawUnit(2.0f, 40.0f, 2.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-657.0f, 250.0f, -262.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 40.0f, 0.2f);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glVertex3f(-30.0f, 30.0f, 0.0f);
    glVertex3f(-30.0f, 0.0f, 0.0f);
    glVertex3f(30.0f, 0.0f, 0.0f);
    glVertex3f(30.0f, 30.0f, 0.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    glTranslatef(0.0f, -40.0f, -1.0f);
    glColor3f(0.65f, 0.65f, 0.65f);
    DrawUnit(2.0f, 40.0f, 2.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(657.0f, 250.0f, 262.0f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 40.0f, 0.2f);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glVertex3f(-30.0f, 30.0f, 0.0f);
    glVertex3f(-30.0f, 0.0f, 0.0f);
    glVertex3f(30.0f, 0.0f, 0.0f);
    glVertex3f(30.0f, 30.0f, 0.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    glTranslatef(0.0f, -40.0f, -1.0f);
    glColor3f(0.65f, 0.65f, 0.65f);
    DrawUnit(2.0f, 40.0f, 2.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-657.0f, 250.0f, 87.5f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 40.0f, 0.2f);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glVertex3f(-30.0f, 30.0f, 0.0f);
    glVertex3f(-30.0f, 0.0f, 0.0f);
    glVertex3f(30.0f, 0.0f, 0.0f);
    glVertex3f(30.0f, 30.0f, 0.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    glTranslatef(0.0f, -40.0f, -1.0f);
    glColor3f(0.65f, 0.65f, 0.65f);
    DrawUnit(2.0f, 40.0f, 2.0f);
    glPopMatrix();
}

void DrawFlag()
{
    static double time = 0.0;
    static GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};
    double s = sin(time), c = cos(time);

    //Draw the flag pole.
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-657.0f, 250.0f, 0.0f);

        glBegin(GL_POLYGON);
            for (double theta = 360.0; theta > 0.0; theta -= 36.0)
                glVertex3f(cos(theta * M_PI / 180), 69.9f,
                           sin(theta * M_PI / 180));
        glEnd();

        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(cylinder, 1.0f, 1.0f, 70.0f, 10, 10);
    glPopMatrix();

    //Draw the flag.
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, flagTexture);

    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-640.0f, 302.0f, -21.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glScalef (5.5f, 6.8f, 5.5f);

        //Animate the flag.
        flagPoints[1][2][2] += (0.2 * c);
        flagPoints[0][0][2] += (0.2 * c);
        flagPoints[0][1][2] += (0.2 * s);
        flagPoints[0][2][2] += (0.2 * c);
        flagPoints[3][0][2] += (0.2 * s);
        flagPoints[3][1][2] += (0.2 * c);
        flagPoints[3][2][2] += (0.2 * s);

        time += 0.1;

        gluBeginSurface(flag);
        //Generate the vertices.
        gluNurbsSurface(flag, 8, knots, 8, knots,
                        4 * 3, 3, &flagPoints[0][0][0], 4, 4,
                        GL_MAP2_VERTEX_3);

        //Generate texture coordinates.
        gluNurbsSurface(flag, 8, knots, 8, knots,
                        4 * 3, 3, &flagPoints[0][0][0], 4, 4,
                        GL_MAP2_TEXTURE_COORD_2);

        gluEndSurface(flag);

    glPopMatrix();

    glEnable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
}

void DrawUnit(float scaleX, float scaleY, float scaleZ)
{
    glBegin(GL_TRIANGLE_STRIP);

    //Calling glScalef will force us to renormalize the normal
    //so try to avoid calling it.
    //Front face.
    glNormal3f(0.0f, 0.0f, 1.0f); //Normal facing forward.

    //Bottom right.
    glTexCoord2f(1.0f, 0.0f); glVertex3f(scaleX * 1.0f,
                                         scaleY * 0.0f,
                                         scaleZ * 0.0f);
    //Top right.
    glTexCoord2f(1.0f, 1.0f); glVertex3f(scaleX * 1.0f,
                                         scaleY * 1.0f,
                                         scaleZ * 0.0f);
    //Bottom left.
    glTexCoord2f(0.0f, 0.0f); glVertex3f(scaleX * 0.0f,
                                         scaleY * 0.0f,
                                         scaleZ * 0.0f);
    //Top left.
    glTexCoord2f(0.0f, 1.0f); glVertex3f(scaleX * 0.0f,
                                         scaleY * 1.0f,
                                         scaleZ * 0.0f);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    //Back face.
    glNormal3f(0.0f, 0.0f, -1.0f); //Normal facing away.

    //Bottom right.
    glTexCoord2f(1.0f, 0.0f); glVertex3f(scaleX * 0.0f,
                                         scaleY * 0.0f,
                                         scaleZ * -1.0f);
    //Top right.
    glTexCoord2f(1.0f, 1.0f); glVertex3f(scaleX * 0.0f,
                                         scaleY * 1.0f,
                                         scaleZ * -1.0f);
    //Bottom left.
    glTexCoord2f(0.0f, 0.0f); glVertex3f(scaleX * 1.0f,
                                         scaleY * 0.0f,
                                         scaleZ * -1.0f);
    //Top left.
    glTexCoord2f(0.0f, 1.0f); glVertex3f(scaleX * 1.0f,
                                         scaleY * 1.0f,
                                         scaleZ * -1.0f);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    //Top face.
    glNormal3f(0.0f, 1.0f, 0.0f); //Normal facing up.

    //Bottom right.
    glTexCoord2f(1.0f, 0.0f); glVertex3f(scaleX * 1.0f,
                                         scaleY * 1.0f,
                                         scaleZ * 0.0f);
    //Top right.
    glTexCoord2f(1.0f, 1.0f); glVertex3f(scaleX * 1.0f,
                                         scaleY * 1.0f,
                                         scaleZ * -1.0f);
    //Bottom left.
    glTexCoord2f(0.0f, 0.0f); glVertex3f(scaleX * 0.0f,
                                         scaleY * 1.0f,
                                         scaleZ * 0.0f);
    //Top left.
    glTexCoord2f(0.0f, 1.0f); glVertex3f(scaleX * 0.0f, 
                                         scaleY * 1.0f,
                                         scaleZ * -1.0f);
    glEnd();

    
    glBegin(GL_TRIANGLE_STRIP);
    //Bottom face.
    glNormal3f(0.0f, -1.0f, 0.0f); //Normal facing down.
    //Bottom right.
    glTexCoord2f(1.0f, 0.0f); glVertex3f(scaleX * 0.0f,
                                         scaleY * 0.0f,
                                         scaleZ *  0.0f);
    //Top right.
    glTexCoord2f(1.0f, 1.0f); glVertex3f(scaleX * 0.0f,
                                         scaleY * 0.0f,
                                         scaleZ * -1.0f);
    //Bottom left.
    glTexCoord2f(0.0f, 0.0f); glVertex3f(scaleX * 1.0f,
                                         scaleY * 0.0f,
                                         scaleZ * 0.0f);
    //Top left.
    glTexCoord2f(0.0f, 1.0f); glVertex3f(scaleX * 1.0f,
                                         scaleY * 0.0f,
                                         scaleZ * -1.0f);
    glEnd();

    
    glBegin(GL_TRIANGLE_STRIP);
    //Right face.
    glNormal3f(1.0f, 0.0f, 0.0f); //Normal facing right.
    //Bottom right.
    glTexCoord2f(1.0f, 0.0f); glVertex3f(scaleX * 1.0f,
                                         scaleY * 0.0f,
                                         scaleZ * -1.0f);
    //Top right.
    glTexCoord2f(1.0f, 1.0f); glVertex3f(scaleX * 1.0f,
                                         scaleY * 1.0f,
                                         scaleZ * -1.0f);
    //Bottom left.
    glTexCoord2f(0.0f, 0.0f); glVertex3f(scaleX * 1.0f,
                                         scaleY * 0.0f,
                                         scaleZ * 0.0f);
    //Top left.
    glTexCoord2f(0.0f, 1.0f); glVertex3f(scaleX * 1.0f,
                                         scaleY * 1.0f,
                                         scaleZ * 0.0f);
    glEnd();

    
    glBegin(GL_TRIANGLE_STRIP);
    //Left face.
    glNormal3f(-1.0f, 0.0f, 0.0f); //Normal facing left.
    //Top Left.
    glTexCoord2f(0.0f, 1.0f); glVertex3f(scaleX * 0.0f,
                                         scaleY * 1.0f,
                                         scaleZ * -1.0f);
    //Bottom left.
    glTexCoord2f(0.0f, 0.0f); glVertex3f(scaleX * 0.0f,
                                         scaleY * 0.0f,
                                         scaleZ * -1.0f);
    //Top right.
    glTexCoord2f(1.0f, 1.0f); glVertex3f(scaleX * 0.0f,
                                         scaleY * 1.0f,
                                         scaleZ * 0.0f);
    //Bottom right.
    glTexCoord2f(1.0f, 0.0f); glVertex3f(scaleX * 0.0f,
                                         scaleY * 0.0f,
                                         scaleZ * 0.0f);
    glEnd();
}

void DrawFootball()
{
    glPushMatrix();

    glColor3f(139.0f / 255.0f, 69.0f / 255.0f, 19.0f / 255.0f);
    glTranslatef(g_sFrog.position.GetX(),
                 g_sFrog.position.GetY(),
                 g_sFrog.position.GetZ());

    //Make the ball spin.
    glRotatef(g_sFrog.rotationAngle, 1.0f, 0.0f, 0.0f);

    if (g_sFrog.kicked)
    {
        g_sFrog.rotationAngle += 10.0f;
        glDisable(GL_LIGHTING);
    }

    //Rotate the ball to face the correct direction.
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.0f, 1.0f, 2.0f);
    
    gluSphere(sphere, 1, 20, 20);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

static void DrawLines()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    //Draw all yard lines except for the 0 and 100 yard lines.
    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < 19; i++)
        {
            for (int j = 0; j < 47; j++)
            {
                glVertex3f(16.0f + (8 * j), 0.1f, -87.0f - (35 * i));
                glVertex3f(16.0f + (8 * j), 0.1f, -85.0f - (35 * i));
            }
        }
    glEnd();

    //Draw thick line at the back of the endzones.
    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < 48; i++)
        {
            glVertex3f(12.0f + (8 * i), 0.1f, -12.0f);
            glVertex3f(12.0f + (8 * i), 0.1f, -6.0f);
        }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < 48; i++)
        {
            glVertex3f(12.0f + (8 * i), 0.1f, -796.0f);
            glVertex3f(12.0f + (8 * i), 0.1f, -790.0f);
        }
    glEnd();

    //Draw 0 yard line.
    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < 48; i++)
        {
            glVertex3f(12.0f + (8 * i), 0.1f, -52.0f);
            glVertex3f(12.0f + (8 * i), 0.1f, -50.0f);
        }
    glEnd();

    //Draw 100 yard line.
    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < 48; i++)
        {
            glVertex3f(12.0f + (8 * i), 0.1f, -752.0f);
            glVertex3f(12.0f + (8 * i), 0.1f, -750.0f);
        }
    glEnd();

    //Draw the dashes that intersect with the yard lines.
    glBegin(GL_QUADS);
        for (int i = 0; i < 20; i++)
        {
            if (i != 19)
            {
                //Top left.
                glVertex3f(159.0f, 0.1f, -85.0f - (35 * i));
                //Bottom left.
                glVertex3f(159.0f, 0.1f, -83.0f - (35 * i));
                //Bottom right.
                glVertex3f(161.0f, 0.1f, -83.0f - (35 * i));
                //Top right.
                glVertex3f(161.0f, 0.1f, -85.0f - (35 * i));
            
                //Top left.
                glVertex3f(247.0f, 0.1f, -85.0f - (35 * i));
                //Bottom left.
                glVertex3f(247.0f, 0.1f, -83.0f - (35 * i));
                //Bottom right.
                glVertex3f(249.0f, 0.1f, -83.0f - (35 * i));
                //Top right.
                glVertex3f(249.0f, 0.1f, -85.0f - (35 * i));

                //Top left.
                glVertex3f(159.0f, 0.1f, -89.0f - (35 * i));
                //Bottom left.
                glVertex3f(159.0f, 0.1f, -87.0f - (35 * i));
                //Bottom right.
                glVertex3f(161.0f, 0.1f, -87.0f - (35 * i));
                //Top right.
                glVertex3f(161.0f, 0.1f, -89.0f - (35 * i));

                //Top left.
                glVertex3f(247.0f, 0.1f, -89.0f - (35 * i));
                //Bottom left.
                glVertex3f(247.0f, 0.1f, -87.0f - (35 * i));
                //Bottom right.
                glVertex3f(249.0f, 0.1f, -87.0f - (35 * i));
                //Top right.
                glVertex3f(249.0f, 0.1f, -89.0f - (35 * i));
            }
            for (int j = 0; j < 4; j++)
            {
                //Draw dashes near the side lines.
                //Top left.
                glVertex3f(16.0f, 0.1f, -(59.0f + 35 * i) - (7 * j));
                //Bottom left.
                glVertex3f(16.0f, 0.1f, -(57.0f + 35 * i) - (7 * j));
                //Bottom right.
                glVertex3f(22.0f, 0.1f, -(57.0f + 35 * i) - (7 * j));
                //Top right.
                glVertex3f(22.0f, 0.1f, -(59.0f + 35 * i) - (7 * j));
                
                //Top left.
                glVertex3f(151.0f, 0.1f, -(59.0f + 35 * i) - (7 * j));
                //Bottom left.
                glVertex3f(151.0f, 0.1f, -(57.0f + 35 * i) - (7 * j));
                //Bottom right.
                glVertex3f(157.0f, 0.1f, -(57.0f + 35 * i) - (7 * j));
                //Top right.
                glVertex3f(157.0f, 0.1f, -(59.0f + 35 * i) - (7 * j));

                //Top left.
                glVertex3f(251.0f, 0.1f, -(59.0f + 35 * i) - (7 * j));
                //Bottom left.
                glVertex3f(251.0f, 0.1f, -(57.0f + 35 * i) - (7 * j));
                //Bottom right.
                glVertex3f(257.0f, 0.1f, -(57.0f + 35 * i) - (7 * j));
                //Top right.
                glVertex3f(257.0f, 0.1f, -(59.0f + 35 * i) - (7 * j));

                //Top left.
                glVertex3f(378.0f, 0.1f, -(59.0f + 35 * i) - (7 * j));
                //Bottom left.
                glVertex3f(378.0f, 0.1f, -(57.0f + 35 * i) - (7 * j));
                //Bottom right.
                glVertex3f(384.0f, 0.1f, -(57.0f + 35 * i) - (7 * j));
                //Top right.
                glVertex3f(384.0f, 0.1f, -(59.0f + 35 * i) - (7 * j));
            }
        }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < 80; i++)
        {
            //Draw left side line.
            glVertex3f(12.0f, 0.1f, -796.0f + (10 * i));
            glVertex3f(6.0f, 0.1f, -796.0f + (10 * i));
        }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < 80; i++)
        {
            //Draw right side line.
            glVertex3f(394.0f, 0.1f, -796.0f + (10 * i));
            glVertex3f(388.0f, 0.1f, -796.0f + (10 * i));
        }
    glEnd();
}

static void DrawNumbers()
{
    glBindTexture(GL_TEXTURE_2D, fiveTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0f, 0.1f, -414.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.1f, -402.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(52.0f, 0.1f, -402.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(52.0f, 0.1f, -414.0f);

    glTexCoord2f(1.0f, 1.0f); glVertex3f(348.0f, 0.1f, -400.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(348.0f, 0.1f, -388.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(360.0f, 0.1f, -388.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(360.0f, 0.1f, -400.0f);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, fourTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0f, 0.1f, -484.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.1f, -472.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(52.0f, 0.1f, -472.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(52.0f, 0.1f, -484.0f);

    glTexCoord2f(1.0f, 1.0f); glVertex3f(348.0f, 0.1f, -470.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(348.0f, 0.1f, -458.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(360.0f, 0.1f, -458.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(360.0f, 0.1f, -470.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0f, 0.1f, -344.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.1f, -332.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(52.0f, 0.1f, -332.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(52.0f, 0.1f, -344.0f);

    glTexCoord2f(1.0f, 1.0f); glVertex3f(348.0f, 0.1f, -330.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(348.0f, 0.1f, -318.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(360.0f, 0.1f, -318.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(360.0f, 0.1f, -330.0f);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, threeTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0f, 0.1f, -554.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.1f, -542.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(52.0f, 0.1f, -542.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(52.0f, 0.1f, -554.0f);

    glTexCoord2f(1.0f, 1.0f); glVertex3f(348.0f, 0.1f, -540.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(348.0f, 0.1f, -528.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(360.0f, 0.1f, -528.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(360.0f, 0.1f, -540.0f);
    
    glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0f, 0.1f, -274.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.1f, -262.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(52.0f, 0.1f, -262.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(52.0f, 0.1f, -274.0f);

    glTexCoord2f(1.0f, 1.0f); glVertex3f(348.0f, 0.1f, -260.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(348.0f, 0.1f, -248.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(360.0f, 0.1f, -248.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(360.0f, 0.1f, -260.0f);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, twoTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0f, 0.1f, -624.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.1f, -612.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(52.0f, 0.1f, -612.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(52.0f, 0.1f, -624.0f);

    glTexCoord2f(1.0f, 1.0f); glVertex3f(348.0f, 0.1f, -610.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(348.0f, 0.1f, -598.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(360.0f, 0.1f, -598.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(360.0f, 0.1f, -610.0f);
    
    glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0f, 0.1f, -204.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.1f, -192.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(52.0f, 0.1f, -192.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(52.0f, 0.1f, -204.0f);

    glTexCoord2f(1.0f, 1.0f); glVertex3f(348.0f, 0.1f, -190.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(348.0f, 0.1f, -178.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(360.0f, 0.1f, -178.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(360.0f, 0.1f, -190.0f);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, oneTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0f, 0.1f, -694.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.1f, -682.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(52.0f, 0.1f, -682.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(52.0f, 0.1f, -694.0f);

    glTexCoord2f(1.0f, 1.0f); glVertex3f(348.0f, 0.1f, -680.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(348.0f, 0.1f, -668.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(360.0f, 0.1f, -668.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(360.0f, 0.1f, -680.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0f, 0.1f, -134.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.1f, -122.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(52.0f, 0.1f, -122.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(52.0f, 0.1f, -134.0f);

    glTexCoord2f(1.0f, 1.0f); glVertex3f(348.0f, 0.1f, -120.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(348.0f, 0.1f, -108.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(360.0f, 0.1f, -108.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(360.0f, 0.1f, -120.0f);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, zeroTexture);
    glBegin(GL_QUADS);

    for (int i = 0; i < 9; i++)
    {
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(40.0f, 0.1f, -120.0f - (70.0f * i));
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(40.0f, 0.1f, -108.0f - (70.0f * i));
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(52.0f, 0.1f, -108.0f - (70.0f * i));
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(52.0f, 0.1f, -120.0f - (70.0f * i));

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(348.0f, 0.1f, -134.0f - (70.0f * i));
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(348.0f, 0.1f, -122.0f - (70.0f * i));
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(360.0f, 0.1f, -122.0f - (70.0f * i));
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(360.0f, 0.1f, -134.0f - (70.0f * i));
    }

    glEnd();
}

void DrawTurf()
{
    //Changing this value can affect performance.
    //Also make sure it divides evenly into 1080 and 500.
    const double GRID_SIZE = 20.0f;

    glPushMatrix();
    glTranslatef(-200.0f, -5.0f, 400.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, grassTexture);

    glColor3f(0.5f, 0.7f, 0.5f);
    
    glNormal3f(0.0f, 1.0f, 0.0f);

    for (int i = 0; i < 1080 / GRID_SIZE; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < 500 / GRID_SIZE; j++)
        {
            //Top left.
            if (j&1)
                glTexCoord2f(1.0f, 1.0f);
            else
                glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-50.0f + (GRID_SIZE * j), 
                       0.0f,
                       -940.0f + (GRID_SIZE * i));
            //Bottom left.
            if (j&1)
                glTexCoord2f(1.0f, 0.0f);
            else
                glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-50.0f + (GRID_SIZE * j),
                       0.0f,
                      -940.0f + GRID_SIZE + (GRID_SIZE * i));
        }
        glEnd();
    }

    DrawNumbers();
    DrawLines();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void SkyBox_CreateTextures(void)
{
    GLint minFilter = GL_NEAREST_MIPMAP_NEAREST;
    GLint magFilter = GL_NEAREST_MIPMAP_NEAREST;

    loadTexture("textures\\back.bmp", TexIDSkyBox[0],
                minFilter, magFilter);
    loadTexture("textures\\front.bmp", TexIDSkyBox[1],
                minFilter, magFilter);
    loadTexture("textures\\bottom.bmp", TexIDSkyBox[2],
                minFilter, magFilter);
    loadTexture("textures\\top.bmp", TexIDSkyBox[3],
                minFilter, magFilter);
    loadTexture("textures\\left.bmp", TexIDSkyBox[4],
                minFilter, magFilter);
    loadTexture("textures\\right.bmp", TexIDSkyBox[5],
                minFilter, magFilter);
}

void SkyBox_Draw(float x, float y, float z,
                 float width, float height, float length)
{
  x = x - width  / 2;
  y = y - height / 2;
  z = z - length / 2;

  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, TexIDSkyBox[0]);
  glBegin(GL_TRIANGLE_STRIP);                   
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y + height, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z); 
  glEnd();

  glBindTexture(GL_TEXTURE_2D, TexIDSkyBox[1]);
  glBegin(GL_TRIANGLE_STRIP);           
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height,
                                         z + length);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, TexIDSkyBox[2]);
  glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y,   z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, TexIDSkyBox[3]);
  glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y + height,z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height,
                                         z + length);    
  glEnd();

  glBindTexture(GL_TEXTURE_2D, TexIDSkyBox[5]);
  glBegin(GL_TRIANGLE_STRIP);               
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length); 
  glEnd();

  glBindTexture(GL_TEXTURE_2D, TexIDSkyBox[4]);
  glBegin(GL_TRIANGLE_STRIP);               
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height,
                                         z + length); 
  glEnd();

  glDisable(GL_TEXTURE_2D);
}

//Procedurally create the flag's texture.
void loadFlagTexture()
{
    int size = 64 * 64;
    unsigned char *pixels = new unsigned char[size*3];

    //Make the texture red.
    for (int i = 0; i < size; i++)
    {
        pixels[i*3] = 255;
        pixels[i*3+1] = 0;
        pixels[i*3+2] = 0;
    }

    //Create white stripes.
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            pixels[64*j + i*3] = 255;
            pixels[64*j + i*3+1] = 255;
            pixels[64*j + i*3+2] = 255;
        }
    }

    //Upload the texture.
    glGenTextures(1, &flagTexture);
    glBindTexture(GL_TEXTURE_2D, flagTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST_MIPMAP_NEAREST);

    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,
                          64, 64,
                          GL_RGB, GL_UNSIGNED_BYTE,
                          pixels);

    delete [] pixels;
}

void loadTexture(char *texture, GLuint &texId,
                 GLint minFilter, GLint magFilter)
{
	/*
    AUX_RGBImageRec *pTextureImage = auxDIBImageLoad(texture);

    if (pTextureImage != NULL)
    {
        glGenTextures(1, &texId);

        glBindTexture(GL_TEXTURE_2D, texId);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,
                        minFilter);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,
                        magFilter);
        //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

        //Upload the texture.
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,
                          pTextureImage->sizeX, pTextureImage->sizeY,
                          GL_RGB, GL_UNSIGNED_BYTE,
                          pTextureImage->data);
        
        //Deallocate the memory since the texture has been uploaded.
        free(pTextureImage->data);
        free(pTextureImage);
    }
	*/
}

void DrawString(char *string, int x, int y)
{
    glRasterPos2i((GLint)x, (GLint)y);

    for (unsigned i = 0 ; i < strlen(string); i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
}

void PrintHelp()
{
    glDisable(GL_LIGHTING);

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
    DrawString("Controls:", 5, scrHeight - 10);
    DrawString("1: Switch to birds-eye view.", 5, scrHeight - 25);
    DrawString("2: Switch to g_sFrog view", 5, scrHeight - 40);
    DrawString("3: Switch to free float view.", 5, scrHeight - 55);
    DrawString("4: Switch to kicker eyes view.", 5, scrHeight - 70);
    DrawString("5: Switch to returner side view.", 5, scrHeight - 85);
    DrawString("6: Switch to returner eyes view.", 5, scrHeight - 100);
    DrawString("7: Switch to follow returner view.", 5, scrHeight - 115);
    DrawString("8: Switch to choreographed camera.", 5, scrHeight - 130);
    DrawString("9: Start intro.", 5, scrHeight - 145);
    DrawString("e: Move camera forward (in free float mode).",
               5, scrHeight - 160);
    DrawString("d: Move camera backward (in free float mode).",
               5, scrHeight - 175);
    DrawString("s: Move camera left (in free float mode).",
               5, scrHeight - 190);
    DrawString("f: Move camera right (in free float mode).",
               5, scrHeight - 205);
    DrawString("space: Move camera up (in free float mode).",
               5, scrHeight - 220);
    DrawString("c: Move camera down (in free float mode).",
               5, scrHeight - 235);
    DrawString("Mouse: Change camera view vector "
               "(in free float mode).", 5, scrHeight - 250);
    DrawString("q: Quit.", 5, scrHeight - 265);
    DrawString("+: Toggle fullscreen on/off.", 5, scrHeight - 280);
    DrawString("w: Toggle wireframe on/off.", 5, scrHeight - 295);
    DrawString("h: Toggle control menu on/off.", 5, scrHeight - 310);
    DrawString("g: Toggle debug menu on/off.", 5, scrHeight - 325);
    DrawString("r: Reset the players.", 5, scrHeight - 340);
    DrawString("t: Start the animation.", 5, scrHeight - 355);

    //Go back to 3D.
    glPopMatrix(); //Restore previous projection matrix.

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix(); //Restore previous modelview matrix.

    glEnable(GL_LIGHTING);
}