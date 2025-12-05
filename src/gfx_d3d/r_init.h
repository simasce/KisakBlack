#pragma once
#include <Windows.h>
#include <d3d9.h>

struct GfxWindowTarget // sizeof=0x10
{                                       // XREF: DxGlobals/r
    HWND__ *hwnd;                       // XREF: R_ReleaseForShutdownOrReset(void)+28/r
                                        // R_CreateDevice(GfxWindowParms const *):loc_A4ED89/r ...
    IDirect3DSwapChain9 *swapChain;     // XREF: R_ResizeWindow(void)+84/r
                                        // R_FinishAttachingToWindow+85/w ...
    int width;                          // XREF: R_ReleaseForShutdownOrReset(void)+5A/r
                                        // R_ReleaseForShutdownOrReset(void)+69/w ...
    int height;                         // XREF: R_ResizeWindow(void)+C7/w
                                        // R_FinishAttachingToWindow+99/w ...
};

struct __declspec(align(8)) DxGlobals // sizeof=0x2D00
{                                       // XREF: .data:DxGlobals dx/r
    HINSTANCE__ *hinst;
    IDirect3D9 *d3d9;                   // XREF: DB_TryLoadXFileInternal+554/r
                                        // DB_TryLoadXFileInternal+574/r ...
    IDirect3DDevice9 *device;           // XREF: yuv_init_internal(void)+154/r
                                        // yuv_init_internal(void)+15B/r ...
    unsigned int adapterIndex;          // XREF: DB_TryLoadXFileInternal+56E/r
                                        // R_CreateDeviceInternal+54/r ...
    unsigned int vendorId;              // XREF: DB_TryLoadXFileInternal+544/r
                                        // R_PreCreateWindow+D6/w ...
    bool adapterNativeIsValid;          // XREF: R_CreateDeviceInternal+2E/w
                                        // R_StoreWindowSettings+AB/r ...
    // padding byte
    // padding byte
    // padding byte
    int adapterNativeWidth;             // XREF: R_CreateDeviceInternal+21/o
                                        // R_StoreWindowSettings+B6/r ...
    int adapterNativeHeight;            // XREF: R_CreateDeviceInternal:loc_A4F18C/o
                                        // R_StoreWindowSettings+BF/r ...
    int adapterFullscreenWidth;         // XREF: R_CreateDeviceInternal+F5/w
                                        // R_CreateDeviceInternal+10B/w ...
    int adapterFullscreenHeight;        // XREF: R_CreateDeviceInternal+FE/w
                                        // R_CreateDeviceInternal+117/w ...
    bool supportsSceneNullRenderTarget; // XREF: RB_StandardDrawCommands+430/r
                                        // RB_StandardDrawCommands:loc_A74235/r ...
    bool supportsIntZ;                  // XREF: R_SetDepthOfField:loc_A65966/r
                                        // R_DoesDrawSurfListInfoNeedFloatz+6/r ...
    bool nvInitialized;                 // XREF: R_PreCreateWindow+A0/w
                                        // R_PreCreateWindow+FC/w ...
    bool nvStereoActivated;             // XREF: R_CreateDeviceInternal+7C/w
                                        // R_CreateDeviceInternal+C6/w ...
    void *nvStereoHandle;               // XREF: R_CreateDeviceInternal+83/w
                                        // R_CreateDeviceInternal+8D/o ...
    void *nvDepthBufferHandle;          // XREF: R_ResolveIntZ_PC(void)+42/r
                                        // R_ResolveIntZ_PC(void)+66/r ...
    void *nvFloatZBufferHandle;         // XREF: R_ResolveIntZ_PC(void)+4B/r
                                        // R_ResolveIntZ_PC(void)+5D/r ...
    bool resizeWindow;                  // XREF: R_CheckResizeWindow(void):loc_A4F4E0/w
                                        // R_CheckResizeWindow(void):loc_A4F4E7/r ...
    // padding byte
    // padding byte
    // padding byte
    _D3DFORMAT depthStencilFormat;      // XREF: R_CreateDevice(GfxWindowParms const *)+D7/w
                                        // R_SetD3DPresentParameters+D0/r ...
    unsigned int displayModeCount;      // XREF: R_ClosestRefreshRateForMode+D/r
                                        // R_EnumDisplayModes+28/w ...
    _D3DDISPLAYMODE displayModes[256];  // XREF: R_ClosestRefreshRateForMode+34/r
                                        // R_ClosestRefreshRateForMode+48/r ...
    const char *resolutionNameTable[257];
                                        // XREF: R_EnumDisplayModes+212/w
                                        // R_EnumDisplayModes+284/w ...
    const char *refreshRateNameTable[257];
                                        // XREF: R_EnumDisplayModes+2FB/w
                                        // R_EnumDisplayModes+346/w ...
    char modeText[5120];                // XREF: R_EnumDisplayModes:loc_A50749/o
    IDirect3DQuery9 *fencePool[8];      // XREF: R_HW_InsertFence(IDirect3DQuery9 * *)+18/r
                                        // R_ReleaseForShutdownOrReset(void)+170/r ...
    unsigned int nextFence;             // XREF: R_HW_InsertFence(IDirect3DQuery9 * *)+12/r
                                        // R_HW_InsertFence(IDirect3DQuery9 * *)+21/r ...
    int gpuSync;                        // XREF: R_UpdateGpuSyncType(void)+29/w
                                        // RB_CallExecuteRenderCommands(void)+4E5/r
    int gpuCount;                       // XREF: R_InitHardware+3E/w
                                        // R_InitHardware+A6/w ...
    _D3DMULTISAMPLE_TYPE multiSampleType;
                                        // XREF: R_SetD3DPresentParameters+A5/r
                                        // R_SetupAntiAliasing+99/w ...
    unsigned int multiSampleQuality;    // XREF: R_SetD3DPresentParameters+B0/r
                                        // R_SetupAntiAliasing+EE/w ...
    int sunSpriteSamples;               // XREF: R_Init(void)+4F/w
                                        // R_Init(void)+54/r ...
    struct IDirect3DSurface9 *singleSampleDepthStencilSurface;
                                        // XREF: R_GenerateSortedDrawSurfs+381/r
                                        // R_GenerateSortedDrawSurfs:loc_A62FDD/r ...
    bool inScene;                       // XREF: R_AssignSingleSampleDepthStencilSurface+6/r
                                        // R_AssignSingleSampleDepthStencilSurface+1D/w ...
    // padding byte
    // padding byte
    // padding byte
    int targetWindowIndex;              // XREF: R_ComErrorCleanup(void)+42/r
                                        // R_ComErrorCleanup(void)+F9/w ...
    int windowCount;                    // XREF: R_CreateGameWindow:loc_A50D41/w
                                        // RB_SetGammaRamp(GfxGammaRamp const *)+123/r ...
    GfxWindowTarget windows[1];         // XREF: R_ReleaseForShutdownOrReset(void)+28/r
                                        // R_ReleaseForShutdownOrReset(void)+5A/r ...
    IDirect3DQuery9 *flushGpuQuery;     // XREF: R_ResizeWindow(void)+D0/w
                                        // R_FinishAttachingToWindow+AD/w ...
    unsigned __int64 gpuSyncDelay;      // XREF: R_ReleaseForShutdownOrReset(void):loc_A4EB31/r
                                        // R_ReleaseForShutdownOrReset(void):loc_A4EB5E/r ...
    unsigned __int64 gpuSyncStart;      // XREF: RB_CallExecuteRenderCommands(void)+4EE/w
                                        // RB_CallExecuteRenderCommands(void)+4F8/w
    unsigned __int64 gpuSyncEnd;
    _D3DTEXTUREFILTERTYPE linearNonMippedMinFilter;
    _D3DTEXTUREFILTERTYPE linearNonMippedMagFilter;
    _D3DTEXTUREFILTERTYPE linearMippedMinFilter;
    _D3DTEXTUREFILTERTYPE linearMippedMagFilter;
    _D3DTEXTUREFILTERTYPE anisotropicMinFilter;
    _D3DTEXTUREFILTERTYPE anisotropicMagFilter;
    int linearMippedAnisotropy;
    int anisotropyFor2x;
    int anisotropyFor4x;
    int mipFilterMode;
    unsigned int mipBias;
    IDirect3DQuery9 *swapFence[4];      // XREF: R_ReleaseForShutdownOrReset(void)+1F9/r
                                        // R_ReleaseForShutdownOrReset(void)+206/w ...
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};

struct GfxGlobals // sizeof=0x24
{                                       // XREF: .data:GfxGlobals r_glob/r
    bool startedRenderThread;           // XREF: R_ShutdownInternal(int)+32/w
                                        // R_BeginRegistration(vidConfig_t *)+5A/r ...
    bool isMultiplayer;                 // XREF: R_SetIsMultiplayer(bool)+6/w
                                        // R_RegisterDvars(void)+4A5D/r ...
    // padding byte
    // padding byte
    volatile int endFrameFence;
    bool isRenderingRemoteUpdate;       // XREF: R_InitThreads(void)+3/r
                                        // R_ReleaseLostDeviceAssets2(void)+6C/r ...
    // padding byte
    // padding byte
    // padding byte
    volatile int screenUpdateNotify;    // XREF: R_BeginRemoteScreenUpdate(void):loc_A7D848/r
                                        // R_EndRemoteScreenUpdate(void (*)(void)):loc_A7D9E8/r ...
    volatile int remoteScreenUpdateNesting; // XREF: DB_Sleep:loc_58F143/r
                                        // R_SyncRenderThread(void):loc_A7A1B6/r ...
    volatile int remoteScreenUpdateInGame;
                                        // XREF: R_BeginRemoteScreenUpdate(void)+85/r
                                        // R_EndRemoteScreenUpdate(void (*)(void))+B9/r
    unsigned __int8 remoteScreenLastSceneResolveTarget;
                                        // XREF: R_Init(void)+13/w
                                        // R_PerMap_Init(void)+8/w
    // padding byte
    // padding byte
    // padding byte
    int backEndFrameCount;              // XREF: RB_DrawCoronaQuerySprite+53/r
                                        // RB_BeginFrame(void const *)+2D/r ...
    unsigned __int8 frameBuffer;
    unsigned __int8 displayBuffer;
    unsigned __int8 ui3dUseFrameBuffer;
    unsigned __int8 ui3dRenderTarget;
};

struct GfxConfiguration // sizeof=0x34
{                                       // XREF: .data:GfxConfiguration gfxCfg/r
                                        // ?CL_InitRef@@YAXXZ/r ...
    unsigned int maxClientViews;        // XREF: R_UnfilterEntFromCells(int,uint):loc_A416E8/r
                                        // R_FilterDObjIntoCells(int,uint,float * const,float)+3A/r ...
    unsigned int entCount;              // XREF: R_UnfilterEntFromCells(int,uint)+9E/r
                                        // R_UnfilterEntFromCells(int,uint)+E2/r ...
    unsigned int entnumNone;            // XREF: R_AddSceneDObj(uint,uint)+6/r
                                        // R_DrawAllSceneEnt(GfxViewInfo const *)+FE/r ...
    unsigned int entnumOrdinaryEnd;     // XREF: R_GenerateMarkVertsForDynamicModels+5A/r
                                        // R_GenerateMarkVertsForDynamicModels+10F/r ...
    int threadContextCount;
    int critSectCount;
    const char *codeFastFileName;
    const char *patchFastFileName;
    const char *uiFastFileName;
    const char *uiViewerFastFileName;
    const char *commonFastFileName;
    const char *modFastFileName;
    const char *devFastFileName;
};

struct GfxGammaRamp // sizeof=0x200
{                                       // XREF: ?R_SetColorMappings@@YAXXZ/r
    unsigned __int16 entries[256];
};

struct GfxWindowParms // sizeof=0x28
{                                       // XREF: ?R_ResizeWindow@@YAXXZ/r
                                        // R_InitGraphicsApi/r ...
    HWND__ *hwnd;                       // XREF: R_ResetDevice+B/w
                                        // R_ResetDevice+DF/r ...
    int hz;                             // XREF: R_ResetDevice+40/w
    bool fullscreen;                    // XREF: R_ResizeWindow(void)+D6/r
                                        // R_ResizeWindow(void)+152/r ...
    // padding byte
    // padding byte
    // padding byte
    int x;                              // XREF: R_ResizeWindow(void)+14E/r
                                        // R_ResizeWindow(void)+176/r ...
    int y;                              // XREF: R_ResizeWindow(void)+14A/r
                                        // R_ResizeWindow(void)+172/r ...
    int sceneWidth;                     // XREF: R_ResetDevice+31/w
    int sceneHeight;                    // XREF: R_ResetDevice+37/w
    int displayWidth;                   // XREF: R_ResizeWindow(void)+C4/r
                                        // R_ResizeWindow(void)+103/r ...
    int displayHeight;                  // XREF: R_ResizeWindow(void)+CD/r
                                        // R_ResizeWindow(void)+110/r ...
    int aaSamples;                      // XREF: R_ResetDevice+5B/w
};

struct __declspec(align(4)) vidConfig_t // sizeof=0x38
{                                       // XREF: .data:vidConfig_t vidConfig/r
                                        // clientStatic_t/r
    unsigned int sceneWidth;            // XREF: R_StoreWindowSettings+3B/w
                                        // R_StoreWindowSettings+23E/r ...
    unsigned int sceneHeight;           // XREF: R_StoreWindowSettings+46/w
                                        // R_StoreWindowSettings+225/r ...
    unsigned int displayWidth;          // XREF: CL_GetScreenDimensions(int *,int *,float *)+81/r
                                        // CL_SetupViewport(void)+6/r ...
    unsigned int displayHeight;         // XREF: CL_GetScreenDimensions(int *,int *,float *)+8C/r
                                        // CL_SetupViewport(void)+E/r ...
    unsigned __int16 outputDisplayWidth;
    unsigned __int16 outputDisplayHeight;
    unsigned int displayFrequency;      // XREF: R_StoreWindowSettings+69/w
                                        // R_ReduceWindowSettings+39/r ...
    bool isToolMode;                    // XREF: CG_Init(int,int,int,int)+A21/r
                                        // CL_InitRenderer(void):loc_5643F4/w ...
    // padding byte
    // padding byte
    // padding byte
    int isFullscreen;                   // XREF: Sys_UpdateHotkeyBlock(void):loc_7E0A25/r
                                        // R_StoreWindowSettings+76/w ...
    float aspectRatioWindow;            // XREF: CL_GetScreenDimensions(int *,int *,float *)+96/r
                                        // CL_SetupViewport(void)+26/r ...
    float aspectRatioScenePixel;        // XREF: ScrPlace_SetupFloatViewport(ScreenPlacement *,float,float,float,float,float)+7A/r
                                        // R_StoreWindowSettings+252/w ...
    float aspectRatioDisplayPixel;      // XREF: CL_GetScreenAspectRatioDisplayPixel(void)+3/r
                                        // CL_DrawSpinnerPhysical(float,float,float,float,float const * const)+D7/r ...
    unsigned int maxTextureSize;        // XREF: R_StoreDirect3DCaps+59/w
    unsigned int maxTextureMaps;        // XREF: R_StoreDirect3DCaps+5E/w
                                        // R_StoreDirect3DCaps+80/r ...
    bool deviceSupportsGamma;           // XREF: R_SetColorMappings(void)+13/r
                                        // R_StoreDirect3DCaps+7A/w ...
    // padding byte
    // padding byte
    // padding byte
};

struct trViewStatistics_t // sizeof=0x18
{                                       // XREF: .data:rendererViewStats/r
    int c_indexes;
    int c_fxIndexes;
    int c_viewIndexes;
    int c_shadowIndexes;
    int c_vertexes;
    int c_batches;
};

struct Image_MemUsage // sizeof=0xC
{                                       // XREF: trStatistics_t/r
    int total;                          // XREF: CG_DrawFPS(int,ScreenPlacement const *,float,meminfo_t *)+8B6/r
    int lightmap;
    int minspec;                        // XREF: CG_DrawFPS(int,ScreenPlacement const *,float,meminfo_t *)+90D/r
                                        // CG_DrawFPS(int,ScreenPlacement const *,float,meminfo_t *)+920/r ...
};

struct trStatistics_t // sizeof=0x10
{                                       // XREF: .data:rendererStats/r
    trViewStatistics_t *views;          // XREF: CG_DrawFPS(int,ScreenPlacement const *,float,meminfo_t *)+699/w
    Image_MemUsage c_imageUsage;        // XREF: CG_DrawFPS(int,ScreenPlacement const *,float,meminfo_t *)+8B6/r
                                        // CG_DrawFPS(int,ScreenPlacement const *,float,meminfo_t *)+90D/r ...
};

void __cdecl    R_FatalInitError(const char *msg);
void __cdecl    R_FatalLockError(HRESULT hr);
const char *__cdecl R_ErrorDescription(HRESULT hr);
void __cdecl R_SetColorMappings();
void __cdecl R_CalcGammaRamp(GfxGammaRamp *gammaRamp);
void __cdecl R_MakeDedicated(const GfxConfiguration *config);
void __cdecl SetGfxConfig(const GfxConfiguration *config);
void __cdecl R_ReleaseForShutdownOrReset();
void __cdecl R_UpdateGpuSyncType();
char __cdecl R_CreateDevice(const GfxWindowParms *wndParms);
void __cdecl R_SetD3DPresentParameters(_D3DPRESENT_PARAMETERS_ *d3dpp, const GfxWindowParms *wndParms);
void __cdecl R_SetupAntiAliasing(const GfxWindowParms *wndParms);
HRESULT __cdecl R_CreateDeviceInternal(HWND__ *hwnd, unsigned int behavior, _D3DPRESENT_PARAMETERS_ *d3dpp);
bool __cdecl R_GetMonitorDimensions(int *width, int *height);
int __cdecl R_GetDeviceType();
void __cdecl R_CheckResizeWindow();
void __cdecl R_ResizeWindow();
void __cdecl R_StoreWindowSettings(const GfxWindowParms *wndParms);
void __cdecl R_SetWndParms(GfxWindowParms *wndParms);
const char *__cdecl R_ClosestRefreshRateForMode(unsigned int width, unsigned int height, int refreshRate);
bool __cdecl R_SetCustomResolution(GfxWindowParms *wndParms);
void __cdecl R_AllocateMinimalResources();
void __cdecl R_SetIsMultiplayer(bool isMp);
void __cdecl R_InitThreads();
void __cdecl R_Init();
void R_InitGraphicsApi();
void R_InitSystems();
char __cdecl R_PreCreateWindow();
void __cdecl R_StoreDirect3DCaps(unsigned int adapterIndex);
void __cdecl R_GetDirect3DCaps(unsigned int adapterIndex, _D3DCAPS9 *caps);
void __cdecl R_PickRenderer(_D3DCAPS9 *caps);
bool __cdecl R_CheckTransparencyMsaa(unsigned int adapterIndex);
void __cdecl R_SetShadowmapFormats_DX(unsigned int adapterIndex);
void __cdecl R_EnumDisplayModes(unsigned int adapterIndex);
int __cdecl R_CompareDisplayModes(unsigned int *e0, unsigned int *e1);
int __cdecl R_AddValidRefreshRate(int refreshRate, int rateCount, int *availableRefreshRates);
int __cdecl R_CompareRefreshRates(unsigned int *e0, unsigned int *e1);
int __cdecl R_AddValidResolution(int width, int height, int resolutionCount, int (*availableResolutions)[2]);
unsigned int __cdecl R_ChooseAdapter();
HMONITOR__ *__cdecl R_ChooseMonitor();
int __stdcall R_MonitorEnumCallback(HMONITOR__ *monitorHandle, HDC__ *hdc, tagRECT *rect, unsigned int *userData);
char __cdecl R_CreateGameWindow(GfxWindowParms *wndParms);
char __cdecl R_InitHardware(const GfxWindowParms *wndParms);
void R_InitGamma();
void __cdecl R_FinishAttachingToWindow(const GfxWindowParms *wndParms);
char __cdecl R_CreateForInitOrReset();
IDirect3DQuery9 *__cdecl RB_HW_AllocOcclusionQuery();
char __cdecl R_CreateWindow(GfxWindowParms *wndParms);
char __cdecl R_ReduceWindowSettings();
void R_Register();
void R_InitGlobalStructs();
void __cdecl R_ShutdownStreams();
void __cdecl R_ShutdownInternal();
int R_ShutdownDirect3D();
int R_ShutdownDirect3DInternal();
void R_UnloadGraphicsAssets();
void __cdecl R_Shutdown(int destroyWindow);
void __cdecl R_UnloadWorld();
void __cdecl R_BeginRegistrationInternal();
void __cdecl R_BeginRegistration(vidConfig_t *vidConfigOut);
void __cdecl R_EndRegistration();
void __cdecl R_TrackStatistics(trStatistics_t *stats);
void __cdecl R_SyncGpu();
void __cdecl R_UpdateTeamColors(const float *color_allies, const float *color_axis);
void __cdecl R_ConfigureRenderer(const GfxConfiguration *config);
char __cdecl R_ReleaseLostDeviceAssets2();
char __cdecl R_RecoverLostDevice();
char __cdecl R_ResetDevice();
void __cdecl R_ComErrorCleanup();
bool __cdecl R_StereoActivated();


extern GfxConfiguration gfxCfg;
extern vidConfig_t vidConfig;
extern DxGlobals dx;

extern int g_disableRendering;