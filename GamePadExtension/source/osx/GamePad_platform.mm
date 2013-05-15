/*
 * osx-specific implementation of the GamePad extension.
 * written by Halfbot.com ( Melvin Samuel )
 */

#include "GamePad_internal.h"
#include "Xbox360ControllerManager.h"
#include "Xbox360Controller.h"


s3eResult GamePadInit_platform()
{    
    [Xbox360ControllerManager initialize];
    return S3E_RESULT_SUCCESS;
}

void GamePadTerminate_platform()
{
    // Add any platform-specific termination code here
}

bool GamePad_IsConnected_platform()
{
    int gpCount = [[Xbox360ControllerManager sharedInstance] controllerCount];
    return gpCount > 0;
}

bool GamePad_Update_platform(float dt)
{
    // Run loop, You can change the number if you dont think this is updated enought
    while (CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.002, NO) == kCFRunLoopRunHandledSource);
    return true;
}

float GamePad_GetStick1XAxis_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;
    
    return [[Xbox360ControllerManager sharedInstance] getController:0].leftStickX;
}

float GamePad_GetStick1YAxis_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;
    
    return [[Xbox360ControllerManager sharedInstance] getController:0].leftStickY;
}

float GamePad_GetStick2XAxis_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;
    
    return [[Xbox360ControllerManager sharedInstance] getController:0].rightStickX;

}

float GamePad_GetStick2YAxis_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;
    
    return [[Xbox360ControllerManager sharedInstance] getController:0].rightStickY;

}

float GamePad_GetLeftTrigger_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;
    
    return [[Xbox360ControllerManager sharedInstance] getController:0].leftTrigger;
}

float GamePad_GetRightTrigger_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].rightTrigger;
}

bool GamePad_GetButtonX_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].x;
}

bool GamePad_GetButtonY_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].y;
}

bool GamePad_GetButtonA_platform()
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

bool GamePad_GetButtonB_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].b;
}

bool GamePad_GetButtonDPadLeft_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL)
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].left;
}

bool GamePad_GetButtonDPadRight_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].right;
}

bool GamePad_GetButtonDPadUp_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].up;
}

bool GamePad_GetButtonDPadDown_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL)
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].down;
}

bool GamePad_GetButtonLShoulderDown_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].leftShoulder;
}

bool GamePad_GetButtonRShoulderDown_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL)
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].rightShoulder;
}

bool GamePad_GetButtonStart_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].start;
}

bool GamePad_GetButtonSelect_platform()
{
    if ( [[Xbox360ControllerManager sharedInstance] getController:0] == NULL )
        return 0;

    return [[Xbox360ControllerManager sharedInstance] getController:0].back;
}
