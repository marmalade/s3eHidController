/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
/*
 * This file contains the automatically generated loader-side
 * functions that form part of the extension.
 *
 * This file is awlays compiled into all loaders but compiles
 * to nothing if this extension is not enabled in the loader
 * at build time.
 */
#include "s3eHidController_autodefs.h"
#include "s3eEdk.h"
#include "s3eHidController.h"
//Declarations of Init and Term functions
extern s3eResult s3eHidControllerInit();
extern void s3eHidControllerTerminate();


void s3eHidControllerRegisterExt()
{
    /* fill in the function pointer struct for this extension */
    void* funcPtrs[20];
    funcPtrs[0] = (void*)s3eHidControllerIsConnected;
    funcPtrs[1] = (void*)s3eHidControllerUpdate;
    funcPtrs[2] = (void*)s3eHidControllerGetStick1XAxis;
    funcPtrs[3] = (void*)s3eHidControllerGetStick1YAxis;
    funcPtrs[4] = (void*)s3eHidControllerGetStick2XAxis;
    funcPtrs[5] = (void*)s3eHidControllerGetStick2YAxis;
    funcPtrs[6] = (void*)s3eHidControllerGetLeftTrigger;
    funcPtrs[7] = (void*)s3eHidControllerGetRightTrigger;
    funcPtrs[8] = (void*)s3eHidControllerGetButtonX;
    funcPtrs[9] = (void*)s3eHidControllerGetButtonY;
    funcPtrs[10] = (void*)s3eHidControllerGetButtonA;
    funcPtrs[11] = (void*)s3eHidControllerGetButtonB;
    funcPtrs[12] = (void*)s3eHidControllerGetButtonDPadLeft;
    funcPtrs[13] = (void*)s3eHidControllerGetButtonDPadRight;
    funcPtrs[14] = (void*)s3eHidControllerGetButtonDPadUp;
    funcPtrs[15] = (void*)s3eHidControllerGetButtonDPadDown;
    funcPtrs[16] = (void*)s3eHidControllerGetButtonLShoulderDown;
    funcPtrs[17] = (void*)s3eHidControllerGetButtonRShoulderDown;
    funcPtrs[18] = (void*)s3eHidControllerGetButtonStart;
    funcPtrs[19] = (void*)s3eHidControllerGetButtonSelect;

    /*
     * Flags that specify the extension's use of locking and stackswitching
     */
    int flags[20] = { 0 };

    /*
     * Register the extension
     */
s3eEdkRegister("s3eHidController", funcPtrs, sizeof(funcPtrs), flags, s3eHidControllerInit, s3eHidControllerTerminate, 0);
}

#if !defined S3E_BUILD_S3ELOADER

#if defined S3E_EDK_USE_STATIC_INIT_ARRAY
int s3eHidControllerStaticInit()
{
    void** p = g_StaticInitArray;
    void* end = p + g_StaticArrayLen;
    while (*p) p++;
    if (p < end)
        *p = (void*)&s3eHidControllerRegisterExt;
    return 0;
}

int g_s3eHidControllerVal = s3eHidControllerStaticInit();

#elif defined S3E_EDK_USE_DLLS
S3E_EXTERN_C S3E_DLL_EXPORT void RegisterExt()
{
    s3eHidControllerRegisterExt();
}
#endif

#endif
