/*
 * windows-specific implementation of the GamePad extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include "GamePad_internal.h"
#include <IwDebug.h>

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include <s3eDevice.h>

// WinDDK: Adjust the directories here to match the location you installed the DDK in
// You can download the DDK from here: http://www.microsoft.com/en-us/download/details.aspx?id=11800
extern "C" 
{
    #include <C:/WinDDK/7600.16385.1/inc/api/hidsdi.h>
    #include <C:/WinDDK/7600.16385.1/inc/api/ddraw.h>
};

#pragma comment(lib, "C:/WinDDK/7600.16385.1/lib/win7/i386/dxguid.lib")
#pragma comment(lib, "C:/WinDDK/7600.16385.1/lib/win7/i386/ddraw.lib")
#pragma comment(lib, "C:/WinDDK/7600.16385.1/lib/win7/i386/hid.lib")

// Required for WinProc routines below
#pragma comment(lib, "user32.lib")

#define ARRAY_SIZE(x)	(sizeof(x) / sizeof((x)[0]))
#define WC_INPUTFRAME   TEXT("Message")
#define MAX_BUTTONS		128
#define CHECK(exp)		{ if(!(exp)) goto Error; }
#define SAFE_FREE(p)	{ if(p) { HeapFree(hHeap, 0, p); (p) = NULL; } }

// Xbox 360 Controller Button Mappings:
// Button 1: A
// Button 2: B
// Button 3: X
// Button 4: Y
// Button 5: L-Shoulder
// Button 6: R-Shoulder
// Button 7: Back
// Button 8: Start
// Button 9: L-Stick-Click
// Button 10: R-Stick-Click
static BOOL bButtonStates[MAX_BUTTONS];
static const LONG axisMax = 32768L;
static LONG lAxisX = axisMax;
static LONG lAxisY = axisMax;
static LONG lAxisZ = axisMax;
static LONG lAxisU = axisMax;
static LONG lAxisR = axisMax;
static LONG lDPad = 0;
static INT  g_NumberOfButtons = 0;

static void ParseRawInput(PRAWINPUT pRawInput)
{
    //IwDebugTraceLinePrintf("%s(%d): Parsing raw input\n", __FUNCTION__, __LINE__);
    PHIDP_PREPARSED_DATA pPreparsedData;
    HIDP_CAPS            Caps;
    PHIDP_BUTTON_CAPS    pButtonCaps;
    PHIDP_VALUE_CAPS     pValueCaps;
    USHORT               capsLength;
    UINT                 bufferSize;
    HANDLE               hHeap;
    USAGE                usage[MAX_BUTTONS];
    ULONG                i, usageLength, value;

    pPreparsedData = NULL;
    pButtonCaps    = NULL;
    pValueCaps     = NULL;
    hHeap          = GetProcessHeap();

    //
    // Get the preparsed data block
    //

    CHECK( GetRawInputDeviceInfo(pRawInput->header.hDevice, RIDI_PREPARSEDDATA, NULL, &bufferSize) == 0 );
    CHECK( pPreparsedData = (PHIDP_PREPARSED_DATA)HeapAlloc(hHeap, 0, bufferSize) );
    CHECK( (int)GetRawInputDeviceInfo(pRawInput->header.hDevice, RIDI_PREPARSEDDATA, pPreparsedData, &bufferSize) >= 0 );

    //
    // Get the joystick's capabilities
    //

    // Button caps
    CHECK( HidP_GetCaps(pPreparsedData, &Caps) == HIDP_STATUS_SUCCESS )
        CHECK( pButtonCaps = (PHIDP_BUTTON_CAPS)HeapAlloc(hHeap, 0, sizeof(HIDP_BUTTON_CAPS) * Caps.NumberInputButtonCaps) );

    capsLength = Caps.NumberInputButtonCaps;
    CHECK( HidP_GetButtonCaps(HidP_Input, pButtonCaps, &capsLength, pPreparsedData) == HIDP_STATUS_SUCCESS )
        g_NumberOfButtons = pButtonCaps->Range.UsageMax - pButtonCaps->Range.UsageMin + 1;

    // Value caps
    CHECK( pValueCaps = (PHIDP_VALUE_CAPS)HeapAlloc(hHeap, 0, sizeof(HIDP_VALUE_CAPS) * Caps.NumberInputValueCaps) );
    capsLength = Caps.NumberInputValueCaps;
    CHECK( HidP_GetValueCaps(HidP_Input, pValueCaps, &capsLength, pPreparsedData) == HIDP_STATUS_SUCCESS )

    //
    // Get the pressed buttons
    //

    usageLength = g_NumberOfButtons;
    CHECK(
        HidP_GetUsages(
        HidP_Input, pButtonCaps->UsagePage, 0, usage, &usageLength, pPreparsedData,
        (PCHAR)pRawInput->data.hid.bRawData, pRawInput->data.hid.dwSizeHid
        ) == HIDP_STATUS_SUCCESS );

    ZeroMemory(bButtonStates, sizeof(bButtonStates));
    for(i = 0; i < usageLength; i++)
        bButtonStates[usage[i] - pButtonCaps->Range.UsageMin] = TRUE;

    //
    // Get the state of discrete-valued-controls
    //
//#define VALUES_DEBUG
#ifdef VALUES_DEBUG
    char str[512] = "";
#endif

    for(i = 0; i < Caps.NumberInputValueCaps; i++)
    {
        CHECK(
            HidP_GetUsageValue(
            HidP_Input, pValueCaps[i].UsagePage, 0, pValueCaps[i].Range.UsageMin, &value, pPreparsedData,
            (PCHAR)pRawInput->data.hid.bRawData, pRawInput->data.hid.dwSizeHid
            ) == HIDP_STATUS_SUCCESS );

        // NOTE: These values are only correct for the Xbox 360 controller 
        // and for the PS3 Controller (via MotioninJoy '360 Emulation' mode)
        switch(pValueCaps[i].Range.UsageMin)
        {
        case 0x30:	// X-axis (L-Stick Horizontal)
            lAxisX = (LONG)value;
            break;

        case 0x31:	// Y-axis (L-Stick Vertical)
            lAxisY = (LONG)value;
            break;

        case 0x32: // Z-axis (L-Trigger: 32K-65K, R-Trigger: 0K-32K)
            lAxisZ = (LONG)value;
            break;

        case 0x33: // U-axis (R-Stick Horizontal)
            lAxisU = (LONG)value;
            break;

        case 0x34: // R-axis (R-Stick Vertical)
            lAxisR = (LONG)value;
            break;

        // POV Hat Switch (DPAD:
        // 1: Up
        // 2: UP/RIGHT
        // 3: RIGHT
        // 4: RIGHT/DOWN
        // 5: DOWN
        // 6: DOWN/LEFT
        // 7: LEFT
        // 8: LEFT/UP
        case 0x39:
            lDPad = (LONG)value;
            break;
        }

#ifdef VALUES_DEBUG
        char s[128];
        _snprintf(s, 128, "[Usage=0x%2X, Val=%4u] ", pValueCaps[i].Range.UsageMin, value);
        strcat(str, s);
#endif
    }


    //
    // Clean up
    //

Error:
    SAFE_FREE(pPreparsedData);
    SAFE_FREE(pButtonCaps);
    SAFE_FREE(pValueCaps);
}

static void EnumerateDevices()
{
    // Enumerate devices
    int i;
    UINT numDevicesFound = 64;
    RAWINPUTDEVICELIST allDevices[64];
    RID_DEVICE_INFO deviceInfo;
    WCHAR s[256];
    WCHAR name[256];
    UINT retVal;
    UINT sizeInfo;

    ZeroMemory(&(allDevices[0]), sizeof(allDevices));
    numDevicesFound = GetRawInputDeviceList(&(allDevices[0]), &numDevicesFound, sizeof(RAWINPUTDEVICELIST));

    for (i = 0; i < (int)numDevicesFound; ++i)
    {
        if ((allDevices[i].dwType == RIM_TYPEHID) || (allDevices[i].dwType == RIM_TYPEMOUSE) || (allDevices[i].dwType == RIM_TYPEKEYBOARD))
        {
            ZeroMemory(&deviceInfo, sizeof(deviceInfo));
            sizeInfo = sizeof(deviceInfo);
            retVal = GetRawInputDeviceInfo(allDevices[i].hDevice, RIDI_DEVICEINFO, &deviceInfo, &sizeInfo);

            UINT bufferSize = 0;
            retVal = GetRawInputDeviceInfo(allDevices[i].hDevice, RIDI_DEVICENAME, NULL, &bufferSize);
            if (retVal < 0)
            {
                _snwprintf(
                    &(s[0]), 
                    256, 
                    L"Device %d, Vendor=%X, Product=%X, Version=%d, UsagePage=%d, Usage=%d: FAILED TO GET DEVICE NAME!\n",
                    i,
                    deviceInfo.hid.dwVendorId, 
                    deviceInfo.hid.dwProductId, 
                    deviceInfo.hid.dwVersionNumber, 
                    deviceInfo.hid.usUsagePage, 
                    deviceInfo.hid.usUsage,
                    &(name[0]));
                continue;
            }

            WCHAR* wcDeviceName = new WCHAR[bufferSize + 1];
            retVal = GetRawInputDeviceInfo(allDevices[i].hDevice, RIDI_DEVICENAME, wcDeviceName, &bufferSize);
            if (retVal < 0)
            {
                _snwprintf(
                    &(s[0]), 
                    256, 
                    L"Device %d, Vendor=%X, Product=%X, Version=%d, UsagePage=%d, Usage=%d: FAILED TO GET DEVICE NAME!\n",
                    i,
                    deviceInfo.hid.dwVendorId, 
                    deviceInfo.hid.dwProductId, 
                    deviceInfo.hid.dwVersionNumber, 
                    deviceInfo.hid.usUsagePage, 
                    deviceInfo.hid.usUsage,
                    &(name[0]));
                continue;
            }

            _snwprintf(
                &(s[0]), 
                256, 
                L"\n\nDevice %d:\nVendor=%X\nProduct=%X\nVersion=%d\nUsagePage=%d\nUsage=%d\nName=%32S\n\n",
                i,
                deviceInfo.hid.dwVendorId, 
                deviceInfo.hid.dwProductId, 
                deviceInfo.hid.dwVersionNumber, 
                deviceInfo.hid.usUsagePage, 
                deviceInfo.hid.usUsage,
                &(wcDeviceName[0]));
            
            delete[] wcDeviceName;
        }
    }
}


static LRESULT CALLBACK WindowProc_InputOnly(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CREATE:
        {
            //
            // Register for joystick devices
            //
            EnumerateDevices();            

            // See USB Serial BUS HID Usage Tables (http://www.usb.org/developers/devclass_docs/Hut1_12v2.pdf) for more info
            RAWINPUTDEVICE rid;
            const USHORT usageJoystick = 4;
            const USHORT usageGamePad = 5;
            USHORT usageToAttempt = usageGamePad;

            // Try game-pad first
            rid.usUsagePage = 1;
            rid.usUsage     = usageGamePad;
            rid.dwFlags     = RIDEV_INPUTSINK;
            rid.hwndTarget  = hWnd;

            if(!RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE)))
            {
                // Try usage joystick next...if no game-pad found...this is for Logitech compatibility
                rid.usUsage = usageJoystick;
                IwDebugTraceLinePrintf("%s: WM_CREATE: RegisterRawInputDevices with usUsage %d failed, trying %d!\n", __FUNCTION__, usageGamePad, usageJoystick);
                
                if(!RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE)))
                {
                    IwError(("%s: WM_CREATE: RegisterRawInputDevices returned -1...attempted both %d and %d usages :(\n", __FUNCTION__, usageGamePad, usageJoystick));
                    return -1;
                }
            }
            else
            {
                IwDebugTraceLinePrintf("%s: WM_CREATE: RegisterRawInputDevices SUCCEEDED for Usage Id %d!\n", __FUNCTION__, rid.usUsage);
            }
        }
        return 0;

    case WM_INPUT:
        {
            //
            // Get the pointer to the raw device data, process it and update the window
            //

            PRAWINPUT pRawInput;
            UINT      bufferSize;
            HANDLE    hHeap;

            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &bufferSize, sizeof(RAWINPUTHEADER));

            hHeap     = GetProcessHeap();
            pRawInput = (PRAWINPUT)HeapAlloc(hHeap, 0, bufferSize);
            if(!pRawInput)
                return 0;

            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, pRawInput, &bufferSize, sizeof(RAWINPUTHEADER));
            ParseRawInput(pRawInput);

            HeapFree(hHeap, 0, pRawInput);
        }
        return 0;

    default:
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

static int CreateInputWindow()
{
    HWND hWnd;
    WNDCLASSEX wcex;

    wcex.cbSize        = sizeof(WNDCLASSEX);
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = 0;
    wcex.hbrBackground = NULL;
    wcex.hCursor       = NULL;
    wcex.hIcon         = NULL;
    wcex.hIconSm       = NULL;
    wcex.hInstance     = (HINSTANCE)GetModuleHandle(NULL);
    wcex.lpfnWndProc   = WindowProc_InputOnly;
    wcex.lpszClassName = WC_INPUTFRAME;
    wcex.lpszMenuName  = NULL;
    wcex.style         = 0;

    if(!RegisterClassEx(&wcex))
    {
        IwError(("RegisterClassEx() failed!"));
        return -1;
    }

    //
    // Create window
    //
    hWnd = CreateWindow(
        WC_INPUTFRAME, 
        TEXT("Joystick using Raw Input API"), 
        WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        HWND_MESSAGE,
        NULL,
        wcex.hInstance, 
        NULL);
   
    if (hWnd == NULL)
    {
        IwError(("CreateWindow() failed!"));
        return -1;
    }

    IwDebugTraceLinePrintf("%s: Successfully created input message hidden window hWnd=0x%X, hInstance=0x%X\n", __FUNCTION__, hWnd, wcex.hInstance);
    return 0;
}

static IDirectDraw7 *idd7 = NULL;

s3eResult GamePadInit_platform()
{
    CreateInputWindow();
        
    HRESULT hr = DirectDrawCreateEx( NULL, (LPVOID *)&idd7, IID_IDirectDraw7, NULL );
    if (hr != DD_OK) { IwError(("Couldn't initialize DirectDraw() :( ErrCode=0x%X\n", (uint32)hr)); }

    return S3E_RESULT_SUCCESS;
}

void GamePadTerminate_platform()
{
}

bool GamePad_IsConnected_platform()
{
    return false;
}

bool GamePad_Update_platform(float dt)
{
    // Dispatch any waiting messages to our windowproc
    MSG msg;
    bool hasMessage = false;
    do
    {
        hasMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0;
        if (hasMessage)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    while (hasMessage);

    return false;
}

float GamePad_GetStick1XAxis_platform()
{
    return (lAxisX - axisMax) / (float)axisMax;
}

float GamePad_GetStick1YAxis_platform()
{
    return (lAxisY - axisMax) / (float)axisMax;
}

float GamePad_GetStick2XAxis_platform()
{
    const float resultU = (lAxisU - axisMax) / (float)axisMax;
    //IwDebugTraceLinePrintf("%s(%d): lAxisU=%8d, lAxisR=%8d, resultU=%.2f\n", __FUNCTION__, __LINE__, lAxisU, lAxisR, resultU);
    return resultU;
}

float GamePad_GetStick2YAxis_platform()
{
    return (lAxisR - axisMax) / (float)axisMax;
}

float GamePad_GetLeftTrigger_platform()
{
    // Z-axis (L-Trigger: 32K-65K, R-Trigger: 0K-32K)
    return (max(axisMax, min(axisMax * 2, lAxisZ)) - axisMax) / (float)axisMax;
}

float GamePad_GetRightTrigger_platform()
{
    // Z-axis (L-Trigger: 32K-65K, R-Trigger: 0K-32K)
    return fabsf((max(0, min(axisMax, lAxisZ)) - axisMax) / (float)axisMax);
}

bool GamePad_GetButtonX_platform()
{
    return bButtonStates[2] ? true : false;
}

bool GamePad_GetButtonY_platform()
{
    return bButtonStates[3] ? true : false;
}

bool GamePad_GetButtonA_platform()
{
    return bButtonStates[0] ? true : false;
}

bool GamePad_GetButtonB_platform()
{
    return bButtonStates[1] ? true : false;
}

// Returns value of DPAD Left button
bool GamePad_GetButtonDPadLeft_platform()
{
    return (lDPad == 6) || (lDPad == 7) || (lDPad == 8);
}

// Returns value of DPAD Right button
bool GamePad_GetButtonDPadRight_platform()
{
    return (lDPad == 2) || (lDPad == 3) || (lDPad == 4);
}

// Returns value of DPAD Up button
bool GamePad_GetButtonDPadUp_platform()
{
    return (lDPad == 1) || (lDPad == 2) || (lDPad == 8);
}

// Returns value of DPAD Down button
bool GamePad_GetButtonDPadDown_platform()
{
    return (lDPad == 4) || (lDPad == 5) || (lDPad == 6);
}

bool GamePad_GetButtonLShoulderDown_platform()
{
    return bButtonStates[4] ? true : false;
}

bool GamePad_GetButtonRShoulderDown_platform()
{
    return bButtonStates[5] ? true : false;
}

bool GamePad_GetButtonStart_platform()
{
    return bButtonStates[7] ? true: false;
}

bool GamePad_GetButtonSelect_platform()
{
    return bButtonStates[6] ? true : false;
}