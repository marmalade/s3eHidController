/*
 * Internal header for the GamePad extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef GAMEPAD_INTERNAL_H
#define GAMEPAD_INTERNAL_H

#include "s3eTypes.h"
#include "GamePad.h"
#include "GamePad_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult GamePadInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult GamePadInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void GamePadTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void GamePadTerminate_platform();
bool GamePad_IsConnected_platform();

bool GamePad_Update_platform(float dt);

float GamePad_GetStick1XAxis_platform();

float GamePad_GetStick1YAxis_platform();

float GamePad_GetStick2XAxis_platform();

float GamePad_GetStick2YAxis_platform();

float GamePad_GetLeftTrigger_platform();

float GamePad_GetRightTrigger_platform();

bool GamePad_GetButtonX_platform();

bool GamePad_GetButtonY_platform();

bool GamePad_GetButtonA_platform();

bool GamePad_GetButtonB_platform();

bool GamePad_GetButtonDPadLeft_platform();

bool GamePad_GetButtonDPadRight_platform();

bool GamePad_GetButtonDPadUp_platform();

bool GamePad_GetButtonDPadDown_platform();

bool GamePad_GetButtonLShoulderDown_platform();

bool GamePad_GetButtonRShoulderDown_platform();

bool GamePad_GetButtonStart_platform();

bool GamePad_GetButtonSelect_platform();


#endif /* !GAMEPAD_INTERNAL_H */