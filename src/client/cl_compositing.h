#pragma once

#include <gfx_d3d/r_material.h>

enum CompositeState : __int32
{                                       // XREF: CompositeJob/r
    COMPOSITE_STATE_IDLE         = 0x0,
    COMPOSITE_STATE_PRE          = 0x1,
    COMPOSITE_STATE_RENDERING    = 0x2,
    COMPOSITE_STATE_POST         = 0x3,
    COMPOSITE_STATE_POST_ALLOCED = 0x4,
    COMPOSITE_STATE_PC_WAITING_FOR_GPU = 0x5,
    COMPOSITE_STATE_COMPLETE     = 0x6,
};

enum CompositeType : __int32
{                                       // XREF: CompositeJob/r
    COMPOSITE_NONE   = 0x0,
    COMPOSITE_EMBLEM = 0x1,
};

struct __declspec(align(4)) CompositeEmblemLayer // sizeof=0x20
{                                       // XREF: .data:s_emblem/r
                                        // PCachePlayerEmblem/r ...
    __int16 icon;                       // XREF: UI_DrawEmblemSelector(int,int,itemDef_s *,rectDef_s const *,float const * const)+9D/w
                                        // UI_DrawEmblemIconThumbnail(int,rectDef_s const *,float const * const)+66/w ...
    // padding byte
    // padding byte
    int colorIdx;                       // XREF: UI_DrawEmblemSelector(int,int,itemDef_s *,rectDef_s const *,float const * const)+96/w
                                        // UI_DrawEmblemIconThumbnail(int,rectDef_s const *,float const * const)+5A/w
    float pos[2];                       // XREF: UI_DrawEmblemSelector(int,int,itemDef_s *,rectDef_s const *,float const * const)+48/w
                                        // UI_DrawEmblemSelector(int,int,itemDef_s *,rectDef_s const *,float const * const)+55/w ...
    float scale[2];                     // XREF: UI_DrawEmblemSelector(int,int,itemDef_s *,rectDef_s const *,float const * const)+62/w
                                        // UI_DrawEmblemSelector(int,int,itemDef_s *,rectDef_s const *,float const * const)+6F/w ...
    float angle;                        // XREF: UI_DrawEmblemSelector(int,int,itemDef_s *,rectDef_s const *,float const * const)+7C/w
                                        // UI_DrawEmblemIconThumbnail(int,rectDef_s const *,float const * const)+4D/w
    bool outline;                       // XREF: UI_DrawEmblemSelector(int,int,itemDef_s *,rectDef_s const *,float const * const)+81/w
    bool flip;                          // XREF: UI_DrawEmblemSelector(int,int,itemDef_s *,rectDef_s const *,float const * const)+85/w
    // padding byte
    // padding byte
};

struct __declspec(align(4)) CompositeJob // sizeof=0x19C
{                                       // XREF: .data:s_jobs/r
    CompositeState state;               // XREF: CL_CompositePushEmblem(CompositeEmblemLayer *,int)+56/r
                                        // CL_CompositeIsComplete(int)+6B/r ...
    CompositeType type;                 // XREF: CL_CompositeEmblemCallback(GfxImage *)+46/r
    int id;                             // XREF: CL_CompositePushCancel(int)+57/r
                                        // CL_CompositeIsComplete(int)+57/r ...
    int layerCount;
    CompositeEmblemLayer layers[12];
    GfxImage *renderImage;              // XREF: CL_CompositeEmblemCallback(GfxImage *)+94/w
    GfxImage *resultImage;              // XREF: CL_CompositePopImage(int)+90/r
    bool cancel;                        // XREF: CL_CompositePushCancel(int)+6B/w
    // padding byte
    // padding byte
    // padding byte
};

void __cdecl CL_CompositeSetupImageCallback(unsigned int *param);
GfxImage *__cdecl CL_CompositeSetupImage();
void __cdecl CL_CompositeReleaseImage(GfxImage *image);
bool __cdecl CL_CompositeValidateImage(GfxImage *image);
int __cdecl CL_CompositePushEmblem(CompositeEmblemLayer *layers, int layerCount);
char __cdecl CL_CompositePushCancel(int id);
char __cdecl CL_CompositeIsComplete(int id);
GfxImage *__cdecl CL_CompositePopImage(int id);
bool __cdecl CL_CompositeUseGenerated(float w, float h);
bool __cdecl CL_CompositeCheckStreaming(CompositeEmblemLayer *layers, int layerCount);
void __cdecl CL_CompositeEmblemCallback(GfxImage *result);
void __cdecl R_HW_InsertFence(IDirect3DQuery9 **fence);
void __cdecl CL_PCCopyImageGenMIPCallback(unsigned int *job);
void __cdecl CL_CompositeRender();
bool __cdecl R_HW_IsFencePending(IDirect3DQuery9 *const *fence);
char    CL_CompositeDrawEmblemPhysical(
                float x,
                float y,
                float w,
                float h,
                const float *color,
                CompositeEmblemLayer *layers,
                int layerCount);
void __cdecl UV_Transform(const float (*mat)[3], float *vec);
bool __cdecl CL_CompositeIsLayerEmpty(CompositeEmblemLayer *layer);
void __cdecl CL_CompositeResetLayer(CompositeEmblemLayer *layer);
void __cdecl CL_CompositeClearLayer(CompositeEmblemLayer *layer);
