
// Include the single header file for the IwGx module
#include "IwGx.h"
#include "s3eHidController.h"

// Standard C-style entry point. This can take args if required.
int main()
{
    // Initialise the IwGx drawing module
    IwGxInit();

    // Set the background colour to (opaque) blue
    IwGxSetColClear(0, 0, 0xff, 0xff);

    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {
        // Update the Xbox 360 game-pad, enabling button latch, input event processing etc
        s3eHidControllerUpdate();

        // Clear the surface
        IwGxClear();

        // Use the built-in font to display a string at coordinate (120, 150)
        const int MaxStr = 255;
        char str[MaxStr] = "";
        snprintf(str, MaxStr, "Left-Stick: {X=%.3f, Y=%.3f}",s3eHidControllerGetStick1XAxis(), s3eHidControllerGetStick1YAxis());
        IwGxPrintString(10, 150, str);
        snprintf(str, MaxStr, "Right-Stick: {X=%.3f, Y=%.3f}", s3eHidControllerGetStick2XAxis(), s3eHidControllerGetStick2YAxis());
        IwGxPrintString(10, 170, str);
        snprintf(
            str, 
            MaxStr, 
            "%s %s %s %s", 
            s3eHidControllerGetButtonA() ? "A" : "",
            s3eHidControllerGetButtonB() ? "B" : "",
            s3eHidControllerGetButtonX() ? "X" : "",
            s3eHidControllerGetButtonY() ? "Y" : "");
        IwGxPrintString(10, 190, str);
        snprintf(
            str, 
            MaxStr, 
            "%s %s %s %s %s %s",
            s3eHidControllerGetButtonSelect() ? "Select" : "",
            s3eHidControllerGetButtonStart() ? "Start" : "",
            s3eHidControllerGetButtonLShoulderDown() ? "LShoulder" : "",
            s3eHidControllerGetButtonRShoulderDown() ? "RShoulder" : "",
			s3eHidControllerGetButtonStick1() ? "LStick" : "",
			s3eHidControllerGetButtonStick2() ? "Rstick" : "");
        IwGxPrintString(10, 210, str);
        snprintf(str, MaxStr, "Left-Trigger: %.3f Right-Trigger: %.3f}", s3eHidControllerGetLeftTrigger(), s3eHidControllerGetRightTrigger());
        IwGxPrintString(10, 230, str);
        snprintf(
            str, 
            MaxStr, 
            "%s %s %s %s", 
            s3eHidControllerGetButtonDPadLeft() ? "DPadLeft" : "",
            s3eHidControllerGetButtonDPadRight() ? "DPadRight" : "",
            s3eHidControllerGetButtonDPadUp() ? "DPadUp" : "",
            s3eHidControllerGetButtonDPadDown() ? "DPadDown" : "");
        IwGxPrintString(10, 250, str);

        
        // Standard EGL-style flush of drawing to the surface
        IwGxFlush();

        // Standard EGL-style flipping of double-buffers
        IwGxSwapBuffers();

        // Sleep for 0ms to allow the OS to process events etc.
        s3eDeviceYield(0);
    }

    // Shut down the IwGx drawing module
    IwGxTerminate();

    // Return
    return 0;
}
