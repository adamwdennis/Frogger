//file: drawing.h

#include "common.h"
void DrawString(char *string, int x, int y);
void DrawUnit(float scaleX, float scaleY, float scaleZ);
void DrawTeam();
void DrawFootball();
void DrawTurf();
void DrawLights();
static void DrawLines();
void loadTexture(char *texture, GLuint &texId,
                 GLint minFilter, GLint magFilter);
void PrintHelp();
void DrawFlag();
void DrawUpRights();
void loadFlagTexture();
void DrawStadium();
static void DrawMarkers();
static void DrawSeat(float bottomLength, float topLength,
                     float height, float width);
void SkyBox_CreateTextures(void);
void SkyBox_Draw(float x, float y, float z,
                 float width, float height, float length);
