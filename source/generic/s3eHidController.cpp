/*
Generic implementation of the s3eHidController extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3eHidController_internal.h"
s3eResult s3eHidControllerInit()
{
    //Add any generic initialisation code here
    return s3eHidControllerInit_platform();
}

void s3eHidControllerTerminate()
{
    //Add any generic termination code here
    s3eHidControllerTerminate_platform();
}

bool s3eHidControllerIsConnected()
{
	return s3eHidControllerIsConnected_platform();
}

bool s3eHidControllerUpdate()
{
	return s3eHidControllerUpdate_platform();
}

bool s3eHidControllerUpdateLegacy(float dt)
{
    //extension never needed the dt value. So cutting it out.
    return s3eHidControllerUpdate_platform();
}

float s3eHidControllerGetStick1XAxis()
{
	return s3eHidControllerGetStick1XAxis_platform();
}

float s3eHidControllerGetStick1YAxis()
{
	return s3eHidControllerGetStick1YAxis_platform();
}

float s3eHidControllerGetStick2XAxis()
{
	return s3eHidControllerGetStick2XAxis_platform();
}

float s3eHidControllerGetStick2YAxis()
{
	return s3eHidControllerGetStick2YAxis_platform();
}

float s3eHidControllerGetLeftTrigger()
{
	return s3eHidControllerGetLeftTrigger_platform();
}

float s3eHidControllerGetRightTrigger()
{
	return s3eHidControllerGetRightTrigger_platform();
}

bool s3eHidControllerGetButtonX()
{
	return s3eHidControllerGetButtonX_platform();
}

bool s3eHidControllerGetButtonY()
{
	return s3eHidControllerGetButtonY_platform();
}

bool s3eHidControllerGetButtonA()
{
	return s3eHidControllerGetButtonA_platform();
}

bool s3eHidControllerGetButtonB()
{
	return s3eHidControllerGetButtonB_platform();
}

bool s3eHidControllerGetButtonDPadLeft()
{
	return s3eHidControllerGetButtonDPadLeft_platform();
}

bool s3eHidControllerGetButtonDPadRight()
{
	return s3eHidControllerGetButtonDPadRight_platform();
}

bool s3eHidControllerGetButtonDPadUp()
{
	return s3eHidControllerGetButtonDPadUp_platform();
}

bool s3eHidControllerGetButtonDPadDown()
{
	return s3eHidControllerGetButtonDPadDown_platform();
}

bool s3eHidControllerGetButtonLShoulderDown()
{
	return s3eHidControllerGetButtonLShoulderDown_platform();
}

bool s3eHidControllerGetButtonRShoulderDown()
{
	return s3eHidControllerGetButtonRShoulderDown_platform();
}

bool s3eHidControllerGetButtonStart()
{
	return s3eHidControllerGetButtonStart_platform();
}

bool s3eHidControllerGetButtonSelect()
{
	return s3eHidControllerGetButtonSelect_platform();
}

bool s3eHidControllerGetButtonStick1()
{
	return s3eHidControllerGetButtonStick1_platform();
}

bool s3eHidControllerGetButtonStick2()
{
	return s3eHidControllerGetButtonStick2_platform();
}
