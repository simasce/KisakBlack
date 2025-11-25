#pragma once
#include <universal/com_math.h>

enum GfxDrawSceneMethod : __int32
{                                       // XREF: GfxDrawMethod/r
    GFX_DRAW_SCENE_NONE        = 0x0,
    GFX_DRAW_SCENE_FULLBRIGHT  = 0x1,
    GFX_DRAW_SCENE_DEBUGSHADER = 0x2,
    GFX_DRAW_SCENE_STANDARD    = 0x3,
};

struct __declspec(align(4)) GfxDrawMethod // sizeof=0x1C8
{                                       // XREF: .data:GfxDrawMethod gfxDrawMethod/r
    GfxDrawSceneMethod drawScene;       // XREF: R_GenerateSortedDrawSurfs+E1E/r
                                        // R_GenerateSortedDrawSurfs:loc_A63D75/r ...
    unsigned __int8 baseTechType;       // XREF: R_GenerateSortedDrawSurfs+181E/r
                                        // R_GenerateSortedDrawSurfs+18C4/r ...
    unsigned __int8 emissiveTechType;   // XREF: R_AddBModelSurfacesCamera(BModelDrawInfo restrict *,GfxBrushModel const restrict *,GfxDrawSurf restrict * * const,GfxDrawSurf restrict * * const,uint,float,float,uint):loc_A5D7E8/r
                                        // R_AddBModelSurfacesCamera(BModelDrawInfo restrict *,GfxBrushModel const restrict *,GfxDrawSurf restrict * * const,GfxDrawSurf restrict * * const,uint,float,float,uint)+8C/r ...
    unsigned __int8 litTechType[16][7][2][2];
                                        // XREF: R_AddMarkMeshDrawSurf(Material *,GfxMarkContext const *,ushort *,uint,float const * const,uint):loc_ACAC4B/r
                                        // R_SetDefaultLitTechTypes+D/o ...
    // padding byte
    // padding byte
};


struct GfxDrawSurfFields // sizeof=0x8
{                                       // XREF: GfxDrawSurf/r
    unsigned __int64 objectId : 16;
    unsigned __int64 fade : 4;
    unsigned __int64 customIndex : 5;
    unsigned __int64 reflectionProbeIndex : 3;
    unsigned __int64 hdrBits : 1;
    unsigned __int64 glightRender : 1;
    unsigned __int64 dlightRender : 1;
    unsigned __int64 materialSortedIndex : 12;
    unsigned __int64 primaryLightIndex : 8;
    unsigned __int64 surfType : 4;
    unsigned __int64 prepass : 2;
    unsigned __int64 noDynamicShadow : 1;
    unsigned __int64 primarySortKey : 6;
};

union GfxDrawSurf // sizeof=0x8
{                                       // XREF: R_AddBModelSurfacesCamera(BModelDrawInfo restrict *,GfxBrushModel const restrict *,GfxDrawSurf restrict * * const,GfxDrawSurf restrict * * const,uint,float,float,uint)+1FC/w
                                        // R_AddBModelSurfacesCamera(BModelDrawInfo restrict *,GfxBrushModel const restrict *,GfxDrawSurf restrict * * const,GfxDrawSurf restrict * * const,uint,float,float,uint)+1FF/w ...
    GfxDrawSurfFields fields;
    unsigned __int64 packed;
};

struct GfxDelayedCmdBuf // sizeof=0x10
{                                       // XREF: GfxBspDrawSurfData/r
                                        // GfxSModelDrawSurfData/r ...
    int primDrawSurfPos;
    unsigned int primDrawSurfSize;
    GfxDrawSurf drawSurfKey;
};

struct GfxDrawSurfList // sizeof=0x8
{                                       // XREF: GfxBspDrawSurfData/r
    GfxDrawSurf *current;               // XREF: R_GetStaticModelLightSurfs(GfxLight const *,int)+282/w
    GfxDrawSurf *end;                   // XREF: R_GetStaticModelLightSurfs(GfxLight const *,int)+297/w
};

struct GfxBspDrawSurfData // sizeof=0x18
{                                       // XREF: R_GetBspLightSurfs(GfxLight const *,int)+6D/o
    GfxDelayedCmdBuf delayedCmdBuf;
    GfxDrawSurfList drawSurfList;       // XREF: R_AddAllBspDrawSurfacesRangeCamera+10D/w
};

struct GfxSModelDrawSurfLightingData // sizeof=0x28
{                                       // XREF: ?R_AddAllStaticModelSurfacesCamera@@YAXHHPBUGfxLight@@H_N@Z/r
    GfxDelayedCmdBuf delayedCmdBuf;
    GfxDrawSurfList drawSurf[3];        // XREF: R_AddAllStaticModelSurfacesCamera(int,int,GfxLight const *,int,bool)+15E/w
};

struct __declspec(align(4)) GfxLightImage // sizeof=0x8
{                                       // XREF: GfxLightDef/r
    GfxImage *image;
    unsigned __int8 samplerState;
    // padding byte
    // padding byte
    // padding byte
};

struct GfxLightDef // sizeof=0x10
{                                       // XREF: XAssetPoolEntry<GfxLightDef>/r
    const char *name;
    GfxLightImage attenuation;
    int lmapLookupStart;
};

struct __declspec(align(16)) GfxLight // sizeof=0x170
{                                       // XREF: refdef_s/r
                                        // PointLightPartition/r ...
    unsigned __int8 type;
    unsigned __int8 canUseShadowMap;
    __int16 cullDist;
    float color[3];
    float dir[3];
    float origin[3];
    float radius;
    float cosHalfFovOuter;
    float cosHalfFovInner;
    int exponent;
    unsigned int spotShadowIndex;
    float angles[3];
    float spotShadowHiDistance;
    float diffuseColor[4];
    float specularColor[4];
    float shadowColor[4];
    float falloff[4];
    float attenuation[4];
    float aAbB[4];
    float cookieControl0[4];
    float cookieControl1[4];
    float cookieControl2[4];
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    float44 viewMatrix;
    float44 projMatrix;
    GfxLightDef *def;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};

struct GfxViewport // sizeof=0x10
{                                       // XREF: refdef_s/r
                                        // GfxCmdBufState/r ...
    int x;                              // XREF: RB_StandardDrawCommands+B5/w
                                        // RB_StandardDrawCommands+DA6/r ...
    int y;                              // XREF: RB_StandardDrawCommands+BB/w
                                        // RB_StandardDrawCommands+DAB/r ...
    int width;                          // XREF: RB_EndSceneRendering+C9/r
                                        // RB_EndSceneRendering+D2/r ...
    int height;                         // XREF: RB_StandardDrawCommands+C7/w
                                        // RB_StandardDrawCommands+DB7/r ...
};

struct GfxExposureValue // sizeof=0xB0
{                                       // XREF: refdef_s/r
                                        // GfxViewInfo/r ...
    float blackPoint[4];                // XREF: R_UpdateExposureValue+A9/r
                                        // R_DefaultExposureValue(int)+14/w ...
    float whitePoint[4];                // XREF: R_DefaultExposureValue(int)+78/w
                                        // R_DefaultExposureValue(int)+91/w ...
    float linearStart[4];               // XREF: R_DefaultExposureValue(int)+DC/w
                                        // R_DefaultExposureValue(int)+F5/w ...
    float linearEnd[4];                 // XREF: R_DefaultExposureValue(int)+140/w
                                        // R_DefaultExposureValue(int)+159/w ...
    float remapStart[4];                // XREF: R_DefaultExposureValue(int)+1A4/w
                                        // R_DefaultExposureValue(int)+1BD/w ...
    float remapEnd[4];                  // XREF: R_DefaultExposureValue(int)+208/w
                                        // R_DefaultExposureValue(int)+221/w ...
    float scurveStart[4];               // XREF: R_DefaultExposureValue(int)+26C/w
                                        // R_DefaultExposureValue(int)+285/w ...
    float scurveEnd[4];                 // XREF: R_DefaultExposureValue(int)+2D0/w
                                        // R_DefaultExposureValue(int)+2E9/w ...
    float bloomCurveLDR[4];             // XREF: R_DefaultExposureValue(int)+334/w
                                        // R_DefaultExposureValue(int)+34D/w ...
    float bloomCurveHDR[4];             // XREF: R_DefaultExposureValue(int)+398/w
                                        // R_DefaultExposureValue(int)+3B1/w ...
    float bloomScale[4];                // XREF: R_DefaultExposureValue(int)+3FC/w
                                        // R_DefaultExposureValue(int)+415/w ...
};