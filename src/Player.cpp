//file: player.cpp

#include "Player.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "common.h"
#include <windows.h>
using namespace std;

extern Frog g_sFrog;

Player::Player(float x, float y, float z)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
    
    originalPosition[0] = x;
    originalPosition[1] = y;
    originalPosition[2] = z;

    direction = 0.0f;

    runDirection[0] = 0.0f;
    runDirection[1] = 0.0f;
    runDirection[2] = 0.5f + (rand() / (float)(RAND_MAX + 1)) * 0.1f;
    
    stopDistance = 99999.0f;

    hopHeight = 1.0f;
    running = false;
    kicking = false;
    catching = false;
    holding = false;
    runningForTouchDown = false;
    hopUp = false;
    tackled = false;
    soundPlayed = false;
    jitter = true;
    willGetTackled = false;

    leftLegPitch = 0.0f;
    rightLegPitch = 0.0f;
    leftLegRoll = 0.0f;
    rightLegRoll = 0.0f;
    rightArmPitch = 0.0f;
    rightArmRoll = 0.0f;
    leftArmPitch = 0.0f;
    leftArmRoll = 0.0f;
    torsoPitch = 0.0f;
    headPitch = 0.0f;

    switchDirection = false;
    team = "smu";
}

void Player::setParams(float x, float y, float z,
                       float direction, string team, bool kicking,
                       bool catching)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
    
    originalPosition[0] = x;
    originalPosition[1] = y;
    originalPosition[2] = z;

    this->kicking = kicking;
    this->direction = direction;
    this->team = team;
    this->catching = catching;
}

bool Player::canRun()
{
    if (waitingUntilBallIsKicked && g_sFrog.kicked)
        return true;
    else if (waitingUntilBallIsKicked && !g_sFrog.kicked)
        return false;
    else
        return true;

    return false;
}

void Player::run()
{
    static const float MAX_LEG_HEIGHT = 90.0f;

    if (running && canRun())
    {
        //Make the player run forward.
        if (kicking && !g_sFrog.kicked)
            position[2] += 1.1f;
        else
        {
            for (int i = 0; i < 3; i++)
                position[i] += runDirection[i];
        }

        stopDistance -= abs(runDirection[2]);

        //Move switch the direction of the legs' movement.
        if (rightLegPitch >= MAX_LEG_HEIGHT)
            switchDirection = true;
        else if (rightLegPitch <= -MAX_LEG_HEIGHT)
            switchDirection = false;

        if (switchDirection)
        {
            //Right leg forward.
            rightLegPitch -= 9.0f;
            //Left leg back.
            leftLegPitch += 9.0f;

            if (!runningForTouchDown)
                //Right arm back.
                rightArmPitch += 9.0f;
 
            //Left arm forward.
            leftArmPitch -= 9.0f;
        }
        else
        {
            //Right leg back.
            rightLegPitch += 9.0f;
            //Left leg forward.
            leftLegPitch -= 9.0f;

            if (!runningForTouchDown)
                //Right arm forward.
                rightArmPitch -= 9.0f;

            //Left arm back.
            leftArmPitch += 9.0f;
        }

        //Prevent the player from sinking into the floor.
        if (hopHeight <= 1.0f)
            hopUp = true;
        else if (hopHeight >= 2.8f)
            hopUp = false;

        if (hopUp)
            hopHeight += 0.2125f;
        else
            hopHeight -= 0.2125f;

        //Make the player hop slightly.
        position[1] = hopHeight;

        //Stop running after awhile.
        if (stopDistance < 0)
        {
            hopHeight = 1.0f;
            rightLegPitch = 0.0f;
            leftLegPitch = 0.0f;
            switchDirection = false;

            //Do this for everyone except the player
            //who caught the ball.
            if (!runningForTouchDown)
            {
                rightArmPitch = 0.0f;
                leftArmPitch = 0.0f;

                //Kicker gets tackled.
                //if (kicking)
                if (willGetTackled)
                {
                    kicking = false;
                    tackled = true;
                }
                else
                    //Everyone else holds.
                    holding = true;
            }

            running = false;
        }

        //Frog was just kicked.
        if (kicking && position[2] > -143.694)
            g_sFrog.kicked = true;
    }
}

void Player::catchBall()
{
    if (catching)
    {
        if (g_sFrog.position.GetZ() < -200.0f)
        {
            //Moves his arms up to catch the ball.
            rightArmPitch -= 1.2f;
            leftArmPitch -= 1.2f;

            //Moves his arms towards his chest.
            leftArmRoll += 1.4f;
            rightArmRoll -= 1.4f;

            //Lean back.
            torsoPitch -= 0.25f;

            //Keep this pose.
            if (rightArmPitch < -40.0f)
                catching = false;
        }
    }
}

void Player::hold()
{
    if (holding)
    {
        if (!soundPlayed)
        {
            string sound = "sounds//tackle";
            sound += ('0' + (1 + (rand() % 9)));
            sound += ".wav";

            soundPlayed = true;
            PlaySound(sound.c_str(), NULL, SND_ASYNC | SND_FILENAME);
        }

        position[1] = 1.0f;

        //Random jitter.
        if (rand() % 2 == 0 && jitter)
        {
            torsoPitch -= 0.4f;
            leftArmPitch -= 0.4f;
            rightArmPitch -= 0.4f;
        }
        else if (jitter)
        {
            torsoPitch += 0.4f;
            leftArmPitch += 0.4f;
            rightArmPitch += 0.4f;
        }

        //Left and right arms forward.
        if (leftArmPitch > -90.0f)
        {
            leftArmPitch -= 3.75f;
            rightArmPitch -= 3.75f;
        }

        //Lean head back.
        if (headPitch > -50.0f)
            headPitch -= 3.0f;

        //Lean forward.
        if (torsoPitch < 45.0f)
            torsoPitch += 2.5f;

        if (leftLegPitch < 35.0f)
            leftLegPitch += 2.5f;

        //Prevent them from becoming pretzels.
        if (torsoPitch > 50.0f)
            torsoPitch = 50.0f;
    }
}

void Player::runForTouchDown()
{
	/*
    if (runningForTouchDown)
    {
        torsoPitch = 0.0f;
        leftArmRoll = 0.0f;
        rightArmRoll = 0.0f;
        
        if (stopDistance > 0.0f)
        {
            //Make the player run.
            running = true;
            run();
            running = false;

            //Keep the g_sFrog in the player's hand.
            g_sFrog.position.SetX(g_sFrog.position.GetX() - runDirection[0]);
            g_sFrog.position[1] = 3.6f + hopHeight;
            g_sFrog.position[2] -= runDirection[2];
        }
        else if (!soundPlayed)
        {
            soundPlayed = true;
            //Weeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee.
            PlaySound("sounds//crowd1.wav", NULL,
                       SND_ASYNC | SND_FILENAME);
        }
    }
	*/
}

void Player::getTackled()
{
    if (tackled)
    {
        if (!soundPlayed)
        {
            soundPlayed = true;
            //Pain.
            PlaySound("sounds//tackle3.wav", NULL,
                      SND_ASYNC | SND_FILENAME);
        }

        //Make the player fall down.
        if (position[1] > -3.5f)
            position[1] -= 0.5f;
        
        //Lean back.
        if (torsoPitch > -90.0f)
            torsoPitch -= 5.0f;

        //Legs back.
        if (leftLegPitch > -90.0f)
            leftLegPitch -= 5.0f;

        if (rightLegPitch > -90.0f)
            rightLegPitch -= 5.0f;

        //Move the left arm.
        if (leftArmPitch > -85.0f)
            leftArmPitch -= 5.0f;
        if (leftArmRoll > -70.0f)
            leftArmRoll -= 5.0f;

        //Move the right arm.
        if (rightArmPitch > -85.0f)
            rightArmPitch -= 5.0f;
        if (rightArmRoll < 70.0f)
            rightArmRoll += 5.0f;

        //Spread out legs.
        if (leftLegRoll > -50.0f)
        {
            leftLegRoll -= 2.0f;
            rightLegRoll += 2.0f;
        }
    }
}

void Player::reset()
{
    position[0] = originalPosition[0];
    position[1] = originalPosition[1];
    position[2] = originalPosition[2];

    hopHeight = 1.0f;
    leftLegPitch = 0.0f;
    rightLegPitch = 0.0f;
    rightArmPitch = 0.0f;
    rightArmRoll = 0.0f;
    leftArmPitch = 0.0f;
    leftArmRoll = 0.0f;
    torsoPitch = 0.0f;
    headPitch = 0.0f;
    leftLegRoll = 0.0f;
    rightLegRoll = 0.0f;
    stopDistance = originalStopDistance;

    running = false;
    kicking = false;
    catching = false;
    holding = false;
    runningForTouchDown = false;
    hopUp = false;
    tackled = false;
    soundPlayed = false;
    jitter = true;
    willGetTackled = false;
}

void Player::setRunDirection(float x, float y, float z)
{
    runDirection[0] = x;
    runDirection[1] = y;
    runDirection[2] = z;
}

void Player::setDirection(float theta)
{
    this->direction = theta;
}

void Player::getPosition(float a[]) const
{
    a[0] = position[0];
    a[1] = position[1];
    a[2] = position[2];
}

void Player::setRunning(bool running, bool waitingUntilBallIsKicked)
{
    this->running = running;
    this->waitingUntilBallIsKicked = waitingUntilBallIsKicked;
}