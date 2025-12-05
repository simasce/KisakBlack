#pragma once
#include "cl_main.h"


inline connstate_t __cdecl CL_GetLocalClientConnectionState(int localClientNum)
{
    iassert(localClientNum == 0);
    return clientUIActives[localClientNum].connectionState;
}