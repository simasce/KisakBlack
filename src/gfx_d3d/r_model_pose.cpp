#include "r_model_pose.h"
#include <xanim/xmodel.h>
#include <xanim/dobj_utils.h>
#include "r_dvars.h"
#include <cgame_mp/cg_pose_mp.h>
#include <EffectsCore/fx_marks.h>

float4 g_worldMins = { { -131072.0, -131072.0, -131072.0, 0.0 } }; // KISAKTODO: better spot
float4 g_worldMaxs = { { 131072.0, 131072.0, 131072.0, 0.0 } }; // KISAKTODO: better spot


DObjAnimMat * R_UpdateSceneEntBounds(
                GfxSceneEntity *sceneEnt,
                GfxSceneEntity **pLocalSceneEnt,
                const DObj **pObj,
                int waitForCullState)
{
    float v6; // xmm0_4
    float radiusSqMaxs; // [esp+24h] [ebp-614h]
    float radiusSqMins; // [esp+28h] [ebp-610h]
    float radiusHi; // [esp+2Ch] [ebp-60Ch]
    float v10; // [esp+34h] [ebp-604h]
    float *maxs; // [esp+40h] [ebp-5F8h]
    float *mins; // [esp+44h] [ebp-5F4h]
    int v13; // [esp+54h] [ebp-5E4h]
    int v14; // [esp+58h] [ebp-5E0h]
    int v15; // [esp+5Ch] [ebp-5DCh]
    int v16; // [esp+60h] [ebp-5D8h]
    int v17; // [esp+6Ch] [ebp-5CCh]
    int v18; // [esp+70h] [ebp-5C8h]
    int v19; // [esp+74h] [ebp-5C4h]
    __int64 v20; // [esp+78h] [ebp-5C0h]
    __int64 v21; // [esp+80h] [ebp-5B8h]
    __int64 v22; // [esp+88h] [ebp-5B0h]
    __int64 v23; // [esp+90h] [ebp-5A8h]
    int v24; // [esp+98h] [ebp-5A0h]
    __int64 v25; // [esp+ACh] [ebp-58Ch]
    float v26[7]; // [esp+B4h] [ebp-584h]
    __int64 v27; // [esp+D0h] [ebp-568h]
    float v28[11]; // [esp+D8h] [ebp-560h]
    int v29; // [esp+104h] [ebp-534h]
    int v30; // [esp+108h] [ebp-530h]
    int v31; // [esp+10Ch] [ebp-52Ch]
    int v32; // [esp+110h] [ebp-528h]
    int v33; // [esp+148h] [ebp-4F0h]
    int v34; // [esp+14Ch] [ebp-4ECh]
    int v35; // [esp+150h] [ebp-4E8h]
    int v36; // [esp+154h] [ebp-4E4h]
    int v37; // [esp+1CCh] [ebp-46Ch]
    int v38; // [esp+1D0h] [ebp-468h]
    int v39; // [esp+1D4h] [ebp-464h]
    int v40; // [esp+204h] [ebp-434h]
    int v41; // [esp+208h] [ebp-430h]
    float v42; // [esp+2C8h] [ebp-370h]
    float v43; // [esp+2CCh] [ebp-36Ch]
    float v44; // [esp+2D0h] [ebp-368h]
    float v45; // [esp+2D8h] [ebp-360h]
    float v46; // [esp+2DCh] [ebp-35Ch]
    float v47; // [esp+2E0h] [ebp-358h]
    XBoneInfo *boneInfo; // [esp+2E8h] [ebp-350h]
    DObjSkelMat boneAxis; // [esp+2ECh] [ebp-34Ch] BYREF
    DObjAnimMat *bone; // [esp+32Ch] [ebp-30Ch]
    int boneIndex; // [esp+330h] [ebp-308h]
    unsigned int animPartBit; // [esp+334h] [ebp-304h]
    int boneCount; // [esp+338h] [ebp-300h]
    XBoneInfo *boneInfoArray[160]; // [esp+33Ch] [ebp-2FCh] BYREF
    float4 *v55; // [esp+5C0h] [ebp-78h]
    float4 bounds[2]; // [esp+5C4h] [ebp-74h] BYREF
    DObjAnimMat *boneMatrix; // [esp+5E4h] [ebp-54h]
    int surfaceCount; // [esp+5E8h] [ebp-50h]
    int partBits[5]; // [esp+5ECh] [ebp-4Ch] BYREF
    int v60; // [esp+600h] [ebp-38h]
    const DpvsPlane *frustumPlanes; // [esp+608h] [ebp-30h]
    int v63; // [esp+60Ch] [ebp-2Ch]
    int frustumPlaneCount; // [esp+610h] [ebp-28h]
    DpvsView *dpvsView; // [esp+614h] [ebp-24h]
    bool offscreen; // [esp+61Bh] [ebp-1Dh]
    const DObj *obj; // [esp+61Ch] [ebp-1Ch]
    GfxSceneEntity *localSceneEnt; // [esp+620h] [ebp-18h]
    unsigned int state; // [esp+624h] [ebp-14h]
    //_UNKNOWN *v70; // [esp+62Ch] [ebp-Ch]
    //GfxSceneEntity *sceneEnta; // [esp+630h] [ebp-8h]
    //GfxSceneEntity **pLocalSceneEnta; // [esp+634h] [ebp-4h] BYREF
    //const DObj **pObja; // [esp+638h] [ebp+0h]
    //
    //v70 = a1;
    //sceneEnta = (GfxSceneEntity *)pObja;
    if (_InterlockedCompareExchange((volatile unsigned __int32 *)&sceneEnt->cull, 1, 0))
    {
        *pLocalSceneEnt = 0;
        if (waitForCullState)
        {
            do
            {
                state = sceneEnt->cull.state;
                if (!state
                    && !Assert_MyHandler(
                        "C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\r_model_pose.cpp",
                        201,
                        0,
                        "%s\n\t(state) = %i",
                        "(state >= CULL_STATE_BOUNDED_PENDING)",
                        0))
                {
                    __debugbreak();
                }
            } while (state == 1);
            if (state == 4)
            {
                return 0;
            }
            else
            {
                localSceneEnt = sceneEnt;
                *pLocalSceneEnt = sceneEnt;
                obj = localSceneEnt->obj;
                *pObj = obj;
                if (!obj
                    && !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\r_model_pose.cpp", 212, 0, "%s", "obj"))
                {
                    __debugbreak();
                }
                return I_dmaGetDObjSkel(obj);
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        localSceneEnt = sceneEnt;
        *pLocalSceneEnt = sceneEnt;
        if (!localSceneEnt->obj
            && !Assert_MyHandler(
                "C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\r_model_pose.cpp",
                229,
                0,
                "%s",
                "localSceneEnt->obj"))
        {
            __debugbreak();
        }
        obj = localSceneEnt->obj;
        *pObj = obj;
        if (!obj && !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\r_model_pose.cpp", 232, 0, "%s", "obj"))
            __debugbreak();
        offscreen = 0;
        if (r_offscreenCasterLodScale->current.value > 1.0)
        {
            dpvsView = dpvsGlob.views[scene.dpvs.localClientNum];
            if (localSceneEnt->cull.state >= 2)
            {
                frustumPlaneCount = dpvsView->frustumPlaneCount;
                v63 = 0;
                frustumPlanes = dpvsView->frustumPlanes;
                while (v63 < frustumPlaneCount)
                {
                    if (R_DpvsPlaneMaxSignedDistToBox(frustumPlanes, localSceneEnt->cull.mins) <= 0.0)
                    {
                        v60 = 1;
                        goto LABEL_28;
                    }
                    ++v63;
                    ++frustumPlanes;
                }
                v60 = 0;
            LABEL_28:
                if (v60)
                    offscreen = 1;
            }
        }
        DObjGetSurfaceData(
            obj,
            localSceneEnt->placement.base.origin,
            localSceneEnt->placement.scale,
            offscreen,
            localSceneEnt->cull.lods);
        if (useFastFile->current.enabled || !DObjBad(obj))
        {
            if (obj->localModels)
                surfaceCount = DObjGetSurfaces(obj, partBits, localSceneEnt->cull.lods);
            else
                surfaceCount = 0;
            if (!surfaceCount)
                goto LABEL_37;
            if (DObjIsRecorded(obj) && DObjGetRotTransArray(obj))
            {
                boneMatrix = I_dmaGetDObjSkel(obj);
                DObjGetSetBones(obj, partBits);
                DObjSkelSetSkel(obj, partBits);
            }
            else
            {
                boneMatrix = R_DObjCalcPose(localSceneEnt, (DObj *)obj, partBits);
            }
            if (boneMatrix)
            {
                if (!DObjSkelAreBonesUpToDate(obj, partBits)
                    && !Assert_MyHandler(
                        "C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\r_model_pose.cpp",
                        328,
                        0,
                        "%s",
                        "DObjSkelAreBonesUpToDate( obj, partBits )"))
                {
                    __debugbreak();
                }
                bounds[0] = g_worldMaxs;
                v55 = &bounds[1];
                bounds[1] = g_worldMins;
                DObjGetBoneInfo(obj, boneInfoArray);
                boneCount = DObjNumBones(obj);
                animPartBit = 0x80000000;
                boneIndex = 0;
                while (boneIndex < boneCount)
                {
                    if ((animPartBit & partBits[boneIndex >> 5]) != 0)
                    {
                        bone = &boneMatrix[boneIndex];
                        ConvertQuatToSkelMat(bone, &boneAxis);
                        boneInfo = boneInfoArray[boneIndex];
                        v42 = boneInfo->bounds[0][0];
                        v43 = boneInfo->bounds[0][1];
                        v44 = boneInfo->bounds[0][2];
                        v45 = boneInfo->bounds[1][0];
                        v46 = boneInfo->bounds[1][1];
                        v47 = boneInfo->bounds[1][2];
                        if (boneAxis.axis[0][0] >= 0.0)
                            v41 = 0;
                        else
                            v41 = -1;
                        if (boneAxis.axis[0][1] >= 0.0)
                            v39 = 0;
                        else
                            v39 = -1;
                        if (boneAxis.axis[0][2] >= 0.0)
                            v38 = 0;
                        else
                            v38 = -1;
                        if (boneAxis.axis[0][3] >= 0.0)
                            v37 = 0;
                        else
                            v37 = -1;
                        if (boneAxis.axis[1][0] >= 0.0)
                            v36 = 0;
                        else
                            v36 = -1;
                        if (boneAxis.axis[1][1] >= 0.0)
                            v35 = 0;
                        else
                            v35 = -1;
                        if (boneAxis.axis[1][2] >= 0.0)
                            v34 = 0;
                        else
                            v34 = -1;
                        if (boneAxis.axis[1][3] >= 0.0)
                            v33 = 0;
                        else
                            v33 = -1;
                        if (boneAxis.axis[2][0] >= 0.0)
                            v32 = 0;
                        else
                            v32 = -1;
                        if (boneAxis.axis[2][1] >= 0.0)
                            v31 = 0;
                        else
                            v31 = -1;
                        if (boneAxis.axis[2][2] >= 0.0)
                            v30 = 0;
                        else
                            v30 = -1;
                        if (boneAxis.axis[2][3] >= 0.0)
                            v29 = 0;
                        else
                            v29 = -1;
                        v40 = v29;
                        *(float *)&v27 = (float)(COERCE_FLOAT(LODWORD(v47) & v32 | LODWORD(v44) & ~v32) * boneAxis.axis[2][0])
                            + (float)((float)(COERCE_FLOAT(LODWORD(v46) & v36 | LODWORD(v43) & ~v36) * boneAxis.axis[1][0])
                                + (float)((float)(COERCE_FLOAT(LODWORD(v45) & v41 | LODWORD(v42) & ~v41)
                                    * boneAxis.axis[0][0])
                                    + boneAxis.origin[0]));
                        *((float *)&v27 + 1) = (float)(COERCE_FLOAT(LODWORD(v47) & v31 | LODWORD(v44) & ~v31) * boneAxis.axis[2][1])
                            + (float)((float)(COERCE_FLOAT(LODWORD(v46) & v35 | LODWORD(v43) & ~v35)
                                * boneAxis.axis[1][1])
                                + (float)((float)(COERCE_FLOAT(LODWORD(v45) & v39 | LODWORD(v42) & ~v39)
                                    * boneAxis.axis[0][1])
                                    + boneAxis.origin[1]));
                        v28[0] = (float)(COERCE_FLOAT(LODWORD(v47) & v30 | LODWORD(v44) & ~v30) * boneAxis.axis[2][2])
                            + (float)((float)(COERCE_FLOAT(LODWORD(v46) & v34 | LODWORD(v43) & ~v34) * boneAxis.axis[1][2])
                                + (float)((float)(COERCE_FLOAT(LODWORD(v45) & v38 | LODWORD(v42) & ~v38) * boneAxis.axis[0][2])
                                    + boneAxis.origin[2]));
                        v28[1] = (float)(COERCE_FLOAT(LODWORD(v47) & v40 | LODWORD(v44) & ~v40) * boneAxis.axis[2][3])
                            + (float)((float)(COERCE_FLOAT(LODWORD(v46) & v33 | LODWORD(v43) & ~v33) * boneAxis.axis[1][3])
                                + (float)((float)(COERCE_FLOAT(LODWORD(v45) & v37 | LODWORD(v42) & ~v37) * boneAxis.axis[0][3])
                                    + boneAxis.origin[3]));
                        *(float *)&v25 = (float)(COERCE_FLOAT(LODWORD(v44) & v32 | LODWORD(v47) & ~v32) * boneAxis.axis[2][0])
                            + (float)((float)(COERCE_FLOAT(LODWORD(v43) & v36 | LODWORD(v46) & ~v36) * boneAxis.axis[1][0])
                                + (float)((float)(COERCE_FLOAT(LODWORD(v42) & v41 | LODWORD(v45) & ~v41)
                                    * boneAxis.axis[0][0])
                                    + boneAxis.origin[0]));
                        *((float *)&v25 + 1) = (float)(COERCE_FLOAT(LODWORD(v44) & v31 | LODWORD(v47) & ~v31) * boneAxis.axis[2][1])
                            + (float)((float)(COERCE_FLOAT(LODWORD(v43) & v35 | LODWORD(v46) & ~v35)
                                * boneAxis.axis[1][1])
                                + (float)((float)(COERCE_FLOAT(LODWORD(v42) & v39 | LODWORD(v45) & ~v39)
                                    * boneAxis.axis[0][1])
                                    + boneAxis.origin[1]));
                        v26[0] = (float)(COERCE_FLOAT(LODWORD(v44) & v30 | LODWORD(v47) & ~v30) * boneAxis.axis[2][2])
                            + (float)((float)(COERCE_FLOAT(LODWORD(v43) & v34 | LODWORD(v46) & ~v34) * boneAxis.axis[1][2])
                                + (float)((float)(COERCE_FLOAT(LODWORD(v42) & v38 | LODWORD(v45) & ~v38) * boneAxis.axis[0][2])
                                    + boneAxis.origin[2]));
                        v26[1] = (float)(COERCE_FLOAT(LODWORD(v44) & v40 | LODWORD(v47) & ~v40) * boneAxis.axis[2][3])
                            + (float)((float)(COERCE_FLOAT(LODWORD(v43) & v33 | LODWORD(v46) & ~v33) * boneAxis.axis[1][3])
                                + (float)((float)(COERCE_FLOAT(LODWORD(v42) & v37 | LODWORD(v45) & ~v37) * boneAxis.axis[0][3])
                                    + boneAxis.origin[3]));
                        if (bounds[0].v[0] <= *(float *)&v27)
                            v24 = 0;
                        else
                            v24 = -1;
                        LODWORD(v20) = v24;
                        if (bounds[0].v[1] <= *((float *)&v27 + 1))
                            v19 = 0;
                        else
                            v19 = -1;
                        HIDWORD(v20) = v19;
                        if (bounds[0].v[2] <= v28[0])
                            v18 = 0;
                        else
                            v18 = -1;
                        LODWORD(v21) = v18;
                        if (bounds[0].v[3] <= v28[1])
                            v17 = 0;
                        else
                            v17 = -1;
                        HIDWORD(v21) = v17;
                        *(_QWORD *)bounds[0].v = v27 & v20 | *(_QWORD *)bounds[0].v & ~v20;
                        *(_QWORD *)&bounds[0].unitVec[2].packed = *(_QWORD *)v28 & v21
                            | *(_QWORD *)&bounds[0].unitVec[2].packed & ~v21;
                        if (bounds[1].v[0] <= *(float *)&v25)
                            v16 = 0;
                        else
                            v16 = -1;
                        LODWORD(v22) = v16;
                        if (bounds[1].v[1] <= *((float *)&v25 + 1))
                            v15 = 0;
                        else
                            v15 = -1;
                        HIDWORD(v22) = v15;
                        if (bounds[1].v[2] <= v26[0])
                            v14 = 0;
                        else
                            v14 = -1;
                        LODWORD(v23) = v14;
                        if (bounds[1].v[3] <= v26[1])
                            v13 = 0;
                        else
                            v13 = -1;
                        HIDWORD(v23) = v13;
                        *(_QWORD *)bounds[1].v = *(_QWORD *)bounds[1].v & v22 | v25 & ~v22;
                        *(_QWORD *)&bounds[1].unitVec[2].packed = *(_QWORD *)&bounds[1].unitVec[2].packed & v23
                            | *(_QWORD *)v26 & ~v23;
                    }
                    ++boneIndex;
                    animPartBit = (animPartBit << 31) | (animPartBit >> 1);
                }
                mins = localSceneEnt->cull.mins;
                *(_QWORD *)localSceneEnt->cull.mins = *(_QWORD *)bounds[0].v;
                mins[2] = bounds[0].v[2];
                maxs = localSceneEnt->cull.maxs;
                localSceneEnt->cull.maxs[0] = bounds[1].v[0];
                maxs[1] = bounds[1].v[1];
                maxs[2] = bounds[1].v[2];
                if (localSceneEnt->cull.state != 1
                    && !Assert_MyHandler(
                        "C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\r_model_pose.cpp",
                        353,
                        0,
                        "%s\n\t(localSceneEnt->cull.state) = %i",
                        "(localSceneEnt->cull.state == CULL_STATE_BOUNDED_PENDING)",
                        localSceneEnt->cull.state))
                {
                    __debugbreak();
                }
                if ((float)((float)(obj->radius - 16.0) - 0.0) < 0.0)
                    v10 = 0.0f;
                else
                    v10 = obj->radius - 16.0;
                radiusHi = obj->radius + 16.0;
                radiusSqMins = Vec3DistanceSq(localSceneEnt->placement.base.origin, localSceneEnt->cull.mins);
                radiusSqMaxs = Vec3DistanceSq(localSceneEnt->placement.base.origin, localSceneEnt->cull.maxs);
                if ((float)(radiusSqMins - radiusSqMaxs) < 0.0)
                    v6 = radiusSqMaxs;
                else
                    v6 = radiusSqMins;
                if ((float)(v10 * v10) > v6 || v6 > (float)(radiusHi * radiusHi))
                    localSceneEnt->obj->radius = sqrtf(v6);
                localSceneEnt->cull.state = 2;
                return boneMatrix;
            }
            else
            {
            LABEL_37:
                R_SetNoDraw(sceneEnt);
                return 0;
            }
        }
        else
        {
            R_SetNoDraw(sceneEnt);
            return 0;
        }
    }
}

DObjAnimMat *__cdecl R_DObjCalcPose(const GfxSceneEntity *sceneEnt, DObj *obj, int *partBits)
{
    int i; // [esp+0h] [ebp-1Ch]
    int completePartBits[5]; // [esp+8h] [ebp-14h] BYREF

    if ( !sceneEnt
        && !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\r_model_pose.cpp", 49, 0, "%s", "sceneEnt") )
    {
        __debugbreak();
    }
    if ( !obj && !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\r_model_pose.cpp", 50, 0, "%s", "obj") )
        __debugbreak();
    for ( i = 0; i < 5; ++i )
        completePartBits[i] = partBits[i];
    return CG_DObjCalcPose(sceneEnt->info.pose, obj, completePartBits);
}

void __cdecl R_SetNoDraw(GfxSceneEntity *sceneEnt)
{
    if ( sceneEnt->cull.state != 1
        && !Assert_MyHandler(
                    "C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\r_model_pose.cpp",
                    71,
                    0,
                    "%s\n\t(sceneEnt->cull.state) = %i",
                    "(sceneEnt->cull.state == CULL_STATE_BOUNDED_PENDING)",
                    sceneEnt->cull.state) )
    {
        __debugbreak();
    }
    sceneEnt->cull.state = 4;
}

void __cdecl R_UpdateGfxEntityBoundsCmd(GfxSceneEntity **data)
{
    const DObj *obj; // [esp+0h] [ebp-10h] BYREF
    GfxSceneEntity *localSceneEnt; // [esp+4h] [ebp-Ch] BYREF
    GfxSceneEntity *sceneEnt; // [esp+8h] [ebp-8h]
    GfxSceneEntity **pSceneEnt; // [esp+Ch] [ebp-4h]
    int savedregs; // [esp+10h] [ebp+0h] BYREF

    localSceneEnt = 0;
    obj = 0;
    if ( !data && !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\r_model_pose.cpp", 413, 0, "%s", "data") )
        __debugbreak();
    pSceneEnt = data;
    sceneEnt = *data;
    if ( R_UpdateSceneEntBounds(sceneEnt, &localSceneEnt, &obj, 0)
        && !localSceneEnt
        && !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\r_model_pose.cpp", 423, 0, "%s", "localSceneEnt") )
    {
        __debugbreak();
    }
}

