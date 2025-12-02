#pragma once

#include <qcommon/msg_mp.h>

enum pmoveVehAnimState_t : __int32
{                                                                             // XREF: pmove_t/r
                                                                                // ?G_VehicleFinishedAnimating@@YAXPAUgentity_s@@W4pmoveVehAnimState_t@@@Z/r
        PMOVE_VEH_ANIM_STATE_PLAYING     = 0x0,
        PMOVE_VEH_ANIM_STATE_END_STAGE = 0x1,
        PMOVE_VEH_ANIM_STATE_COMPLETE    = 0x2,
};

struct pmove_t // sizeof=0x910
{                                                                             // XREF: .data:pmove_t * g_pmove/r
                                                                                // UIViewer/r ...
        struct playerState_s *ps;
        usercmd_s cmd;                                            // XREF: PlayerCmd_Revive(scr_entref_t)+149/o
                                                                                // PlayerCmd_Revive(scr_entref_t)+18D/o
        usercmd_s oldcmd;
        int tracemask;
        int numtouch;
        int touchents[32];
        int numGlassTouch;
        int touchGlasses[32];
        float mins[3];
        float maxs[3];
        float xyspeed;
        float currentPitch;
        float averagePitch;
        int nextPitch;
        float pitchHistory[30];
        int proneChange;
        float maxSprintTimeMultiplier;
        bool mantleStarted;
        // padding byte
        // padding byte
        // padding byte
        float mantleEndPos[3];
        int mantleDuration;
        int viewChangeTime;
        float viewChange;
        float vehicleAngles[3];
        pmoveVehAnimState_t vehAnimState;
        unsigned __int8 handler;
        // padding byte
        // padding byte
        // padding byte
        int localClientNum;
        const struct gjkcc_input_t *m_gjkcc_input;
        colgeom_visitor_inlined_t<200> proximity_data;
                                                                                // XREF: PlayerCmd_Revive(scr_entref_t)+25C/w
                                                                                // G_ShutdownGame(int)+18/o ...
};