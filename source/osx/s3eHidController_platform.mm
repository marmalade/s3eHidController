/*
 * osx-specific implementation of the GamePad extension.
 * written by Halfbot.com ( Melvin Samuel )
 */

#include "s3eHidController_internal.h"
#include "Xbox360ControllerManager.h"
#include "Xbox360Controller.h"


s3eResult s3eHidControllerInit_platform()
{    
    [Xbox360ControllerManager initialize];
    return S3E_RESULT_SUCCESS;
}

void s3eHidControllerTerminate_platform()
{
    // Add any platform-specific termination code here
}

bool s3eHidControllerIsConnected_platform()
{
    int gpCount = [[Xbox360ControllerManager sharedInstance] controllerCount];
    return gpCount > 0;
}

bool s3eHidControllerUpdate_platform()
{
    // Run loop, You can change the number if you dont think this is updated enought
    while (CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.002, NO) == kCFRunLoopRunHandledSource);
    return true;
}

float s3eHidControllerGetStick1XAxis_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;
    
    return [[Xbox360ControllerManager sharedInstance] getController:0].leftStickX;
}

float s3eHidControllerGetStick1YAxis_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;
    
    return [[Xbox360ControllerManager sharedInstance] getController:0].leftStickY;
}

float s3eHidControllerGetStick2XAxis_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;
    
    return [[Xbox360ControllerManager sharedInstance] getController:0].rightStickX;

}

float s3eHidControllerGetStick2YAxis_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;
    
    return [[Xbox360ControllerManager sharedInstance] getController:0].rightStickY;

}

float s3eHidControllerGetLeftTrigger_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;
    
    return [[Xbox360ControllerManager sharedInstance] getController:0].leftTrigger;
}

float s3eHidControllerGetRightTrigger_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].rightTrigger;
}

bool s3eHidControllerGetButtonX_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].x;
}

bool s3eHidControllerGetButtonY_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].y;
}

bool s3eHidControllerGetButtonA_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
    {
     // printf("A button not initialized so returnintg false!\n");
      return 0;
    }
       
    if (
        [[Xbox360ControllerManager sharedInstance] getController:0].a )
    {
    //    printf("A button is pressed\n");
    }
    else
    {
       // printf("A button not pressed\n");
    }
    return [[Xbox360ControllerManager sharedInstance] getController:0].a;
}

bool s3eHidControllerGetButtonB_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].b;
}

bool s3eHidControllerGetButtonDPadLeft_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL)
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].left;
}

bool s3eHidControllerGetButtonDPadRight_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].right;
}

bool s3eHidControllerGetButtonDPadUp_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].up;
}

bool s3eHidControllerGetButtonDPadDown_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL)
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].down;
}

bool s3eHidControllerGetButtonLShoulderDown_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].leftShoulder;
}

bool s3eHidControllerGetButtonRShoulderDown_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL)
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].rightShoulder;
}

bool s3eHidControllerGetButtonStart_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].start;
}

bool s3eHidControllerGetButtonSelect_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].back;
}
