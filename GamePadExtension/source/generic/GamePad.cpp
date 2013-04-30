/*
Generic implementation of the GamePad extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "GamePad_internal.h"
s3eResult GamePadInit()
{
    //Add any generic initialisation code here
    return GamePadInit_platform();
}

void GamePadTerminate()
{
    //Add any generic termination code here
    GamePadTerminate_platform();
}

bool GamePad_IsConnected()
{
	return GamePad_IsConnected_platform();
}

bool GamePad_Update(float dt)
{
	return GamePad_Update_platform(dt);
}

float GamePad_GetStick1XAxis()
{
	return GamePad_GetStick1XAxis_platform();
}

float GamePad_GetStick1YAxis()
{
	return GamePad_GetStick1YAxis_platform();
}

float GamePad_GetStick2XAxis()
{
	return GamePad_GetStick2XAxis_platform();
}

float GamePad_GetStick2YAxis()
{
	return GamePad_GetStick2YAxis_platform();
}

float GamePad_GetLeftTrigger()
{
	return GamePad_GetLeftTrigger_platform();
}

float GamePad_GetRightTrigger()
{
	return GamePad_GetRightTrigger_platform();
}

bool GamePad_GetButtonX()
{
	return GamePad_GetButtonX_platform();
}

bool GamePad_GetButtonY()
{
	return GamePad_GetButtonY_platform();
}

bool GamePad_GetButtonA()
{
	return GamePad_GetButtonA_platform();
}

bool GamePad_GetButtonB()
{
	return GamePad_GetButtonB_platform();
}

bool GamePad_GetButtonDPadLeft()
{
	return GamePad_GetButtonDPadLeft_platform();
}

bool GamePad_GetButtonDPadRight()
{
	return GamePad_GetButtonDPadRight_platform();
}

bool GamePad_GetButtonDPadUp()
{
	return GamePad_GetButtonDPadUp_platform();
}

bool GamePad_GetButtonDPadDown()
{
	return GamePad_GetButtonDPadDown_platform();
}

bool GamePad_GetButtonLShoulderDown()
{
	return GamePad_GetButtonLShoulderDown_platform();
}

bool GamePad_GetButtonRShoulderDown()
{
	return GamePad_GetButtonRShoulderDown_platform();
}

bool GamePad_GetButtonStart()
{
	return GamePad_GetButtonStart_platform();
}

bool GamePad_GetButtonSelect()
{
	return GamePad_GetButtonSelect_platform();
}
