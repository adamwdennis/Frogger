//file: player.h

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;

class Player
{
public:
    Player(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    void run();
    void catchBall();
    void hold();
    void runForTouchDown();
    void getTackled();
    void reset();
    
    bool isRunning() const { return running; }
    bool isKicking() const { return kicking; }
    bool isCatching() const { return catching; }
    bool isHolding() const { return holding; }
    bool isRunningForTouchDown() const { return runningForTouchDown; }
    bool waitUntilBallIsKicked() const { return waitingUntilBallIsKicked; }
    bool isTackled() const { return tackled; }

    void setParams(float x, float y, float z,
                   float direction, string team, bool kicking,
                   bool catching);
    void setRunning(bool running, bool waitUntilBallIsKicked);
    void setKicking(bool b) { kicking = b; }
    void setCatching(bool b) { catching = b; }
    void setHolding(bool b) { holding = b; }
    void setRunForTouchDown(bool b) { runningForTouchDown = b; }
    void setWillGetTackled(bool b) { willGetTackled = b; }
    void setWaitUntilBallIsKicked(bool b) { waitingUntilBallIsKicked = b; }

    float getLeftLegPitch() const { return leftLegPitch; }
    float getRightLegPitch() const { return rightLegPitch; }
    float getLeftLegRoll() const { return leftLegRoll; }
    float getRightLegRoll() const { return rightLegRoll; }
    float getRightArmPitch() const { return rightArmPitch; }
    float getRightArmRoll() const { return rightArmRoll; }
    float getLeftArmPitch() const { return leftArmPitch; }
    float getLeftArmRoll() const { return leftArmRoll; }
    float getTorsoPitch() const { return torsoPitch; }
    float getDirection() const { return direction; }
    float getHeadPitch() const { return headPitch; }
    string getTeam() const { return team; }

    void setRunDirection(float x, float y, float z);
    void setStopDistance(float stop) { originalStopDistance = stopDistance = stop; }
    void setJitter(bool b) { jitter = b; }
    void setDirection(float theta);
    void getPosition(float a[]) const;
private:
    bool canRun();
    //Where the player is located.
    float position[3];
    //Where the player is initially located.
    float originalPosition[3];
    //The running direction of the player.
    float runDirection[3];
    //Where the player should run to.
    float stopDistance;
    float originalStopDistance;
    //The hop height of the player.
    float hopHeight;
    float headPitch;

    //Legs.
    float leftLegPitch;
    float rightLegPitch;
    float leftLegRoll;
    float rightLegRoll;

    //Arms.
    float rightArmPitch;
    float rightArmRoll;
    float leftArmPitch;
    float leftArmRoll;

    //Which direction the player is facing.
    float direction;
    //Lean of the players torse.
    float torsoPitch;

    //These indicate what the player is currently doing.
    bool running;
    bool kicking;
    bool catching;
    bool holding;
    bool switchDirection;
    bool runningForTouchDown;
    bool waitingUntilBallIsKicked;
    bool hopUp;
    bool tackled;
    bool soundPlayed;
    bool jitter;
    bool willGetTackled;

    //Which team the player is on.
    string team;
};

#endif
