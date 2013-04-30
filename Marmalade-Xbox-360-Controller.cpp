/*
 * This file is part of the Marmalade SDK Code Samples.
 *
 * Copyright (C) 2001-2012 Ideaworks3D Ltd.
 * All Rights Reserved.
 *
 * This source code is intended only as a supplement to Ideaworks Labs
 * Development Tools and/or on-line documentation.
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

/**
 * @page ExampleIwGxHelloWorld IwGx Hello World Example
 *
 * The following example, in typical Hello World style, displays the phrase
 * "Hello, World!" on screen.
 *
 * The functions required to achieve this are:
 * Printing the text to screen:
 *  - IwGxPrintString()
 *
 * Standard IwGx API:
 *  - IwGxInit()
 *  - IwGxTerminate()
 *  - IwGxSetColClear()
 *  - IwGxFlush()
 *  - IwGxSwapBuffers()
 *
 * Device interoperability through the s3e API:
 *  - s3eDeviceCheckQuitRequest()
 *  - s3eDeviceYield()
 *
 * All examples will follow this basic pattern; a brief description of what
 * the example does will be given followed by a list of all the important
 * functions and, perhaps, classes.
 *
 * Should the example be more complex, a more detailed explanation of what the
 * example does and how it does it will be added. Note that most examples
 * use an example framework to remove boilerplate code and allow the projects
 * to be made up of a single source file for easy viewing. This framework can
 * be found in the examples/s3e/ExamplesMain directory.
 *
 * @include IwGxHelloWorld.cpp
 */

// Include the single header file for the IwGx module
#include "IwGx.h"
#include "h/GamePad.h"

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
        GamePad_Update(0.0f);

        // Clear the surface
        IwGxClear();

        // Use the built-in font to display a string at coordinate (120, 150)
        const int MaxStr = 255;
        char str[MaxStr] = "";
        snprintf(str, MaxStr, "Left-Stick: {X=%.3f, Y=%.3f}",GamePad_GetStick1XAxis(), GamePad_GetStick1YAxis());
        IwGxPrintString(10, 150, str);
        snprintf(str, MaxStr, "Right-Stick: {X=%.3f, Y=%.3f}", GamePad_GetStick2XAxis(), GamePad_GetStick2YAxis());
        IwGxPrintString(10, 170, str);
        snprintf(
            str, 
            MaxStr, 
            "%s %s %s %s", 
            GamePad_GetButtonA() ? "A" : "",
            GamePad_GetButtonB() ? "B" : "",
            GamePad_GetButtonX() ? "X" : "",
            GamePad_GetButtonY() ? "Y" : "");
        IwGxPrintString(10, 190, str);
        snprintf(
            str, 
            MaxStr, 
            "%s %s %s %s",
            GamePad_GetButtonSelect() ? "Select" : "",
            GamePad_GetButtonStart() ? "Start" : "",
            GamePad_GetButtonLShoulderDown() ? "LShoulder" : "",
            GamePad_GetButtonRShoulderDown() ? "RShoulder" : "");
        IwGxPrintString(10, 210, str);
        snprintf(str, MaxStr, "Left-Trigger: %.3f Right-Trigger: %.3f}", GamePad_GetLeftTrigger(), GamePad_GetRightTrigger());
        IwGxPrintString(10, 230, str);
        snprintf(
            str, 
            MaxStr, 
            "%s %s %s %s", 
            GamePad_GetButtonDPadLeft() ? "DPadLeft" : "",
            GamePad_GetButtonDPadRight() ? "DPadRight" : "",
            GamePad_GetButtonDPadUp() ? "DPadUp" : "",
            GamePad_GetButtonDPadDown() ? "DPadDown" : "");
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
