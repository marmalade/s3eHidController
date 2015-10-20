/*
 * Internal header for the s3eHidController extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef S3EHIDCONTROLLER_INTERNAL_H
#define S3EHIDCONTROLLER_INTERNAL_H

#include "s3eTypes.h"
#include "s3eHidController.h"
#include "s3eHidController_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult s3eHidControllerInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult s3eHidControllerInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void s3eHidControllerTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void s3eHidControllerTerminate_platform();
bool s3eHidControllerIsConnected_platform();

bool s3eHidControllerUpdate_platform();

float s3eHidControllerGetStick1XAxis_platform();

float s3eHidControllerGetStick1YAxis_platform();

float s3eHidControllerGetStick2XAxis_platform();

float s3eHidControllerGetStick2YAxis_platform();

float s3eHidControllerGetLeftTrigger_platform();

float s3eHidControllerGetRightTrigger_platform();

bool s3eHidControllerGetButtonX_platform();

bool s3eHidControllerGetButtonY_platform();

bool s3eHidControllerGetButtonA_platform();

bool s3eHidControllerGetButtonB_platform();

bool s3eHidControllerGetButtonDPadLeft_platform();

bool s3eHidControllerGetButtonDPadRight_platform();

bool s3eHidControllerGetButtonDPadUp_platform();

bool s3eHidControllerGetButtonDPadDown_platform();

bool s3eHidControllerGetButtonLShoulderDown_platform();

bool s3eHidControllerGetButtonRShoulderDown_platform();

bool s3eHidControllerGetButtonStart_platform();

bool s3eHidControllerGetButtonSelect_platform();

bool s3eHidControllerGetButtonStick1_platform();

bool s3eHidControllerGetButtonStick2_platform();

bool s3eHidControllerUpdateLegacy_platform(float dt);


#endif /* !S3EHIDCONTROLLER_INTERNAL_H */